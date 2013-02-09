/*
 * Scene2D.cpp
 *
 * TileGame - Copyright (c) 27 déc. 2012 - Jerome Mourey
 *
 * This software is provided 'as-is', without any express or
 * implied warranty. In no event will the authors be held
 * liable for any damages arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute
 * it freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented;
 *    you must not claim that you wrote the original software.
 *    If you use this software in a product, an acknowledgment
 *    in the product documentation would be appreciated but
 *    is not required.
 * 
 * 2. Altered source versions must be plainly marked as such,
 *    and must not be misrepresented as being the original software.
 * 
 * 3. This notice may not be removed or altered from any
 *    source distribution.
 *
 *  Created on: 27 déc. 2012
 */

#include "Scene2D.h"
#include "../Loader/TMXLoader.hpp"

//#define _LOG_
#ifdef _LOG_
	#define PRINT(...) printf(__VA_ARGS__)
#else
	#define PRINT(...)
#endif



Scene2D::Scene2D(const std::string& tmx_file)
: collision()
, layers()
, width_in_tile(0)
, height_in_tile(0)
, tile_size(0)
, tilesetName()
, m_correctly_load(false)
{
	std::auto_ptr<TMX::Map> tmx_map = TMX::Loader::LoadFromFile(tmx_file);

	width_in_tile  = tmx_map->width;
	height_in_tile = tmx_map->height;
	tile_size      = tmx_map->tileWidth;

	if(tmx_map->tileWidth != tmx_map->tileHeight)
	{
		printf("tilemap %s hasn't square tile\n",tmx_file.c_str());
		return;
	}

	std::vector<int> firstGIDList;

	if(!loadingTileset(tmx_map.get(),firstGIDList)) return;

	if(!loadingLayer(tmx_map.get(),firstGIDList)) return;

	m_correctly_load = true;
}

bool Scene2D::loadingTileset(TMX::Map* map,std::vector<int>& firstGIDList)
{
	for(unsigned int i=0;i<map->tilesets.size();i++)
	{
		TMX::TileSet* tileset = map->tilesets[i];
		if(tileset->margin != 0 || tileset->spacing != 0)
		{
			printf("not handling tileset %s with spacing or margin\n",tileset->name.c_str());
			tilesetName.clear();
			firstGIDList.clear();
			return false;
		}

		if(tileset->tileWidth != tile_size || tileset->tileHeight != tile_size)
		{
			printf("not handling tileset %s with tile_size different than the tilemap\n",tileset->name.c_str());
			tilesetName.clear();
			firstGIDList.clear();
			return false;
		}

		tilesetName.push_back(tileset->sourceFileName);
		firstGIDList.push_back(tileset->firstGlobalID);
	}
	return true;
}


bool Scene2D::loadingLayer(TMX::Map* map,std::vector<int>& firstGIDList)
{
	unsigned int tile_count = width_in_tile*height_in_tile;
	bool found_layer_collision = false;
	bool found_layer_entity    = false;

	for(unsigned int i=0;i<map->layers.size();i++)
	{
		TMX::Layer* layer = map->layers[i];

		if(layer->data.size() != tile_count)
		{
			printf("layer %s is corrupted : no enough data read\n", layer->name.c_str());
			return false;
		}

		if(layer->name == "collision")
		{
			if(copyingLayer(collision,layer,firstGIDList) == -1)
			{
				printf("no valid tileset found for layer %s \n", layer->name.c_str());
			}
			else
			{
				found_layer_collision = true;
			}
		}
		else if(layer->name == "entities")
		{
			std::vector<int> entities_layer;
			if(copyingLayer(entities_layer,layer,firstGIDList) == -1)
			{
				printf("no valid tileset found for layer %s \n", layer->name.c_str());
			}
			else
			{

				found_layer_entity = loadingEntities(entities_layer);
			}
		}
		else
		{
			std::auto_ptr<Layer> dest = std::auto_ptr<Layer> (new Layer());
			int tileset_id = copyingLayer(dest->data,layer,firstGIDList);
			if(tileset_id != -1)
			{
				dest->tilesetId = tileset_id;
				layers.push_back(dest.release());
			}
			else
			{
				printf("no valid tileset found for layer %s \n", layer->name.c_str());
			}
		}
	}

	if(!found_layer_entity) 	printf("no entities layer found\n");
	if(!found_layer_collision) 	printf("no collision layer found\n");
	if(map->layers.size()<=1) 	printf("no display layer found\n");

	return found_layer_collision && found_layer_entity && map->layers.size() > 1;
}

int Scene2D::copyingLayer(std::vector<int>& destination,TMX::Layer* layer,std::vector<int>& firstGIDList)
{
	int tileset_id = findCorrespondingTileset(layer,firstGIDList);
	if(tileset_id == -1)
	{
		return tileset_id;
	}

	int firstGID = firstGIDList[tileset_id];

	for(unsigned int i = 0;i<layer->data.size();i++)
	{
		destination.push_back(layer->data[i]-firstGID);
		PRINT("%d,",layer->data[i]-firstGID);
		if((i & 63) == 63) PRINT("\n");
	}
	PRINT("\n-------------------------\n-------------------------\n\n");

	return tileset_id;
}

int  Scene2D::findCorrespondingTileset(TMX::Layer* layer,std::vector<int>& firstGIDList)
{
	int min_tile_id = layer->data[0];
	int max_tile_id = layer->data[0];

	for(unsigned int i = 1;i<layer->data.size();i++)
	{
		int tile = layer->data[i];
		if(min_tile_id > tile)     min_tile_id = tile;
		else if(max_tile_id <tile) max_tile_id = tile;
	}
	// to be sure the layer doesn't use several tileset, no firstGlobalId should be min < id < max
	// the corresponding tileset will be the one having the max firstGlobalId in this case : min >= firstGlobalId
	int firstGIDfound = -1;
	int firstGIDindex = -1;
	for(unsigned int i = 0; i<firstGIDList.size();i++)
	{
		int firstGID = firstGIDList[i];
		if(firstGID > min_tile_id && firstGID <= max_tile_id)
		{
			printf("More than one tileset used : ");
			return -1;
		}
		if(firstGID <= min_tile_id )
		{
			if(firstGID > firstGIDfound)
			{
				firstGIDfound = firstGID;
				firstGIDindex = i;
			}
		}
	}

	return firstGIDindex;
}

bool Scene2D::loadingEntities(std::vector<int>& layerEntity)
{
	bool ret = true;
	bool found_player = false;

	for(int i = 0; i<width_in_tile;i++)
	{
		for(int j = 0; j<height_in_tile;j++)
		{
			int entity_id = layerEntity[i+j*width_in_tile];
			if(entity_id>0)
			{
				Scene2D::Entity entity;
				entity.entityId = entity_id;
				entity.x = i;
				entity.y = j;

				if(entity_id == 1)
				{
					if(found_player)
					{
						ret = false;
						printf("more than one player found\n");
					}
					else
					{
						player = entity;
						found_player = true;
						PRINT("found player\n");
					}
				}
				else
				{
					entities.push_back(entity);
				}
			}
		}
	}
	if(found_player ==  false)
	{
		printf("no player found");
	}

	return ret && found_player;
}


bool Scene2D::loadSuccessfull() const
{
	return m_correctly_load;
}

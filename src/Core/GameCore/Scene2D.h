/*
 * Scene2D.h
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

#ifndef SCENE2D_H_
#define SCENE2D_H_

#include <vector>
#include <string>

namespace TMX{
	class Map;
	class Layer;
};



class Scene2D
{
public:
	struct Layer{
		int tilesetId;
		std::vector<int> data;
	};

	struct Entity{
		int entityId;
		int x;
		int y;
	};


	Scene2D(const std::string& tmx_file);


	std::vector<int>     collision;
	std::vector<Layer*>  layers;
	std::vector<Entity>  entities;
	Entity player;

	int width_in_tile;
	int height_in_tile;
	int tile_size;

	std::vector<std::string > tilesetName;

	bool loadSuccessfull() const;
private:

	bool loadingTileset(TMX::Map* map,std::vector<int>& firstGIDList);
	bool loadingLayer(TMX::Map* map,std::vector<int>& firstGIDList);
	bool loadingEntities(std::vector<int>& layerEntity);
	int  findCorrespondingTileset(TMX::Layer* layer,std::vector<int>& firstGIDList);
	int  copyingLayer(std::vector<int>& destination,TMX::Layer* layer,std::vector<int>& firstGIDList);

	bool m_correctly_load;

};

#endif /* SCENE2D_H_ */

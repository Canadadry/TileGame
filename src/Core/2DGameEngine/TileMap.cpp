/*
 * TileMap.cpp
 *
 * SceneGraph - Copyright (c) 5 déc. 2012 - Jerome Mourey
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
 *  Created on: 5 déc. 2012
 */

#include "TileMap.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

TileMap::TileMap()
: m_tileset(NULL)
, m_textureWidthInTile(0)
, m_textureHeightInTile(0)
, m_tilemapWidthInTile(0)
, m_tilemapHeightInTile(0)
, m_tileWidthInPixel(0)
, m_tileHeightInPixel(0)
, m_data()
, m_vertex_array(sf::Quads,0)
{}

TileMap::TileMap(const sf::Texture& texture, unsigned int textureWidthInTile, unsigned int textureHeightInTile)
: m_tileset(NULL)
, m_textureWidthInTile(0)
, m_textureHeightInTile(0)
, m_tilemapWidthInTile(0)
, m_tilemapHeightInTile(0)
, m_tileWidthInPixel(0)
, m_tileHeightInPixel(0)
, m_data()
, m_vertex_array(sf::Quads,0)
{
	setTileSet(texture,textureWidthInTile,textureHeightInTile);
}

TileMap::~TileMap()
{
}

void TileMap::setTileSet(const sf::Texture& texture, unsigned int textureWidthInTile, unsigned int textureHeightInTile)
{
	if(m_tileset != &texture || m_textureWidthInTile != textureWidthInTile || m_textureHeightInTile != textureHeightInTile)
	{
		if(0 != &texture && 0 != textureWidthInTile && 0 != textureHeightInTile )
		{
			m_tileset = &texture;
			m_textureWidthInTile = textureWidthInTile;
			m_textureHeightInTile = textureHeightInTile;

			sf::Vector2u textureSize  = m_tileset->getSize();
			m_tileWidthInPixel  = textureSize.x / m_textureWidthInTile;
			m_tileHeightInPixel = textureSize.y / m_textureHeightInTile;

			for(unsigned int row = 0; row<m_tilemapHeightInTile; row++)
			{
				for(unsigned int col = 0; col<m_tilemapWidthInTile; col++)
				{
//					printf("init tile (%d,%d) \n",col,row);
					setTilePosition(col, row);
					setTileRect(col, row);
//					setTileColor(col,row);
				}
			}
		}
	}
}

void TileMap::setIDForTile(unsigned int tileId, unsigned int tileColumn, unsigned int tileRow)
{
	if(tileId < m_textureWidthInTile*m_textureHeightInTile)
	{
		if( isValidePosition(tileColumn,tileRow))
		{
			m_data[idFromPosition(tileColumn,tileRow)] = tileId;
			setTileRect(tileColumn,tileRow);
		}
	}
}

int TileMap::getIDForTile(unsigned int tileColumn, unsigned int tileRow) const
{
	int ret = -1;
	if( isValidePosition(tileColumn,tileRow))
	{
		ret = m_data[idFromPosition(tileColumn,tileRow)];
	}

	return ret;
}

void TileMap::setData(unsigned int columns, unsigned int rows, const unsigned int* data)
{
	if(columns != 0 && rows !=0)
	{
		m_data.clear();
		m_data.assign(data, data+rows*columns);
		m_vertex_array.resize(rows*columns*4);
		m_tilemapWidthInTile = columns;
		m_tilemapHeightInTile = rows;

		for(unsigned int row = 0; row<m_tilemapHeightInTile; row++)
		{
			for(unsigned int col = 0; col<m_tilemapWidthInTile; col++)
			{
//				printf("init tile (%d,%d) \n",col,row);
				setTilePosition(col, row);
				setTileRect(col, row);
//				setTileColor(col,row);
			}
		}
	}
}

void TileMap::setTilePosition(unsigned int column, unsigned int row)
{
	int pos = (column+row*m_tilemapWidthInTile)*4;

	unsigned int left   = column * m_tileWidthInPixel;
	unsigned int right  = left   + m_tileWidthInPixel;
	unsigned int top    = row    * m_tileHeightInPixel;
	unsigned int bottom = top    + m_tileHeightInPixel;

//	printf("position for tile %d (%d,%d,%d,%d) \n",pos,left,right,top,bottom);

//	left   = 0;
//	right  = 100;
//	top    = 0;
//	bottom = 100;

	m_vertex_array[pos + 0].position = sf::Vector2f(left,top);
	m_vertex_array[pos + 1].position = sf::Vector2f(left,bottom);
	m_vertex_array[pos + 2].position = sf::Vector2f(right,bottom);
	m_vertex_array[pos + 3].position = sf::Vector2f(right,top);
}

void TileMap::setTileRect(unsigned int column, unsigned int row)
{
	int pos = (column+row*m_tilemapWidthInTile)*4;

	unsigned int tile =  m_data[idFromPosition(column,row)];

	unsigned int tile_row    = tile / m_textureWidthInTile;
	unsigned int tile_column = tile % m_textureWidthInTile;

	float left   = tile_column*m_tileWidthInPixel;
	float right  = left + m_tileWidthInPixel;
	float top    = tile_row*m_tileHeightInPixel;
	float bottom = top + m_tileHeightInPixel;

//	left   /= (float)m_tileset->getSize().x;
//	right  /= (float)m_tileset->getSize().x;
//	top    /= (float)m_tileset->getSize().y;
//	bottom /= (float)m_tileset->getSize().y;
//
//	left   = 0.0;
//	right  = 1.0;
//	top    = 0.0;
//	bottom = 1.0;

//	printf("textcoord for tile %d (%f,%f,%f,%f) \n",pos,left,right,top,bottom);

    m_vertex_array[pos + 0].texCoords = sf::Vector2f(left, top);
    m_vertex_array[pos + 1].texCoords = sf::Vector2f(left, bottom);
    m_vertex_array[pos + 2].texCoords = sf::Vector2f(right, bottom);
    m_vertex_array[pos + 3].texCoords = sf::Vector2f(right, top);
}

void TileMap::setTileColor(unsigned int column,unsigned  int row)
{
	int pos = (column+row*m_tilemapWidthInTile)*4;

	m_vertex_array[pos + 0].color = sf::Color::White;
    m_vertex_array[pos + 1].color = sf::Color::White;
    m_vertex_array[pos + 2].color = sf::Color::White;
    m_vertex_array[pos + 3].color = sf::Color::White;

}

void TileMap::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    if (m_tileset)
    {
        states.transform *= getTransform();
        states.texture = m_tileset;
        target.draw(m_vertex_array,states);
    }
}

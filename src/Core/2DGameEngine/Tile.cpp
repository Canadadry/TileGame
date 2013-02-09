/*
 * Tile.cpp
 *
 * TileGame - Copyright (c) 3 févr. 2013 - Jerome Mourey
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
 *  Created on: 3 févr. 2013
 */

#include "Tile.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>



Tile::Tile()
: m_tileset(NULL)
, m_textureWidthInTile(0)
, m_textureHeightInTile(0)
, m_tileWidthInPixel(0)
, m_tileHeightInPixel(0)
, m_tileId(0)
, m_vertex_array(sf::Quads,4)
{}

Tile::Tile(const sf::Texture& texture, unsigned int textureWidthInTile, unsigned int textureHeightInTile)
: m_tileset(NULL)
, m_textureWidthInTile(0)
, m_textureHeightInTile(0)
, m_tileWidthInPixel(0)
, m_tileHeightInPixel(0)
, m_tileId(0)
, m_vertex_array(sf::Quads,4)
{
	setTileSet(texture,textureWidthInTile,textureHeightInTile);
}

Tile::~Tile(){}


void Tile::setTileSet(const sf::Texture& texture, unsigned int textureWidthInTile, unsigned int textureHeightInTile)
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

			setTilePosition();
			setTileRect();
		}
	}
}

void Tile::setID(unsigned int tileId)
{
	if(tileId < m_textureWidthInTile*m_textureHeightInTile)
	{
		if(tileId != m_tileId)
		{
			m_tileId = tileId;
			setTileRect();
		}
	}
}

int Tile::getID() const
{
	return m_tileId;
}

void Tile::setTilePosition()
{
	int pos = 0;//(column+row*m_tilemapWidthInTile)*4;

	unsigned int left   = 0      * m_tileWidthInPixel;
	unsigned int right  = left   + m_tileWidthInPixel;
	unsigned int top    = 0      * m_tileHeightInPixel;
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

void Tile::setTileRect()
{
	int pos = 0;//(column+row*m_tilemapWidthInTile)*4;

	unsigned int tile =  m_tileId;//m_data[idFromPosition(column,row)];

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

void Tile::setTileColor()
{
	int pos = 0;//(column+row*m_tilemapWidthInTile)*4;

	m_vertex_array[pos + 0].color = sf::Color::White;
    m_vertex_array[pos + 1].color = sf::Color::White;
    m_vertex_array[pos + 2].color = sf::Color::White;
    m_vertex_array[pos + 3].color = sf::Color::White;

}

void Tile::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    if (m_tileset)
    {
        states.transform *= getTransform();
        states.texture = m_tileset;
        target.draw(m_vertex_array,states);
    }
}



/*
 * Tile.h
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

#ifndef TILE_H_
#define TILE_H_

#include <vector>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace sf{
class Texture;
}


class Tile : public sf::Drawable, public sf::Transformable
{
public:
	Tile();
	Tile(const sf::Texture& texture, unsigned int textureWidthInTile, unsigned int textureHeightInTile);
	virtual ~Tile();


	void setTileSet(const sf::Texture& texture, unsigned int textureWidthInTile, unsigned int textureHeightInTile);
	void setID(unsigned int tileId);
	int  getID() const;

private:
	const sf::Texture*        m_tileset;
	unsigned int              m_textureWidthInTile;
	unsigned int              m_textureHeightInTile;
	unsigned int              m_tileWidthInPixel;
	unsigned int              m_tileHeightInPixel;
	unsigned int              m_tileId;
	sf::VertexArray           m_vertex_array;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setTilePosition();
	void setTileRect    ();
	void setTileColor   ();

};

#endif /* TILE_H_ */

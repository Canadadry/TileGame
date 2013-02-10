/*
 * Coin.cpp
 *
 * TileGame - Copyright (c) 10 févr. 2013 - Jerome Mourey
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
 *  Created on: 10 févr. 2013
 */

#include "Coin.h"


sf::Texture Coin::m_texture;
bool Coin::m_texture_init;

extern std::string path;

Coin::Coin(int x,int y,int tile_size)
: Mob((x+0.5)*tile_size,(y+0.5)*tile_size,EntityBehavior(0.0,0.0,0.0,0.0))
{
	m_entity.setSize(sf::Vector2f(tile_size,tile_size));
	m_entity.setOrigin(sf::Vector2f(tile_size/2,tile_size/2));

	if(m_texture_init == false)
	{
		m_texture.loadFromFile(path+"/coin.png");
		m_texture_init = true;
	}
	m_sprite.setTileSet(m_texture,4,1);
	int anim_moving[] = {0,1,2,3};
	std::vector<int> anim ;
	anim.assign(anim_moving,anim_moving+2);
	m_sprite.appendAnimDesc(anim,200);
	m_sprite.useAnim(0);
	m_sprite.setOrigin(8,8);

}

Coin::~Coin()
{
	// TODO Auto-generated destructor stub
}


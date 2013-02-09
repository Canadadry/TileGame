/*
 * Goomba.cpp
 *
 * TileGame - Copyright (c) 5 févr. 2013 - Jerome Mourey
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
 *  Created on: 5 févr. 2013
 */

#include "Goomba.h"

sf::Texture Goomba::m_texture;
bool Goomba::m_texture_init;

extern std::string path;


Goomba::Goomba(int x,int y,int tile_size)
: Mob(x,y,tile_size)
{
	if(m_texture_init == false)
	{
		m_texture.loadFromFile(path+"/goomba.png");
		m_texture_init = true;
	}
	m_sprite.setTileSet(m_texture,2,1);
	int anim_moving[] = {0,1};
	std::vector<int> anim ;
	anim.assign(anim_moving,anim_moving+2);
	m_sprite.appendAnimDesc(anim,100);
	m_sprite.useAnim(0);
	m_sprite.setOrigin(8,8);
	m_entity.move(Entity::LEFT);

}

Goomba::~Goomba()
{
}

void Goomba::update(const World& world,float elapsedTime)
{
	Mob::update(world,elapsedTime);

	if(m_entity.state() == Entity::STOPED)
	{
		if(m_entity.direction() == Entity::LEFT) m_entity.move(Entity::RIGHT);
		else                                     m_entity.move(Entity::LEFT);
	}

}



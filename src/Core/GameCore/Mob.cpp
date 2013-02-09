/*
 * Mob.cpp
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

#include "Mob.h"
#include <SFML/Graphics.hpp>

#include "../2DGameEngine/DrawableGroupe.h"
#include "../2DGameEngine/TileMap.h"
#include "../2DGameEngine/AnimatedTile.h"

#include "../GameCore/Scene2D.h"

#include "../MyPhisics/Entity.h"
#include "../MyPhisics/World.h"


	Mob::Mob(int x,int y,int tile_size, const EntityBehavior& behavior)
	: m_entity((x+0.5)*tile_size,(y+0.5)*tile_size,tile_size,behavior)
	, m_sprite()
	, m_tile_size(tile_size)
	, m_direction(Entity::LEFT)
	{
		m_sprite.setPosition(m_entity.position());
	}

	Mob::~Mob(){}

	void Mob::update(const World& world,float elapsedTime)
	{
		m_sprite.update();
		m_entity.update(world,elapsedTime);
		m_sprite.setPosition(m_entity.position());
	}

	sf::Drawable* Mob::drawable() const
	{
		return (sf::Drawable*)&m_sprite;
	}

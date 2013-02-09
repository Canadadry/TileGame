/*
 * Mob.h
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

#ifndef MOB_H_
#define MOB_H_

#include "../2DGameEngine/AnimatedTile.h"
#include "../MyPhisics/Entity.h"

class World;

class Mob
{
public:
	Mob(int x,int y,int tile_size, const EntityBehavior& behavior= EntityBehavior::MOB);
	virtual ~Mob();
	virtual void update(const World& world,float elapsedTime);
	virtual sf::Drawable* drawable() const;

protected:
	Entity m_entity;
	AnimatedTile m_sprite;
	const int m_tile_size;
	Entity::Direction m_direction;
};


#endif /* MOB_H_ */

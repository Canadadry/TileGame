/*
 * Entity.h
 *
 * TileGame - Copyright (c) 19 déc. 2012 - Jerome Mourey
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
 *  Created on: 19 déc. 2012
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <SFML/System/Vector2.hpp>
#include "Body.h"
#include "EntityBehavior.h"
class World;

class Entity : public Body
{
public :
	enum Direction{
		UP = -90,
		DOWN = 90,
		LEFT = 180,
		RIGHT = 0
	};
	enum StateFlag{
		MOVING  = 1<<0,
		RUNNING = 1<<1,
		JUMPING = 1<<2,
		FALLING = 1<<3
	};

	Entity(int pos_x,int pos_y,const EntityBehavior& behavior);
	virtual void step(World& world,int elapsedTimeMS);

	void move(Entity::Direction dir);
	void running(bool enable);
	void jump();
	void stop();

	int state() const;
	Entity::Direction direction() const;

private:
	const EntityBehavior m_behavior;
	sf::Vector2f         m_speed;
	sf::Vector2f         m_max_speed;
	sf::Vector2f         m_acceleration;
	Entity::Direction    m_direction;
	int                  m_state;

	void falling(World& world,int elapsedTimeMS);

};


#endif /* ENTITY_H_ */

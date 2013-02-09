/*
 * Entity.cpp
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

#include "Entity.h"
#include "World.h"
#include <cmath>

Entity::Entity(int pos_x,int pos_y,const EntityBehavior& behavior)
: Body(0,0,0,0)
, m_behavior    (behavior)
, m_speed       (0.0,0.0)
, m_max_speed   (behavior.mvt_speed,behavior.max_falling_speed)
, m_acceleration(m_behavior.mvt_acc,m_behavior.gravity)
, m_direction   (Entity::UP)
, m_state       (0)
{
	setPosition(sf::Vector2f(pos_x,pos_y));
}

void Entity::move(Direction dir)
{
	m_state = m_state | Entity::MOVING;
	m_direction = dir;
}

void Entity::stop()
{
	m_state = m_state & (~(Entity::MOVING | Entity::RUNNING));
}

int Entity::state() const
{
	return m_state;
}

Entity::Direction Entity::direction() const
{
	return m_direction;
}

void Entity::running(bool enable)
{
	if(enable)
	{
		m_state = m_state  | Entity::RUNNING;
	}
	else
	{
		m_state = m_state  & ~Entity::RUNNING;
	}
	m_max_speed.x = enable ? m_behavior.running_speed : m_behavior.mvt_speed;
}

void Entity::jump()
{
	if((m_state & Entity::JUMPING) != Entity::JUMPING)
	{
		if(m_speed.y < 1.0)
		{
			m_state = m_state  | Entity::JUMPING;
			m_speed.y = -m_behavior.jump_impulse;

		}
	}
}

void Entity::step(World& world, int elapsedTimeMS)
{

	sf::Vector2f      pos = position();
	sf::Vector2f last_pos = position();
	if((m_state & Entity::MOVING) == Entity::MOVING)
	{
		switch(m_direction)
		{
			case Entity::UP    : break;
			case Entity::DOWN  : break;
			case Entity::LEFT  : m_speed.x -= m_acceleration.x*elapsedTimeMS; break;
			case Entity::RIGHT : m_speed.x += m_acceleration.x*elapsedTimeMS; break;
		}

		if(fabs(m_speed.x) > fabs(m_max_speed.x) )
		{
			m_speed.x = (m_speed.x > 0)? m_max_speed.x:-m_max_speed.x;
		}
	}
	else
	{
		m_speed.x*=0.5;
	}

	pos.x += m_speed.x*elapsedTimeMS;

	setPosition(pos);
	if(world.checkBodyCollision(*this))
	{

		setPosition(last_pos);
		m_speed.x = 0.0;
	}

	falling(world,elapsedTimeMS);

}


void Entity::falling(World& world,int elapsedTimeMS)
{
	sf::Vector2f      pos = position();
	sf::Vector2f last_pos = position();

	m_speed.y += m_behavior.gravity*elapsedTimeMS;

	if(fabs(m_speed.y) > fabs(m_max_speed.y) )
	{
		m_speed.y = (m_speed.y > 0)? m_max_speed.y:-m_max_speed.y;
	}

	pos.y += m_speed.y*elapsedTimeMS;

	setPosition(pos);
	if(world.checkBodyCollision(*this))
	{
		setPosition(last_pos);
		if(m_speed.y > 0 ) 	m_state = m_state  & ~Entity::JUMPING;
		m_speed.y = 0.0;
	}
}


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

const EntityBehavior EntityBehavior::PLAYER = {
		/* gravity          */ 40*32,
		/* max_falling_speed*/ 20*32,
		/* mvt_speed        */ 3*32,
		/* running_speed    */ 7*32,
		/* mvt_acc          */ 9*32,
		/* size             */ 0.6,
		/* jump_impulse     */ 15*32,
};

const EntityBehavior EntityBehavior::MOB = {
		/* gravity          */ 40*32,
		/* max_falling_speed*/ 20*32,
		/* mvt_speed        */ 3*32,
		/* running_speed    */ 9*32,
		/* mvt_acc          */ 9*32,
		/* size             */ 0.6,
		/* jump_impulse     */ 15*32,
};


Entity::Entity(int pos_x,int pos_y,int size,const EntityBehavior& behavior)
: m_pos(pos_x,pos_y)
, m_body(0,0,size,size)
, m_moving_max_speed(behavior.mvt_speed)
, m_moving_speed(0)
, m_moving_acceleration(behavior.mvt_acc)
, m_falling_speed(0)
, m_max_falling_speed(behavior.max_falling_speed)
, m_max_current_speed(m_moving_max_speed)
, m_y_gravity(behavior.gravity)
, m_direction(Entity::UP)
, m_moving(false)
, m_jumping(false)
, m_running(false)
, m_jump_speed(0.0)
, m_behavior(behavior)
{
	m_body.setOrigin(sf::Vector2f(size/2,size/2));
}

sf::Vector2f Entity::position() const
{
	return m_pos;
}

void Entity::move(Direction dir)
{
	m_moving = true;
	m_direction = dir;
}

void Entity::stop()
{
	m_moving = false;
}

Entity::State Entity::state() const
{
	if(m_jumping) return Entity::JUMPING;
	if(fabs(m_falling_speed) > 1.0)  return Entity::FALLING;
	if( fabs(m_moving_speed) > m_behavior.mvt_speed ) return Entity::RUNNING;
	if( fabs(m_moving_speed) > 1.0 ) return Entity::MOVING;
	return Entity::STOPED;
}


Entity::Direction Entity::direction() const
{
	return m_direction;
}

void Entity::running(bool enable)
{
	m_running = enable;
	m_max_current_speed = m_running ? m_behavior.running_speed : m_behavior.mvt_speed;
}

void Entity::jump()
{
	if(m_jumping == false)
	{
		if(m_falling_speed < 1.0)
		{
			m_jumping = true;
			m_jump_speed = m_behavior.jump_impulse;
		}
	}
}

void Entity::update(const World& world,float elapsedTime)
{

	sf::Vector2f pos = m_pos;
	if(m_moving)
	{
		switch(m_direction)
		{
			case Entity::UP    : break;
			case Entity::DOWN  : break;
			case Entity::LEFT  : m_moving_speed -= m_moving_acceleration*elapsedTime; break;
			case Entity::RIGHT : m_moving_speed += m_moving_acceleration*elapsedTime; break;
		}

		if(fabs(m_moving_speed) > fabs(m_max_current_speed) )
		{
			m_moving_speed = (m_moving_speed > 0)? m_max_current_speed:-m_max_current_speed;
		}
	}
	else
	{
		m_moving_speed*=0.5;
	}


	pos.x += m_moving_speed*elapsedTime;

	m_body.setPosition(pos);
	if(!world.bodyColliding(m_body)) m_pos = pos;
	else                             m_moving_speed = 0.0;

	jumping(world,elapsedTime);
	falling(world,elapsedTime);

	m_body.setPosition(m_pos);

}


void Entity::jumping(const World& world,float elapsedTime)
{
	if(m_jumping)
	{
		m_jump_speed -= m_y_gravity* elapsedTime;
		if(m_jump_speed <= 0)
		{
			m_jump_speed = 0.0;
		}
		sf::Vector2f pos = m_pos;
		pos.y -= m_jump_speed*elapsedTime;

		m_body.setPosition(pos);
		if(!world.bodyColliding(m_body)) m_pos = pos;
		else                             m_jump_speed = 0.0;
	}
}

void Entity::falling(const World& world,float elapsedTime)
{
	if(m_jump_speed <=0)
	{
		sf::Vector2f pos = m_pos;
		m_falling_speed += m_y_gravity* elapsedTime;
		if(m_falling_speed > m_max_falling_speed)
		{
			m_falling_speed = m_max_falling_speed;
			//			printf("m_max_falling_speed\n");
		}

		pos.y += m_falling_speed*elapsedTime;
		m_body.setPosition(pos);
		if(!world.bodyColliding(m_body)) m_pos = pos;
		else
		{
			//			if(m_jumping){
			//				printf("falling_speed : %lf\n",m_falling_speed);
			//			}
			m_jumping = false;
			m_falling_speed = 0.0;
		}
	}
}


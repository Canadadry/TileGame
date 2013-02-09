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

struct EntityBehavior{
	const int   gravity          ;
	const int   max_falling_speed;
	const int   mvt_speed        ;
	const int   running_speed    ;
	const int   mvt_acc          ;
	const float size             ;
	const int   jump_impulse     ;

	static const EntityBehavior PLAYER;
	static const EntityBehavior MOB;
};




class TileMap;
class World;

class Entity
{
public :
	enum Direction{
		UP = -90,
		DOWN = 90,
		LEFT = 180,
		RIGHT = 0
	};
	enum State{
		STOPED,
		MOVING,
		RUNNING,
		JUMPING,
		FALLING
	};


	Entity(int pos_x,int pos_y,int size,const EntityBehavior& behavior);

	void move(Entity::Direction dir);
	void running(bool enable);
	void jump();
	void stop();

	Entity::State state() const;
	Entity::Direction direction() const;

	void update(const World& world,float elapsedTime);

	sf::Vector2f position() const;

private:
	sf::Vector2f m_pos;
	Body m_body;
	float m_moving_max_speed;
	float m_moving_speed;
	float m_moving_acceleration;
	float m_falling_speed;
	float m_max_falling_speed;
	float m_max_current_speed;
	float m_y_gravity;
	Entity::Direction   m_direction;
	bool  m_moving;
	bool  m_jumping;
	bool  m_running;
	float m_jump_speed;

	const EntityBehavior m_behavior;

	void jumping(const World& world,float elapsedTime);
	void falling(const World& world,float elapsedTime);

};


#endif /* ENTITY_H_ */

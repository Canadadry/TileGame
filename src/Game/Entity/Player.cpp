/*
 * Player.cpp
 *
 * TileGame - Copyright (c) 4 févr. 2013 - Jerome Mourey
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
 *  Created on: 4 févr. 2013
 */

#include "Player.h"
#include <SFML/Window/Event.hpp>


extern std::string path;

Player::Player(int x,int y,int tile_size)
: Mob(x,y,tile_size,EntityBehavior::PLAYER)
{
	m_texture.loadFromFile(path+"/mario.png");
	m_sprite.setTileSet(m_texture,5,2);
	int anim_stopped_left[] = {0};
	int anim_moving_left[] = {0,1,2,1};
	int anim_jumping_left[] = {3};
	int anim_stopped_right[] = {5};
	int anim_moving_right[] = {5,6,7,6};
	int anim_jumping_right[] = {8};
	std::vector<int> anim ;
	anim.assign(anim_stopped_left,anim_stopped_left+1);
	m_sprite.appendAnimDesc(anim,100);
	anim.assign(anim_moving_left,anim_moving_left+4);
	m_sprite.appendAnimDesc(anim,100);
	m_sprite.appendAnimDesc(anim,70);
	anim.assign(anim_jumping_left,anim_jumping_left+1);
	m_sprite.appendAnimDesc(anim,100);

	anim.assign(anim_stopped_right,anim_stopped_right+1);
	m_sprite.appendAnimDesc(anim,100);
	anim.assign(anim_moving_right,anim_moving_right+4);
	m_sprite.appendAnimDesc(anim,100);
	m_sprite.appendAnimDesc(anim,70);
	anim.assign(anim_jumping_right,anim_jumping_right+1);
	m_sprite.appendAnimDesc(anim,100);
	m_sprite.useAnim(0);
	m_sprite.setOrigin(8,24);

}

Player::~Player(){}

sf::Vector2f Player::position() const
{
	return m_sprite.getPosition();
}

void Player::handleEvent(const sf::Event& event)
{
	if(event.type == sf::Event::KeyPressed )
	{
		if(event.key.code == sf::Keyboard::Left)
		{
			if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				m_entity.move(Entity::LEFT);
			}
		}
		else if(event.key.code == sf::Keyboard::C)
		{
			m_entity.running(true);
		}
		else if(event.key.code == sf::Keyboard::Right)
		{
			if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				m_entity.move(Entity::RIGHT);
			}
		}
		else if(event.key.code == sf::Keyboard::Space)
		{
			m_entity.jump();
		}
	}
	else if(event.type == sf::Event::KeyReleased)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				m_entity.move(Entity::LEFT);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				m_entity.move(Entity::RIGHT);
			}
		}
		else if(event.key.code == sf::Keyboard::C)
		{
			m_entity.running(false);
		}
		else
		{
			m_entity.stop();
		}
	}
}

void Player::update(const World& world,float elapsedTime)
{
	Mob::update(world,elapsedTime);

	int line = 0;
	if(m_entity.direction() == Entity::LEFT) line = 1;
	if(m_entity.state() == Entity::STOPED)
	{
		m_sprite.useAnim(0+4*line);
	}
	else if(m_entity.state() == Entity::JUMPING)
	{
		m_sprite.useAnim(3+4*line);
	}
	else
	{
		if(m_entity.state() == Entity::RUNNING)
		{
			m_sprite.useAnim(2+4*line);
		}
		else
		{
			m_sprite.useAnim(1+4*line);
		}
	}
}

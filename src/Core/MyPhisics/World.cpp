/*
 * World.cpp
 *
 * TileGame - Copyright (c) 26 déc. 2012 - Jerome Mourey
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
 *  Created on: 26 déc. 2012
 */

#include "World.h"
#include "Body.h"
#include "Entity.h"
#include  "CollisionHandler.h"

World::World(CollisionHandler* collisionHandler)
: m_collisionHandler(collisionHandler)
{
	if(m_collisionHandler == 0)
	{
		m_collisionHandler = this;
	}
}


void World::appendBody(Body* body)
{
	//TODO Check if updatable then push_front instead of pushing_back
	m_bodies.push_back(body);
	Entity* entity = dynamic_cast<Entity*>(body);
	if(entity)
	{
		m_entities.push_back(entity);
	}
}

void World::removeBody(Body* body)
{
	m_bodies.remove(body);
	Entity* entity = dynamic_cast<Entity*>(body);
	if(entity)
	{
		m_entities.remove(entity);
	}
}

void World::clearBodies()
{
	m_bodies.clear();
	m_entities.clear();
}

typedef std::list<Body*>::iterator   bIter;
typedef std::list<Entity*>::iterator eIter;

void World::step(int elapsedTimeMS)
{
	//TODO only update body that can move ie Entities
	for(eIter it = m_entities.begin() ; it != m_entities.end() ; it++ )
	{
		(*it)->step(*this,elapsedTimeMS);
	}
}


bool World::checkBodyCollision(Body& body)
{
	bool ret = false;
	for(bIter it = m_bodies.begin() ; it != m_bodies.end() ; it++ )
	{
		if(&body == *it) continue;
		if( body.intersects(**it))
		{
			ret = true;
			m_collisionHandler->handleCollision(&body,*it);
		}
	}

	return ret;
}

void World::handleCollision(Body* body1, Body* body2)
{
}



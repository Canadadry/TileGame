/*
 * World.h
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

#ifndef WORLD_H_
#define WORLD_H_

#include <list>
#include "CollisionHandler.h"

class Body;
class Entity;

class World : public CollisionHandler
{
public:
	World(CollisionHandler* collisionHandler = 0);
	void appendBody(Body* body);
	void removeBody(Body* body);
	void clearBodies();

	void step(int elapsedTimeMS);
	bool checkBodyCollision(Body& body);

	virtual void handleCollision(Body* body1,Body* body2);

private:
	CollisionHandler* m_collisionHandler;
	std::list<Body*> m_bodies;
	std::list<Entity*> m_entities;
};

#endif /* WORLD_H_ */

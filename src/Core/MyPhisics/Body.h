/*
 * Body.h
 *
 * TileGame - Copyright (c) 25 déc. 2012 - Jerome Mourey
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
 *  Created on: 25 déc. 2012
 */

#ifndef BODY_H_
#define BODY_H_

#include <SFML/System/Vector2.hpp>
#include  <SFML/Graphics/Rect.hpp>

class World;

class Body
{
public:
	Body(float left,float top, float width, float height);
	Body(float left,float top, float width, float height, float xOrigin, float yOrigin);
	virtual ~Body(){}
	void setOrigin(sf::Vector2f origin);
	void setPosition(sf::Vector2f position);
	void setSize(sf::Vector2f size);
	sf::Vector2f position() const;

	virtual bool intersects(const Body& body)const;
	virtual void step(World& world,int elapsedTimeMS){}

protected:
	sf::FloatRect m_aabb;
	sf::Vector2f m_origin;


};

#endif /* BODY_H_ */

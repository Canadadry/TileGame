/*
 * Body.cpp
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

#include "Body.h"

Body::Body(float left,float top, float width, float height)
: m_aabb(left,top,width,height)
, m_origin(0.0,0.0)
{}

Body::Body(float left,float top, float width, float height, float xOrigin, float yOrigin)
: m_aabb(left,top,width,height)
, m_origin(xOrigin,yOrigin)
{}

void Body::setOrigin(sf::Vector2f origin)
{
	m_origin = origin;
}

void Body::setPosition(sf::Vector2f position)
{
	m_aabb.left = position.x - m_origin.x;
	m_aabb.top  = position.y - m_origin.y;
}

void Body::setSize(sf::Vector2f size)
{
	m_aabb.width = size.x;
	m_aabb.height = size.y;
}

sf::Vector2f Body::position() const
{
	return sf::Vector2f(m_aabb.left,m_aabb.top) - m_origin;
}

bool Body::intersects(const Body& body)const
{
	return m_aabb.intersects(body.m_aabb);
}




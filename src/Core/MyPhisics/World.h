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

#include <vector>

class Body;

class World
{
public:
	void fillWorld(unsigned int width,unsigned int height,unsigned int* data,unsigned int tile_size);
	bool bodyColliding(const Body& body) const;

	std::vector<Body*> world;
};

#endif /* WORLD_H_ */

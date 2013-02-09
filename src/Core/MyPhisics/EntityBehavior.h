/*
 * EntityBehavior.h
 *
 * TileGame - Copyright (c) 9 févr. 2013 - Jerome Mourey
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
 *  Created on: 9 févr. 2013
 */

#ifndef ENTITYBEHAVIOR_H_
#define ENTITYBEHAVIOR_H_

struct EntityBehavior{
	EntityBehavior();
	const float   gravity          ;
	const float   max_falling_speed;
	const float   mvt_speed        ;
	const float   running_speed    ;
	const float   mvt_acc          ;
	const float   size             ;
	const float   jump_impulse     ;

//	static const EntityBehavior PLAYER;
//	static const EntityBehavior MOB;
};


#endif /* ENTITYBEHAVIOR_H_ */

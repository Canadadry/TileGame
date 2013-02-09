/*
 * EntityBehavior.cpp
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

#include "EntityBehavior.h"
#include <cmath>

const float max_height_jump = 16*6.5;

EntityBehavior::EntityBehavior()
:gravity          (4.5*32.0 / 100000.0  )
,max_falling_speed(20.0*32.0 / 1000.0  )
,mvt_speed        (3.0 *32.0 / 1000.0  )
,running_speed    (7.0 *32.0 / 1000.0  )
,mvt_acc          (9.0 *32.0 / 1000.0  )
,size             (0.6                 )
,jump_impulse     (sqrt(2*gravity*max_height_jump)) //20.0*32.0 / 1000.0  )  //hauteur max = 0.5*jump_impulse^2/gravity en pix
{}

//const EntityBehavior EntityBehavior::PLAYER(
//		/* gravity          */ 40*32 / 1000,
//		/* max_falling_speed*/ 20*32 / 1000,
//		/* mvt_speed        */ 3*32 / 1000,
//		/* running_speed    */ 7*32 / 1000,
//		/* mvt_acc          */ 9*32 / 1000,
//		/* size             */ 0.6 ,
//		/* jump_impulse     */ 15*32 / 1000,
//);
//
//const EntityBehavior EntityBehavior::MOB = {
//		/* gravity          */ 40*32 / 1000,
//		/* max_falling_speed*/ 20*32 / 1000,
//		/* mvt_speed        */ 3*32 / 1000,
//		/* running_speed    */ 9*32 / 1000,
//		/* mvt_acc          */ 9*32 / 1000,
//		/* size             */ 0.6,
//		/* jump_impulse     */ 15*32 / 1000,
//};




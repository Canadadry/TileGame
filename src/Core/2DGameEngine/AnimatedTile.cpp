/*
 * AnimatedTile.cpp
 *
 * TileGame - Copyright (c) 3 févr. 2013 - Jerome Mourey
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
 *  Created on: 3 févr. 2013
 */

#include "AnimatedTile.h"

AnimatedTile::AnimatedTile()
: m_current_anim(0)
, m_animList()
{
	stop();
}

AnimatedTile::~AnimatedTile(){}

void AnimatedTile::appendAnimDesc(const std::vector<int>& frameList, int delay)
{
	if(frameList.size() == 0) return;

	m_animList.push_back(AnimDesc());
	m_animList.back().frameList = frameList;
	m_animList.back().delay     = delay;

	if(m_animList.size() == 1)
	{
		setDelay(m_animList[m_current_anim].delay);
		reset();
	}
}

unsigned int AnimatedTile::getSize() const
{
	if(m_animList.size() == 0) return 0;
	return m_animList[m_current_anim].frameList.size();
}

void AnimatedTile::frameChanged()
{
	if(m_animList.size() == 0) return;
	setID(m_animList[m_current_anim].frameList[currentFrame()]);
}

void AnimatedTile::useAnim(unsigned int animId)
{
	if(animId < m_animList.size() && animId != m_current_anim)
	{
		m_current_anim = animId;
		if(m_animList[m_current_anim].frameList.size()== 1 )
		{
			stop();
		}
		else
		{
			setDelay(m_animList[m_current_anim].delay);
			reset();
		}
	}
}





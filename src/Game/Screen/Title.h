/*
 * Title.h
 *
 * TileGame - Copyright (c) 6 févr. 2013 - Jerome Mourey
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
 *  Created on: 6 févr. 2013
 */

#ifndef TITLE_H_
#define TITLE_H_

#include "../../Core/GameCore/Screen.h"
#include <SFML/Graphics/Sprite.hpp>

namespace sf{
	class Event;
	class RenderTarget;
	class Texture;
}



class Title : public Screen
{
public:
	Title();
	virtual ~Title();

	virtual void handleEvent(const sf::Event& Event);
    virtual void update(int elapsedTimeMS);

protected:
    virtual void render(sf::RenderTarget* screen_surface);


private:

	Screen* m_game;
	sf::Texture* m_texture;
	sf::Sprite   m_sprite;

};

#endif /* TITLE_H_ */

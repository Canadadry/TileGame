/*
 * Title.cpp
 *
 * TileGame - Copyright (c) 6 fŽvr. 2013 - Jerome Mourey
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
 *  Created on: 6 fŽvr. 2013
 */

#include "Title.h"
#include "Game.h"

extern std::string path;

Title::Title()
{
	m_game = new Game(this);
//	m_transition = new Transition;
//	m_transition->transitionTo = m_game;
	m_texture = new sf::Texture;
	m_texture->loadFromFile(path+"/title.png");
	m_sprite.setTexture(*m_texture);
}

Title::~Title()
{
	delete m_game;
	delete m_texture;
}

void Title::render(sf::RenderTarget* screen_surface)
{
	screen_surface->draw(m_sprite);
}

void Title::handleEvent(const sf::Event& event)
{
	if(event.type == sf::Event::KeyPressed)
	{
		setNextScreen(m_game);
	}
}

void Title::update(int elapsedTimeMS)
{

}



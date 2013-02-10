/*
 * Game.h
 *
 * TileGame - Copyright (c) 5 févr. 2013 - Jerome Mourey
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
 *  Created on: 5 févr. 2013
 */

#ifndef GAME_H_
#define GAME_H_

#include "Core/GameCore/Screen.h"

#include <SFML/Graphics.hpp>

#include "Core/2DGameEngine/DrawableGroupe.h"
#include "Core/2DGameEngine/TileMap.h"
#include "Core/2DGameEngine/AnimatedTile.h"

#include "Core/GameCore/Scene2D.h"
#include "Core/GameCore/ScreenEffect.h"

#include "Core/MyPhisics/Entity.h"
#include "Core/MyPhisics/World.h"
#include "Core/MyPhisics/CollisionHandler.h"

#include "Game/Entity/Player.h"
#include "Game/Entity/Goomba.h"

class Game: public Screen, public CollisionHandler
{
public:
	Game(Screen* previous = 0);
	virtual ~Game();

	virtual void handleEvent(const sf::Event& Event);
    virtual void update(int elapsedTimeMS);
	virtual void entering();

	virtual void handleCollision(Body* body1,Body* body2);
protected:
    virtual void render(sf::RenderTarget* screen_surface);
    void killBody();
private:
	void leaving();

	ScreenEffect* m_enteringEffect;
	Scene2D* m_scene2D;
    Screen* m_previous;
	DrawableGroupe m_map;
	DrawableGroupe m_bg_map;
	sf::Texture m_bg_text;
	sf::Sprite  m_bg;
	sf::Sprite  m_bg2;

	std::vector<sf::Texture*> m_tilesets;
	std::vector<TileMap*> m_tilemap;

	Player* m_player;
	World m_world;
	std::vector<Mob*> m_mobs;

	int m_width_in_tile;
	int m_height_in_tile;

	bool m_playerDead;
	Body* m_bodyToKill;

};

#endif /* GAME_H_ */

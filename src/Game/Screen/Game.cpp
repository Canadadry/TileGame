/*
 * Game.cpp
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

#include "Game.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <cmath>


extern int screen_width;
extern int screen_height;
extern int tile_size;
extern std::string path;


Game::Game(Screen* previous)
: m_enteringEffect(0)
, m_scene2D(0)
, m_previous(previous)
{

	m_scene2D = new Scene2D(path+"/level_fat.tmx");
	if(!m_scene2D->loadSuccessfull()) return ;

	m_width_in_tile = m_scene2D->width_in_tile;
	m_height_in_tile = m_scene2D->height_in_tile;


	m_bg_text.loadFromFile(path+"/bg.png");
	m_bg.setTexture(m_bg_text);
	m_bg2.setTexture(m_bg_text);
	m_bg2.setPosition(m_bg_text.getSize().x,0);
	m_bg_map.push_back(&m_bg);
	m_bg_map.push_back(&m_bg2);

	m_map.setPosition(screen_width*m_scene2D->tile_size/2, screen_height*m_scene2D->tile_size/2);

	m_tilesets.reserve(m_scene2D->tilesetName.size());
	for(unsigned int i=0;i<m_scene2D->tilesetName.size();i++)
	{
		sf::Texture* text = new sf::Texture();
		text->loadFromFile(path+"/"+m_scene2D->tilesetName[i]);
		m_tilesets.push_back(text);

	}

	m_tilemap.reserve(m_scene2D->layers.size());
	for(unsigned int i=0;i<m_scene2D->layers.size();i++)
	{
		Scene2D::Layer& layer = *m_scene2D->layers[i];
		sf::Texture& tileset = *m_tilesets[layer.tilesetId];

		TileMap* map = new TileMap();
		map->setTileSet(tileset,tileset.getSize().x/m_scene2D->tile_size,tileset.getSize().y/m_scene2D->tile_size);
		map->setData(m_scene2D->width_in_tile,m_scene2D->height_in_tile,(const unsigned int*)&(layer.data[0]));

		m_tilemap.push_back(map);

	}
	m_world.fillWorld(m_scene2D->width_in_tile,m_scene2D->height_in_tile,(unsigned int*)&(m_scene2D->collision[0]),m_scene2D->tile_size);

}

Game::~Game()
{
	for(unsigned int i=0;i<m_tilemap.size();i++)
	{
		delete m_tilemap[i];
	}
	for(unsigned int i=0;i<m_tilesets.size();i++)
	{
		delete m_tilesets[i];
	}
	delete m_scene2D;
}

void Game::entering()
{
	for(unsigned int i=0;i<m_tilemap.size();i++)
	{
		m_map.push_back(m_tilemap[i]);
	}
	m_player = new Player(m_scene2D->player.x,m_scene2D->player.y,m_scene2D->tile_size);
	m_map.push_back(m_player->drawable());

	for(unsigned int i=0;i<m_scene2D->entities.size();i++)
	{
		Scene2D::Entity& entity = m_scene2D->entities[i];
		Mob* mob = new Goomba(entity.x,entity.y,m_scene2D->tile_size);
		m_mobs.push_back(mob);
		m_map.push_back(mob->drawable());
	}

	m_enteringEffect= new ScreenEffect(this, 1000,sf::Vector2f( (float)m_scene2D->player.x/(float)screen_width
			                                                   ,1.0-(float)m_scene2D->player.y/(float)screen_height));

	m_enteringEffect->setFragmentProgram(path+"/pixelate.frag");
	playEffect(m_enteringEffect);
}


void Game::leaving()
{
	for(unsigned int i=0;i<m_mobs.size();i++)
	{
		delete m_mobs[i];
	}
	m_mobs.clear();
	delete m_player;
	m_map.clear();

	setNextScreen(m_previous);
}

void Game::handleEvent(const sf::Event& Event)
{
	m_player->handleEvent(Event);
}

void Game::update(float elapsedTime)
{
	if(m_enteringEffect != 0)
	{
		if(m_enteringEffect->isPlaying())
		{
			m_enteringEffect->update(elapsedTime);
		}
		else
		{
			delete m_enteringEffect;
			m_enteringEffect = 0;
			stopEffect();
		}
	}
	else if(elapsedTime >0)
	{
		for(unsigned int i = 0; i< m_mobs.size();i++)
		{
			m_mobs[i]->update(m_world,((float)elapsedTime)/1000.0);
		}
		m_player->update(m_world,((float)elapsedTime)/1000.0);
	}

	sf::Vector2f mapOrigin = m_player->position()/(float)tile_size;

	if(m_player->position().y > (screen_height+1)*tile_size ) leaving();

	if(m_width_in_tile <= screen_width )					    	  mapOrigin.x = m_width_in_tile/2;
	else if(mapOrigin.x< screen_width/2)                              mapOrigin.x = screen_width/2;
	else if(mapOrigin.x> (m_width_in_tile - screen_width/2))          mapOrigin.x = (m_width_in_tile - screen_width/2);

	if(m_height_in_tile <= screen_height )				              mapOrigin.y = m_height_in_tile/2;
	else if(mapOrigin.y< screen_height/2)                             mapOrigin.y = screen_height/2;
	else if(mapOrigin.y> (m_height_in_tile - screen_height/2))        mapOrigin.y = (m_height_in_tile - screen_height/2);
	m_map.setOrigin(mapOrigin*(float)tile_size);

	float offset_map = fmod( mapOrigin.x*(float)tile_size*1.2 , m_bg_text.getSize().x);
	m_bg_map.setPosition(-offset_map,0);

}

void Game::render(sf::RenderTarget* screen_surface)
{
//	if(m_transition)
//	{
//		m_transition->display(screen_surface);
//	}
	screen_surface->draw(m_bg_map);
	screen_surface->draw(m_map);
}



//
//  Game.cpp
//  LD37
//
//  Created by reworks on 10/12/2016.
//  Copyright (c) 2016 reworks. All rights reserved.
//

#include <re/app/World.hpp>
#include <re/graphics/Window.hpp>
#include <re/services/Config.hpp>
#include <re/services/vfs/VFS.hpp>
#include <re/services/ServiceLocator.hpp>
#include <re/systems/RenderSystem.hpp>
#include <re/systems/AudioSystem.hpp>
#include <re/systems/PhysicsSystem.hpp>

#include "systems/MoveSystem.hpp"

#include "Game.hpp"
#include "Menu.hpp"

using namespace re;

std::shared_ptr<State> Game::m_gameState = std::make_shared<Game>();

std::shared_ptr<State> Game::Inst()
{
	return m_gameState;
}

Game::~Game()
{
}

void Game::LoadResources()
{
	m_window = Locator::Get<Window>();
	m_world = Locator::Get<World>();
	m_vfs = Locator::Get<VFS>();
	m_config = Locator::Get<ConfigReader>();

	m_world->Register("states/gamestate.lua");

	m_world->Get<RenderSystem>()->AutoSubmit(m_world);
	m_world->Get<MoveSystem>()->AutoSubmit(m_world);
	m_world->Get<AudioSystem>()->AutoSubmit(m_world);
	m_world->Get<PhysicsSystem>()->AutoSubmit(m_world);

	if (m_doOnce)
	{
		m_map.Load("bin/Release/assets/maps/oneroom.tmx");
		m_theme = std::make_shared<tgui::Theme>("bin/Release/assets/scripts/ui/themes/black.txt");
		m_doOnce = false;
	}

	m_world->Get<PhysicsSystem>()->SubmitTiles(&m_map);
	m_world->Get<AudioSystem>()->GetMusic("ball.bg")->play();
}

void Game::UnloadResources()
{
	m_gui.removeAllWidgets();
	
	m_world->Get<RenderSystem>()->Clean();
	m_world->Get<MoveSystem>()->Clean();
	m_world->Get<AudioSystem>()->Clean();
	m_world->Get<PhysicsSystem>()->Clean();

	m_world->Clean();
}

void Game::Event()
{
	while (m_window->pollEvent(m_window->m_event))
	{
		switch (m_window->m_event.type)
		{
		case sf::Event::Closed:
			m_window->close();
			break;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
	
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
	
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		
	}
}

void Game::Update(sf::Time dt)
{
	m_map.Update(dt);
	
	m_world->Get<PhysicsSystem>()->Update(dt);
}

void Game::Render()
{
	m_window->clear(sf::Color::Black);

	m_window->draw(m_map);
	m_world->Get<RenderSystem>()->Render(m_window);
	
	m_window->display();
}
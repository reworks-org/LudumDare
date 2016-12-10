//
//  Load.cpp
//  LD37
//
//  Created by reworks on 10/12/2016.
//  Copyright (c) 2016 reworks. All rights reserved.
//

#include <re/app/World.hpp>
#include <re/services/Config.hpp>
#include <re/graphics/Window.hpp>
#include <re/services/vfs/VFS.hpp>
#include <re/systems/RenderSystem.hpp>
#include <re/services/ServiceLocator.hpp>

#include "gamesystems/MoveSystem.hpp"

#include "Load.hpp"
#include "Menu.hpp"

using namespace re;

std::shared_ptr<State> Load::m_loadState = std::make_shared<Load>();

std::shared_ptr<State> Load::Inst()
{
	return m_loadState;
}

Load::~Load()
{
}

void Load::LoadResources()
{
	m_window = Locator::Get<Window>();
	m_world = Locator::Get<World>();
	m_vfs = Locator::Get<VFS>();
	m_config = Locator::Get<ConfigReader>();

	m_world->Register("states/loadstate.lua");
	m_world->Get("loadscreen").Get<SpriteComponent>()->setColor(sf::Color(255, 255, 255, m_alpha));

	m_world->Get<RenderSystem>()->AutoSubmit(m_world);
}

void Load::UnloadResources()
{
	m_world->Get<RenderSystem>()->Clean();
	m_world->Clean();
}

void Load::Event()
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_window->close();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		Locator::Get<StateManager>()->ChangeState(Menu::Inst());
	}
}

void Load::Update(sf::Time dt)
{
	m_world->Update(dt);
	
	m_timePassed += dt;

	if (m_timePassed > sf::seconds(1))
	{
		m_alpha -= 3;

		if (m_alpha < 0)
		{
			m_alpha = 0;
		}

		m_world->Get("loadscreen").Get<SpriteComponent>()->setColor(sf::Color(255, 255, 255, m_alpha));

		if (m_alpha <= 0)
		{
			Locator::Get<StateManager>()->ChangeState(Menu::Inst());
		}
	}
}

void Load::Render()
{
	m_window->clear(sf::Color::Black);

	m_world->Get<RenderSystem>()->Render(m_window);

	m_window->display();
}
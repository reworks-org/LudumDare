//
//  Menu.cpp
//  LD37
//
//  Created by reworks on 10/12/2016.
//  Copyright (c) 2016 reworks. All rights reserved.
//

#include <re/app/World.hpp>
#include <re/graphics/Window.hpp>
#include <re/services/vfs/VFS.hpp>
#include <re/services/Config.hpp>
#include <re/systems/RenderSystem.hpp>

#include "Menu.hpp"
#include "Game.hpp"

using namespace re;

std::shared_ptr<State> Menu::m_menuState = std::make_shared<Menu>();

std::shared_ptr<State> Menu::Inst()
{
	return m_menuState;
}

Menu::~Menu()
{
}

void Menu::LoadResources()
{
	m_window = Locator::Get<Window>();
	m_world = Locator::Get<World>();
	m_vfs = Locator::Get<VFS>();
	m_config = Locator::Get<ConfigReader>();

	m_world->Register("states/menustate.lua");

	m_world->Get<RenderSystem>()->AutoSubmit(m_world);

	m_gui.setWindow(*(m_window));

	if (m_doOnce)
	{
		m_theme = std::make_shared<tgui::Theme>("bin/Release/assets/scripts/ui/themes/black.txt");
		m_doOnce = false;
	}

	tgui::Button::Ptr button_new = tgui::loadButtonWithScript(m_theme, "ui/menu_new.lua");
	tgui::Button::Ptr button_highscore = tgui::loadButtonWithScript(m_theme, "ui/menu_highscore.lua");
	tgui::Button::Ptr button_exit = tgui::loadButtonWithScript(m_theme, "ui/menu_exit.lua");
	
	button_new->connect("pressed", []() { Locator::Get<StateManager>()->ChangeState(Game::Inst()); });
	button_highscore->connect("pressed", []() {});
	button_exit->connect("pressed", []() { Locator::Get<Window>()->close(); });
	
	m_gui.add(button_new, "menu_new");
	m_gui.add(button_highscore, "menu_highscore");
	m_gui.add(button_exit, "menu_exit");
}

void Menu::UnloadResources()
{
	m_gui.removeAllWidgets();

	m_world->Get<RenderSystem>()->Clean();
	m_world->Clean();
}

void Menu::Event()
{
	while (m_window->pollEvent(m_window->m_event))
	{
		switch (m_window->m_event.type)
		{
		case sf::Event::Closed:
			m_window->close();
			break;
		}

		m_gui.handleEvent(m_window->m_event);
	}
}

void Menu::Update(sf::Time dt)
{
	m_world->Update(dt);
}

void Menu::Render()
{
	m_window->clear(sf::Color::Black);

	m_world->Get<RenderSystem>()->Render(m_window);
	m_gui.draw();

	m_window->display();
}
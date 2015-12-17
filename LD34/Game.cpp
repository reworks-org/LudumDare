//
//  Game.cpp
//  LD34
//
//  Created by reworks on 12/12/2015.
//  Copyright (c) 2015 reworks. All rights reserved.
//

#include <SDL2/SDL_events.h>

#include "Game.hpp"

using namespace re;

std::shared_ptr<GameState> Game::game{ new Game };

std::shared_ptr<GameState> Game::Inst()
{
	return game;
}

Game::~Game()
{
	//delete ui;
}

void Game::LoadResources(re::World & world)
{

}

void Game::UnloadResources(re::World & world)
{

}

void Game::Event(SDL_Event & e, re::World & world, GameStateManager * stateManager)
{
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			switch (e.button.button) {
				case SDL_BUTTON_LEFT:
					// shoot
				break;

				case SDL_BUTTON_RIGHT:
					// jump
					break;
			}
		}
	}
}

void Game::Update(double dt, re::World & world, GameStateManager * stateManager)
{

}

void Game::Render(re::World & world, GameStateManager * stateManager)
{

}
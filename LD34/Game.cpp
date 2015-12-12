//
//  Game.cpp
//  LD34
//
//  Created by reworks on 12/12/2015.
//  Copyright (c) 2015 reworks. All rights reserved.
//


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

}

void Game::Update(double dt, re::World & world, GameStateManager * stateManager)
{

}

void Game::Render(re::World & world, GameStateManager * stateManager)
{

}
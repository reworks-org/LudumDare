//
//  Game.hpp
//  LD34
//
//  Created by reworks on 12/12/2015.
//  Copyright (c) 2015 reworks. All rights reserved.
//

#ifndef GAME_LD34_HPP_
#define GAME_LD34_HPP_

#include <ECSREngine/StateManager.hpp>
#include <ECSREngine/UISystem.hpp>

class Game : public GameState
{
public:
	static std::shared_ptr<GameState> Inst();

	~Game() override;
	void LoadResources(re::World& world) override;
	void UnloadResources(re::World& world) override;

	void Event(SDL_Event& e, re::World& world, GameStateManager* stateManager) override;
	void Update(double dt, re::World& world, GameStateManager* stateManager) override;
	void Render(re::World& world, GameStateManager* stateManager) override;
private:
	static std::shared_ptr<GameState> game;
	re::UISystem* ui;
};

#endif
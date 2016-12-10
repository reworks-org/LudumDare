//
//  Game.hpp
//  LD37
//
//  Created by reworks on 10/12/2016.
//  Copyright (c) 2016 reworks. All rights reserved.
//

#ifndef LD37_GAME_HPP_
#define LD37_GAME_HPP_

#include <re/mapping/TMXMap.hpp>
#include <re/systems/StateManager.hpp>
#include <re/scripting/TGUISol2Bridge.hpp>

class Game : public re::State
{
public:
	~Game() override;

	/*
	* IMPORTS: none
	* EXPORTS: none
	* PURPOSE: Instance of state.
	*/
	static std::shared_ptr<re::State> Inst();

	/*
	* IMPORTS: none
	* EXPORTS: none
	* PURPOSE: Load the states resources.
	*/
	void LoadResources() override;

	/*
	* IMPORTS: none
	* EXPORTS: none
	* PURPOSE: Unload the states resources.
	*/
	void UnloadResources() override;

	/*
	* IMPORTS: none
	* EXPORTS: none
	* PURPOSE: Process state events.
	*/
	void Event() override;

	/*
	* IMPORTS: delta time
	* EXPORTS: none
	* PURPOSE: Update state.
	*/
	void Update(sf::Time dt) override;

	/*
	* IMPORTS: none
	* EXPORTS: none
	* PURPOSE: Render state.
	*/
	void Render() override;

private:
	static std::shared_ptr<re::State> m_gameState;
	tgui::Gui m_gui;
	tgui::Theme::Ptr m_theme;
	re::TMXMap m_map;
	bool m_doOnce = true;

};

#endif
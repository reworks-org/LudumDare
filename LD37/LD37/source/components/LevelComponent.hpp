//
//  LevelComponent.hpp
//  LD37
//
//  Created by reworks on 10/12/2016.
//  Copyright (c) 2016 reworks. All rights reserved.
//

#ifndef LD37_LEVELCOMPONENT_HPP_
#define LD37_LEVELCOMPONENT_HPP_

#include "re/mapping/TMXMap.hpp"
#include "re/types/Component.hpp"

class LevelComponent : public re::Component
{
public:
	/*
	* IMPORTS: none
	* EXPORTS: none
	* PURPOSE: Default Constructor.
	*/
	LevelComponent();

	/*
	* IMPORTS: none
	* EXPORTS: none
	* PURPOSE: Clean up.
	*/
	~LevelComponent() override;

	/*
	* IMPORTS: sol::table from lua script containing component data.
	* EXPORTS: none
	* PURPOSE: Set up the component.
	*/
	void Init(sol::table& table) override;

private:
	std::shared_ptr<re::TMXMap> m_map;

};

#endif
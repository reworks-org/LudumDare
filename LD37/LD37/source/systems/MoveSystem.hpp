//
//  MoveSystem.hpp
//  LD37
//
//  Created by reworks on 10/12/2016.
//  Copyright (c) 2016 reworks. All rights reserved.
//

#ifndef LD37_MOVESYSTEM_HPP_
#define LD37_MOVESYSTEM_HPP_

#include <re/types/System.hpp>

// BASIC MOVE SYSTEM EXAMPLE SYSTEM

namespace re
{
	class World;

	class MoveSystem : public System
	{
	public:
		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Cleans up the systems.
		*/
		~MoveSystem() override;

		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Automatically adds entitys to the system.
		*/
		void AutoSubmit(World* world) override;

		/*
		* IMPORTS: id of entity to add and its component list.
		* EXPORTS: none
		* PURPOSE: Add an entitys components from the system.
		*/
		void AddEntity(Entity* e) override;

		/*
		* IMPORTS: id of entity to remove
		* EXPORTS: none
		* PURPOSE: Remove an entitys components from the system.
		*/
		void RemoveEntity(const std::string& name) override;

		/*
		* IMPORTS: name of entity and the horizontal velocity
		* EXPORTS: none
		* PURPOSE: Move an entity.
		*/
		void Move(const std::string& name, double velocity);

		/*
		* IMPORTS: new speed multiplyer. multiply velocity by it.
		* EXPORTS: none
		* PURPOSE: Used mainly for "sprinting"
		*/
		void SetSpeedMultiplyer(int newSpeedMultiplyer);

		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Clean the system.
		*/
		void Clean() override;

	private:
		int m_speedMultiplyer = 1;
	};
}

#endif
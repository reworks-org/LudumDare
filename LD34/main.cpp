//
//  main.cpp
//  LD34
//
//  Created by reworks on 12/12/2015.
//  Copyright (c) 2015 reworks. All rights reserved.
//

#include <string>

#include <SDL2/SDL.h>

#include <ECSREngine/Log.hpp>
#include <ECSREngine/LuaHelper.hpp>
#include <ECSREngine/ZipLoader.hpp>
#include <ECSREngine/Window.hpp>
#include <ECSREngine/StateManager.hpp>
#include <ECSREngine/RenderSystem.hpp>
#include <ECSREngine/Utils.hpp>
#include <ECSREngine/World.hpp>
#include <ECSREngine/PhysicsSystem.hpp>
#include <ECSREngine/SoundSystem.hpp>
#include <ECSREngine/Types.hpp>

#include "Menu.hpp"

#define TARGET_UPS 60.0f

#define MAJOR 1
#define MINOR 0
#define PATCH 0
#define BUILD 0

using namespace re;

int main(int argc, char* argv[])
{
	std::string title = "LD34 - Pew Pew";
	SDL_Event e;
	World world;

	#ifdef _DEBUG
		_Log.DisableLogging(false);
	#else
		_Log.DisableLogging(true);
	#endif

	_Log.OpenLog();

	_ZipLoader.Mount("assets/data.zip");

	_LuaHelper.CreateLuaState();

	_Window.Create(title.c_str(), 800, 600, false, false);
	_Window.SetIcon(ZipLoader::Inst().Get("icon.png"));
	_Window.ShowCursor(true);
	_Window.SetRenderBackgroundColour(96, 96, 96);

	Version v;
	v.major = MAJOR;
	v.minor = MINOR;
	v.patch = PATCH;
	v.build = BUILD;
	v.print(title.c_str());

	world.RegisterSystem<GameStateManager>(std::shared_ptr<System> {new GameStateManager});
	world.RegisterSystem<RenderSystem>(std::shared_ptr<System> {new RenderSystem});
	world.RegisterSystem<PhysicsSystem>(std::shared_ptr<System> {new PhysicsSystem});
	world.RegisterSystem<SoundSystem>(std::shared_ptr<System> {new SoundSystem});

	b2Vec2 gravity(0, 9.81f);

	world.GetSystem<PhysicsSystem>()->CreateWorld(TARGET_UPS, b2RatioMedium, gravity);
	world.GetSystem<GameStateManager>()->SetState(Menu::Inst());
	world.GetSystem<GameStateManager>()->LoadResources(world);

	Uint64 LastTime = Utils::Inst().NanoTime();
	Uint64 Timer = Utils::Inst().SysTime();
	const double Ns = 1000000000.0 / TARGET_UPS;
	double Delta = 0.0;
	int Frames = 0;
	int Updates = 0;

	while (Utils::Inst().IsRunning())
	{
		world.GetSystem<GameStateManager>()->Event(e, world);
		Uint64 Now = Utils::Inst().NanoTime();
		Delta += (Now - LastTime) / Ns;
		LastTime = Now;
		while (Delta >= 1)
		{
			world.GetSystem<GameStateManager>()->Update(Delta, world);
			//std::string print = "Delta: " + Utils::Inst().NumberToString(Delta) + " | ";
			//printf(print.c_str());
			++Updates;
			--Delta;
		}
		world.GetSystem<GameStateManager>()->Render(world);
		++Frames;

		if ((Utils::Inst().SysTime() - Timer) > 1000)
		{
			Timer += 1000;
#ifdef _DEBUG
			std::cout << Updates << " ups, " << Frames << " fps" << std::endl;
			std::string header = "  |  " + Utils::Inst().ToString(Updates) + " ups, " + Utils::Inst().ToString(Frames) + " fps";
			std::string NewTitle = title + header;
			SDL_SetWindowTitle(_Window.GetWindow().get(), NewTitle.c_str());
#endif
			Updates = 0;
			Frames = 0;
		}
	}

	world.GetSystem<GameStateManager>()->UnloadResources(world);

	_Log.Log("Game quit successfully", "main.cpp", 111);

	return EXIT_SUCCESS;
}
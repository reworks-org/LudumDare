//
//  Menu.cpp
//  LD34
//
//  Created by reworks on 12/12/2015.
//  Copyright (c) 2015 reworks. All rights reserved.
//

#include <SDL2/SDL_events.h>

#include <ECSREngine/Window.hpp>
#include <ECSREngine/World.hpp>
#include <ECSREngine/Utils.hpp>
#include <ECSREngine/Types.hpp>
#include <ECSREngine/ZipLoader.hpp>

#include <ECSREngine/GraphicsComponent.hpp>
#include <ECSREngine/MusicComponent.hpp>
#include <ECSREngine/SFXComponent.hpp>

#include <ECSREngine/FontManager.hpp>
#include <ECSREngine/SoundSystem.hpp>
#include <ECSREngine/RenderSystem.hpp>

#include <ECSREngine/UIButton.hpp>
#include <ECSREngine/UILabel.hpp>

#include "Menu.hpp"
#include "Game.hpp"

using namespace re;

std::shared_ptr<GameState> Menu::menu{ new Menu };

std::shared_ptr<GameState> Menu::Inst()
{
	return menu;
}

Menu::~Menu()
{
	//delete ui;
}

void Menu::LoadResources(re::World & world)
{
	FontManager::Inst().Add(std::shared_ptr<Font> { new Font{ ZipLoader::Inst().Get("game_over.ttf"), 256 } }, "GO256");
	FontManager::Inst().Add(std::shared_ptr<Font> { new Font{ ZipLoader::Inst().Get("game_over.ttf"), 128 } }, "GO128");

	ui = new UISystem;

	ui->AddPanel(std::shared_ptr<UIPanel> { new UIPanel({ 0, 0, _Window.GetScreenWidth(), _Window.GetScreenHeight() }, 255, 255, 255, SDL_ALPHA_TRANSPARENT)}, "mainmenu");

	ui->GetPanel("mainmenu")->AddUIComponent(std::shared_ptr<UIComponent> { new UILabel{ 180, -40, "Pew Pew", "GO256",{ 255, 255, 255 }, true, 2 } }, "title");
	ui->GetPanel("mainmenu")->AddUIComponent(std::shared_ptr<UIComponent> { new UIButton(300, 190, "New Game", "GO128", { 255, 255, 0 }, { 225, 215, 0 }, { 238, 221, 130 }, true, 2)}, "newgame");
	ui->GetPanel("mainmenu")->AddUIComponent(std::shared_ptr<UIComponent> { new UIButton(360, 300, "Quit", "GO128", { 255, 255, 0 }, { 225, 215, 0 }, { 238, 221, 130 }, true, 2)}, "quit");

	ui->GetPanel("mainmenu")->GetUIComponent<UIButton>("newgame")->AddSoundEffect(ZipLoader::Inst().Get("beep.wav"), 128);
	ui->GetPanel("mainmenu")->GetUIComponent<UIButton>("quit")->AddSoundEffect(ZipLoader::Inst().Get("beep.wav"), 128);

	ui->GetPanel("mainmenu")->SetComponentOffsets();

	world.RegisterEntity(std::shared_ptr<Entity> { new Entity("assets/scripts/mainmenu.lua", "menu") }, "mainmenu");
	world.GetEntity("mainmenu")->Get<MusicComponent>()->Add(ZipLoader::Inst().Get("game.mp3"), "gamemusic");

	world.GetSystem<RenderSystem>()->RegisterComponents(world);
	world.GetSystem<SoundSystem>()->RegisterComponents(world);
	world.GetSystem<SoundSystem>()->PlayMusic("gamemusic", -1);
}

void Menu::UnloadResources(re::World & world)
{
	world.GetSystem<RenderSystem>()->Clean();
	world.GetSystem<SoundSystem>()->Stop();
	world.GetSystem<SoundSystem>()->Clean();

	world.RemoveEntity("mainmenu");

	delete ui;
}

void Menu::Event(SDL_Event & e, re::World & world, GameStateManager * stateManager)
{
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT) {
			Utils::Inst().SetRunning(false);
		}

		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				Utils::Inst().SetRunning(false);
				break;
			}
		}

		ui->GetPanel("mainmenu")->GetUIComponent<UIButton>("newgame")->ParseEvent(e, 0, 0);
		ui->GetPanel("mainmenu")->GetUIComponent<UIButton>("quit")->ParseEvent(e, 0, 0);
	}
}

void Menu::Update(double dt, re::World & world, GameStateManager * stateManager)
{
	ui->Update();

	if (ui->GetPanel("mainmenu")->GetUIComponent<UIButton>("quit")->IsClicked()) {
		ui->GetPanel("mainmenu")->GetUIComponent<UIButton>("quit")->UnClick();
		Utils::Inst().SetRunning(false);
	}

	if (ui->GetPanel("mainmenu")->GetUIComponent<UIButton>("newgame")->IsClicked()) {
		ui->GetPanel("mainmenu")->GetUIComponent<UIButton>("newgame")->UnClick();
		stateManager->ChangeState(world, Game::Inst());
	}
}

void Menu::Render(re::World & world, GameStateManager * stateManager)
{
	_Window.BeginRendering();

	world.GetSystem<RenderSystem>()->BatchDraw();
	world.GetSystem<RenderSystem>()->Render();

	ui->Render();

	_Window.EndRendering();
}
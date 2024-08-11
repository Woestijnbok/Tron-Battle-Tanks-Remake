#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <iostream>
#include <functional>

#include "Engine.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include "TextComponent.h"
#include "FPSCounterComponent.h"
#include "SpriteComponent.h"
#include "MenuComponent.h"
#include "TileManagerComponent.h"
#include "PlayerTankComponent.h"
#include "AimCommand.h"
#include "BulletManagerComponent.h"
#include "FireCommand.h"
#include "ScoreBoardComponent.h"
#include "BlueTankComponent.h"
#include "TankManagerComponent.h"
#include "PurpleTankComponent.h"

void Load();
void CreateMainMenu();
void CreateFirstLevel();

using namespace Minigin;

void Load()
{
	CreateMainMenu();
	CreateFirstLevel();
}

void CreateMainMenu()
{
	auto scene{ SceneManager::Instance()->CreateScene("Main Menu") };	

	auto menuObject{ scene->CreateGameObject("Menu")};
	menuObject->CreateComponent<MenuComponent>(glm::ivec2{ 200, 50 }, 10);
}

void CreateFirstLevel()
{
	auto scene{ SceneManager::Instance()->CreateScene("First Level", false) };

	// Managers
	GameObject* manager{ scene->CreateGameObject("Manager")};
	TileManagerComponent* tileManager = manager->CreateComponent<TileManagerComponent>(50);
	TankManagerComponent* tankManager = manager->CreateComponent<TankManagerComponent>();
	BulletManagerComponent* bulletManager = manager->CreateComponent<BulletManagerComponent>();	
	manager->SetLocalPosition(glm::ivec2{ 55, 55 });

	// Conecting the managers
	tileManager->SetManagers(bulletManager, tankManager);
	tankManager->SetManagers(tileManager, bulletManager);
	bulletManager->SetManagers(tileManager, tankManager);	

	// Player tank
	PlayerTankComponent* playerTank{ tankManager->CreatePlayerTank() };	

	// Enemy blue tank 1
	std::shared_ptr<Texture> blueTankTexture{ ResourceManager::Instance()->LoadTexture("Blue Tank.png") };
	BlueTankComponent* enemyOne{ tankManager->CreateBlueTank(blueTankTexture) };

	// Enemy Purple 1
	std::shared_ptr<Texture> purpleTankTexture{ ResourceManager::Instance()->LoadTexture("Purple Tank.png") };	
	PurpleTankComponent* enemyTwo{ tankManager->CreatePurpleTank(purpleTankTexture) };		

	// Scoreboard
	GameObject* scoreboardObject{ scene->CreateGameObject("Scoreboard") };	
	ScoreboardComponent* scoreboard{ scoreboardObject->CreateComponent<ScoreboardComponent>(playerTank->GetLives()) };	
	scoreboardObject->SetLocalPosition(glm::ivec2{ 255, 550 });	

	// Hooking scoreboard up to player tank
	playerTank->OnLivesChange().AddObserver(std::bind(&ScoreboardComponent::UpdateLives, scoreboard, std::placeholders::_1));		
	enemyOne->OnDie().AddObserver(std::bind(&ScoreboardComponent::UpdateScore, scoreboard, std::placeholders::_1));
	enemyTwo->OnDie().AddObserver(std::bind(&ScoreboardComponent::UpdateScore, scoreboard, std::placeholders::_1));	

	// Input for player tank
	InputManager::Instance()->GetKeyboard().AddInputAction(Keyboard::Key::W, InputAction::Trigger::Down, std::make_shared<MoveCommand>(playerTank, MoveCommand::Direction::Up));			
	InputManager::Instance()->GetKeyboard().AddInputAction(Keyboard::Key::D, InputAction::Trigger::Down, std::make_shared<MoveCommand>(playerTank, MoveCommand::Direction::Right));				
	InputManager::Instance()->GetKeyboard().AddInputAction(Keyboard::Key::S, InputAction::Trigger::Down, std::make_shared<MoveCommand>(playerTank, MoveCommand::Direction::Down));				
	InputManager::Instance()->GetKeyboard().AddInputAction(Keyboard::Key::A, InputAction::Trigger::Down, std::make_shared<MoveCommand>(playerTank, MoveCommand::Direction::Left));
	InputManager::Instance()->GetMouse().AddInputAction(Mouse::Action::Move, std::make_shared<AimCommand>(playerTank));	
	InputManager::Instance()->GetMouse().AddInputAction(Mouse::Action::RightClick, std::make_shared<FireCommand>(playerTank));		
}

int main(int, char*[])
{
	Engine::Initialize("Tron");
	Engine::Run(&Load);
	Engine::Destroy();

    return 0;
}
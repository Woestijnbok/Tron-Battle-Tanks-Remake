#include <vec2.hpp>

#include "ResourceManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"

#include "Loaders.h"
#include "TileManagerComponent.h"
#include "TankManagerComponent.h"
#include "BulletManagerComponent.h"
#include "PlayerTankComponent.h"
#include "BlueTankComponent.h"
#include "PurpleTankComponent.h"
#include "ScoreBoardComponent.h"
#include "AimCommand.h"
#include "MoveCommand.h"
#include "FireCommand.h"

using namespace Minigin;

void LoadMainMenu()
{
	SceneManager::Instance()->IsolateScene("Main Menu");
	SceneManager::Instance()->GetScene("Main Menu")->SetStatus(ControllableObject::Status::Enabled);
}

void LoadLevelOne()
{
	SceneManager::Instance()->IsolateScene("Main Menu");
	SceneManager::Instance()->GetScene("Main Menu")->SetStatus(ControllableObject::Status::Disabled);

	auto scene{ SceneManager::Instance()->CreateScene("Level 1") };	

	// Managers
	GameObject* manager{ scene->CreateGameObject("Manager") };
	TileManagerComponent* tileManager = manager->CreateComponent<TileManagerComponent>(50);
	TankManagerComponent* tankManager = manager->CreateComponent<TankManagerComponent>();
	BulletManagerComponent* bulletManager = manager->CreateComponent<BulletManagerComponent>();
	manager->SetLocalPosition(glm::ivec2{ 55, 55 });

	// Conecting the managers
	tileManager->SetManagers(bulletManager, tankManager);
	tankManager->SetManagers(tileManager, bulletManager);
	bulletManager->SetManagers(tileManager, tankManager);

	// Scene transisitions
	tankManager->OnGameOver().AddObserver(&LoadMainMenu);
	tankManager->OnLevelCompleted().AddObserver(&LoadLevelTwo);

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
	ScoreboardComponent* scoreboard{ scoreboardObject->CreateComponent<ScoreboardComponent>(0, playerTank->GetLives()) };
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

void LoadLevelTwo()
{	
	SceneManager::Instance()->GetScene("Main Menu")->SetStatus(ControllableObject::Status::Disabled);

	auto scene{ SceneManager::Instance()->CreateScene("Level 2") };

	// Managers
	GameObject* manager{ scene->CreateGameObject("Manager") };
	TileManagerComponent* tileManager = manager->CreateComponent<TileManagerComponent>(50);
	TankManagerComponent* tankManager = manager->CreateComponent<TankManagerComponent>();
	BulletManagerComponent* bulletManager = manager->CreateComponent<BulletManagerComponent>();
	manager->SetLocalPosition(glm::ivec2{ 55, 55 });

	// Conecting the managers
	tileManager->SetManagers(bulletManager, tankManager);
	tankManager->SetManagers(tileManager, bulletManager);
	bulletManager->SetManagers(tileManager, tankManager);

	// Scene transisitions
	tankManager->OnGameOver().AddObserver(&LoadMainMenu);
	tankManager->OnLevelCompleted().AddObserver(&LoadMainMenu);		

	// Player tank
	PlayerTankComponent* playerTank{ tankManager->CreatePlayerTank() };

	// Enemy blue tank 1
	std::shared_ptr<Texture> blueTankTexture{ ResourceManager::Instance()->LoadTexture("Blue Tank.png") };
	BlueTankComponent* enemyOne{ tankManager->CreateBlueTank(blueTankTexture) };

	// Scoreboard
	ScoreboardComponent* oldScoreboard{ SceneManager::Instance()->GetScene("Level 1")->GetGameObject("Scoreboard")->GetComponent<ScoreboardComponent>() };
	GameObject* scoreboardObject{ scene->CreateGameObject("Scoreboard") };
	ScoreboardComponent* scoreboard{ scoreboardObject->CreateComponent<ScoreboardComponent>(oldScoreboard->GetScore(), oldScoreboard->GetLives()) };
	scoreboardObject->SetLocalPosition(glm::ivec2{ 255, 550 });

	// Hooking scoreboard up to player tank
	playerTank->OnLivesChange().AddObserver(std::bind(&ScoreboardComponent::UpdateLives, scoreboard, std::placeholders::_1));
	enemyOne->OnDie().AddObserver(std::bind(&ScoreboardComponent::UpdateScore, scoreboard, std::placeholders::_1));

	// Input for player tank
	InputManager::Instance()->GetKeyboard().AddInputAction(Keyboard::Key::W, InputAction::Trigger::Down, std::make_shared<MoveCommand>(playerTank, MoveCommand::Direction::Up));
	InputManager::Instance()->GetKeyboard().AddInputAction(Keyboard::Key::D, InputAction::Trigger::Down, std::make_shared<MoveCommand>(playerTank, MoveCommand::Direction::Right));
	InputManager::Instance()->GetKeyboard().AddInputAction(Keyboard::Key::S, InputAction::Trigger::Down, std::make_shared<MoveCommand>(playerTank, MoveCommand::Direction::Down));
	InputManager::Instance()->GetKeyboard().AddInputAction(Keyboard::Key::A, InputAction::Trigger::Down, std::make_shared<MoveCommand>(playerTank, MoveCommand::Direction::Left));
	InputManager::Instance()->GetMouse().AddInputAction(Mouse::Action::Move, std::make_shared<AimCommand>(playerTank));
	InputManager::Instance()->GetMouse().AddInputAction(Mouse::Action::RightClick, std::make_shared<FireCommand>(playerTank));

	// Remove level 2
	SceneManager::Instance()->RemoveScene("Level 1");
}

void LoadLevelThree()
{

}
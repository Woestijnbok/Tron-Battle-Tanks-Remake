#include <vec2.hpp>

#include "ResourceManager.h"
#include "InputManager.h"
#include "Renderer.h"
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

void CreateKeyboardAndMouseInput(PlayerTankComponent* tank)
{
	// Movement
	InputManager::Instance()->GetKeyboard().AddInputAction(Keyboard::Key::W, InputAction::Trigger::Down, std::make_shared<MoveCommand>(tank, MoveCommand::Direction::Up));	
	InputManager::Instance()->GetKeyboard().AddInputAction(Keyboard::Key::D, InputAction::Trigger::Down, std::make_shared<MoveCommand>(tank, MoveCommand::Direction::Right));	
	InputManager::Instance()->GetKeyboard().AddInputAction(Keyboard::Key::S, InputAction::Trigger::Down, std::make_shared<MoveCommand>(tank, MoveCommand::Direction::Down));	
	InputManager::Instance()->GetKeyboard().AddInputAction(Keyboard::Key::A, InputAction::Trigger::Down, std::make_shared<MoveCommand>(tank, MoveCommand::Direction::Left));	

	// Aim And Fire
	InputManager::Instance()->GetMouse().AddInputAction(Mouse::Action::Move, std::make_shared<AimCommand>(tank));
	InputManager::Instance()->GetMouse().AddInputAction(Mouse::Action::RightClick, std::make_shared<FireCommand>(tank));	
}

void CreateControllerInput(PlayerTankComponent* tank, int controllerIndex)
{
	// Movement
	InputManager::Instance()->GetController(controllerIndex).AddInputAction(Controller::Button::DpadUp, InputAction::Trigger::Down, std::make_shared<MoveCommand>(tank, MoveCommand::Direction::Up));		
	InputManager::Instance()->GetController(controllerIndex).AddInputAction(Controller::Button::DpadRight, InputAction::Trigger::Down, std::make_shared<MoveCommand>(tank, MoveCommand::Direction::Right));	
	InputManager::Instance()->GetController(controllerIndex).AddInputAction(Controller::Button::DpadDown, InputAction::Trigger::Down, std::make_shared<MoveCommand>(tank, MoveCommand::Direction::Down));	
	InputManager::Instance()->GetController(controllerIndex).AddInputAction(Controller::Button::DpadLeft, InputAction::Trigger::Down, std::make_shared<MoveCommand>(tank, MoveCommand::Direction::Left));	

	// Aim And Fire
	InputManager::Instance()->GetController(controllerIndex).AddInputAction(Controller::Button::RightJoystick, InputAction::Trigger::None, std::make_shared<AimCommand>(tank, true));		
	InputManager::Instance()->GetController(controllerIndex).AddInputAction(Controller::Button::RightShoulder, InputAction::Trigger::Pressed, std::make_shared<FireCommand>(tank));		
}

void GameOver()	
{
	LoadMainMenu();	
}

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
	tankManager->OnGameOver().AddObserver(&GameOver);	
	tankManager->OnLevelCompleted().AddObserver(&LoadLevelTwo);

	// Player tank
	Texture* redTankTexture{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Red Tank.png") };	
	Texture* redBarrelTexture{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Red Barrel.png") };	
	PlayerTankComponent* playerTank{ tankManager->CreatePlayerTank(redTankTexture, redBarrelTexture) };
	PlayerTankComponent::SetLivesShared(false);

	// Enemy blue tank 1
	std::shared_ptr<Texture> blueTankTexture{ ResourceManager::Instance()->LoadTexture("Blue Tank.png") };
	BlueTankComponent* enemyOne{ tankManager->CreateBlueTank(blueTankTexture) };

	// Enemy Purple 1
	std::shared_ptr<Texture> purpleTankTexture{ ResourceManager::Instance()->LoadTexture("Purple Tank.png") };
	PurpleTankComponent* enemyTwo{ tankManager->CreatePurpleTank(purpleTankTexture) };

	// Scoreboard
	GameObject* scoreboardObject{ scene->CreateGameObject("Scoreboard") };
	ScoreboardComponent* scoreboard{ scoreboardObject->CreateComponent<ScoreboardComponent>(0, playerTank->Lives()) };	
	scoreboardObject->SetLocalPosition(glm::ivec2{ 255, 550 });

	// Hooking scoreboard up to player tank
	playerTank->OnHit().AddObserver(std::bind(&ScoreboardComponent::UpdateLives, scoreboard, std::placeholders::_1));	
	enemyOne->OnDie().AddObserver(std::bind(&ScoreboardComponent::UpdateScore, scoreboard, std::placeholders::_1));
	enemyTwo->OnDie().AddObserver(std::bind(&ScoreboardComponent::UpdateScore, scoreboard, std::placeholders::_1));

	// Input for player tank
	CreateKeyboardAndMouseInput(playerTank);
	CreateControllerInput(playerTank, 0);
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
	tankManager->OnGameOver().AddObserver(&GameOver);	
	tankManager->OnLevelCompleted().AddObserver(&LoadLevelThree);				

	// Player tank
	Texture* redTankTexture{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Red Tank.png") };	
	Texture* redBarrelTexture{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Red Barrel.png") };	
	PlayerTankComponent* playerTank{ tankManager->CreatePlayerTank(redTankTexture, redBarrelTexture) };
	PlayerTankComponent::SetLivesShared(false);	

	// Enemy blue tank 1
	std::shared_ptr<Texture> blueTankTexture{ ResourceManager::Instance()->LoadTexture("Blue Tank.png") };
	BlueTankComponent* enemyOne{ tankManager->CreateBlueTank(blueTankTexture) };

	// Scoreboard
	ScoreboardComponent* oldScoreboard{ SceneManager::Instance()->GetScene("Level 1")->GetGameObject("Scoreboard")->GetComponent<ScoreboardComponent>() };
	GameObject* scoreboardObject{ scene->CreateGameObject("Scoreboard") };
	ScoreboardComponent* scoreboard{ scoreboardObject->CreateComponent<ScoreboardComponent>(oldScoreboard->GetScore(), oldScoreboard->GetLives()) };
	scoreboardObject->SetLocalPosition(glm::ivec2{ 255, 550 });

	// Hooking scoreboard up to player tank
	playerTank->OnHit().AddObserver(std::bind(&ScoreboardComponent::UpdateLives, scoreboard, std::placeholders::_1));	
	enemyOne->OnDie().AddObserver(std::bind(&ScoreboardComponent::UpdateScore, scoreboard, std::placeholders::_1));

	// Input for player tank
	CreateKeyboardAndMouseInput(playerTank);	
	CreateControllerInput(playerTank, 0);	

	// Remove level 2
	SceneManager::Instance()->RemoveScene("Level 1");
}

void LoadLevelThree()
{
	SceneManager::Instance()->GetScene("Main Menu")->SetStatus(ControllableObject::Status::Disabled);

	auto scene{ SceneManager::Instance()->CreateScene("Level 3") };

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
	tankManager->OnGameOver().AddObserver(&GameOver);
	tankManager->OnLevelCompleted().AddObserver(&GameOver);	

	// Player tank
	Texture* redTankTexture{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Red Tank.png") };	
	Texture* redBarrelTexture{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Red Barrel.png") };	
	PlayerTankComponent* playerTank{ tankManager->CreatePlayerTank(redTankTexture, redBarrelTexture) };

	PlayerTankComponent::SetLivesShared(false);	

	// Enemy blue tank 1
	std::shared_ptr<Texture> blueTankTexture{ ResourceManager::Instance()->LoadTexture("Blue Tank.png") };
	BlueTankComponent* enemyOne{ tankManager->CreateBlueTank(blueTankTexture) };

	// Scoreboard
	ScoreboardComponent* oldScoreboard{ SceneManager::Instance()->GetScene("Level 2")->GetGameObject("Scoreboard")->GetComponent<ScoreboardComponent>() };
	GameObject* scoreboardObject{ scene->CreateGameObject("Scoreboard") };
	ScoreboardComponent* scoreboard{ scoreboardObject->CreateComponent<ScoreboardComponent>(oldScoreboard->GetScore(), oldScoreboard->GetLives()) };
	scoreboardObject->SetLocalPosition(glm::ivec2{ 255, 550 });

	// Hooking scoreboard up to player tank
	playerTank->OnHit().AddObserver(std::bind(&ScoreboardComponent::UpdateLives, scoreboard, std::placeholders::_1));	
	enemyOne->OnDie().AddObserver(std::bind(&ScoreboardComponent::UpdateScore, scoreboard, std::placeholders::_1));

	// Input for player tank
	CreateKeyboardAndMouseInput(playerTank);
	CreateControllerInput(playerTank, 0);

	// Remove level 2
	SceneManager::Instance()->RemoveScene("Level 2");
}

void LoadCoopLevel()
{
	SceneManager::Instance()->IsolateScene("Main Menu");
	SceneManager::Instance()->GetScene("Main Menu")->SetStatus(ControllableObject::Status::Disabled);

	auto scene{ SceneManager::Instance()->CreateScene("Level Coop") };

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
	tankManager->OnGameOver().AddObserver(&GameOver);
	tankManager->OnLevelCompleted().AddObserver(&LoadLevelTwo);	

	// Player tne	
	Texture* redTankTexture{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Red Tank.png") };	
	Texture* redBarrelTexture{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Red Barrel.png") };	
	PlayerTankComponent* playerOne{ tankManager->CreatePlayerTank(redTankTexture, redBarrelTexture) };	

	// Player two
	Texture* yellowTankTexture{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Yellow Tank.png") };	
	Texture* yellowBarrelTexture{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Yellow Barrel.png") };	
	PlayerTankComponent* playerTwo{ tankManager->CreatePlayerTank(yellowTankTexture, yellowBarrelTexture) };	

	PlayerTankComponent::SetLivesShared(true);

	// Enemy blue tank 1
	std::shared_ptr<Texture> blueTankTexture{ ResourceManager::Instance()->LoadTexture("Blue Tank.png") };	
	BlueTankComponent* enemyOne{ tankManager->CreateBlueTank(blueTankTexture) };	

	// Enemy Purple 1
	std::shared_ptr<Texture> purpleTankTexture{ ResourceManager::Instance()->LoadTexture("Purple Tank.png") };
	PurpleTankComponent* enemyTwo{ tankManager->CreatePurpleTank(purpleTankTexture) };

	// Scoreboard
	GameObject* scoreboardObject{ scene->CreateGameObject("Scoreboard") };
	ScoreboardComponent* scoreboard{ scoreboardObject->CreateComponent<ScoreboardComponent>(0, PlayerTankComponent::SharedLives()) };		
	scoreboardObject->SetLocalPosition(glm::ivec2{ 255, 550 });

	// Hooking scoreboard up to player tank
	playerOne->OnHit().AddObserver(std::bind(&ScoreboardComponent::UpdateLives, scoreboard, std::placeholders::_1));
	playerTwo->OnHit().AddObserver(std::bind(&ScoreboardComponent::UpdateLives, scoreboard, std::placeholders::_1));
	enemyOne->OnDie().AddObserver(std::bind(&ScoreboardComponent::UpdateScore, scoreboard, std::placeholders::_1));
	enemyTwo->OnDie().AddObserver(std::bind(&ScoreboardComponent::UpdateScore, scoreboard, std::placeholders::_1));

	// Input for player tank
	CreateKeyboardAndMouseInput(playerOne);
	CreateControllerInput(playerOne, 1);
	CreateControllerInput(playerTwo, 0);	
}

void LoadVersusLevel()
{
	SceneManager::Instance()->IsolateScene("Main Menu");
	SceneManager::Instance()->GetScene("Main Menu")->SetStatus(ControllableObject::Status::Disabled);

	auto scene{ SceneManager::Instance()->CreateScene("Level Versus") };

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
	tankManager->OnGameOver().AddObserver(&GameOver);

	// Player tne
	Texture* redTankTexture{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Red Tank.png") };
	Texture* redBarrelTexture{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Red Barrel.png") };
	PlayerTankComponent* playerOne{ tankManager->CreatePlayerTank(redTankTexture, redBarrelTexture) };

	// Player two
	Texture* yellowTankTexture{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Yellow Tank.png") };
	Texture* yellowBarrelTexture{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Yellow Barrel.png") };
	PlayerTankComponent* playerTwo{ tankManager->CreatePlayerTank(yellowTankTexture, yellowBarrelTexture) };

	PlayerTankComponent::SetLivesShared(false);

	// Scoreboard player one
	GameObject* scoreboardOneObject{ scene->CreateGameObject("Scoreboard One") };	
	ScoreboardComponent* scoreboardOne{ scoreboardOneObject->CreateComponent<ScoreboardComponent>(0, playerOne->Lives(), false) };	
	playerOne->OnHit().AddObserver(std::bind(&ScoreboardComponent::UpdateLives, scoreboardOne, std::placeholders::_1));
	playerOne->OnDie().AddObserver(std::bind(&TankManagerComponent::RemoveAllPlayers, tankManager));		
	scoreboardOneObject->SetLocalPosition(glm::ivec2{ 155, 550 });	

	// Scoreboard player two
	GameObject* scoreboardTwoObject{ scene->CreateGameObject("Scoreboard Two") };
	ScoreboardComponent* scoreboardTwo{ scoreboardTwoObject->CreateComponent<ScoreboardComponent>(0, playerTwo->Lives(), false) };		
	playerTwo->OnHit().AddObserver(std::bind(&ScoreboardComponent::UpdateLives, scoreboardTwo, std::placeholders::_1));
	playerTwo->OnDie().AddObserver(std::bind(&TankManagerComponent::RemoveAllPlayers, tankManager));			
	scoreboardTwoObject->SetLocalPosition(glm::ivec2{ 255, 550 });

	// Input for player tank
	CreateKeyboardAndMouseInput(playerOne);
	CreateControllerInput(playerOne, 1);
	CreateControllerInput(playerTwo, 0);
}
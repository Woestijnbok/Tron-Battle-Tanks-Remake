#include <vec2.hpp>

#include "ResourceManager.h"
#include "InputManager.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Engine.h"

#include "Loaders.h"
#include "TileManagerComponent.h"
#include "TankManagerComponent.h"
#include "BulletManagerComponent.h"
#include "PlayerTankComponent.h"
#include "BlueTankComponent.h"
#include "PurpleTankComponent.h"
#include "AimCommand.h"
#include "MoveCommand.h"
#include "FireCommand.h"
#include "HighscoresComponent.h"
#include "MenuComponent.h"
#include "ScoreBoardComponent.h"
#include "AudioHelpers.h"

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
	const std::optional<std::string> name{ SceneManager::Instance()->GetScene("Main Menu")->GetGameObject("Menu")->GetComponent<MenuComponent>()->GetPlayerName() };

	if (name)
	{
		HighscoresComponent::AddScore(HighscoresComponent::ScoreEntry{ name.value(), ScoreboardComponent::GetScore()});
		HighscoresComponent::SaveHighscores();		
	}		

	LoadMainMenu();	
}

void LoadMainMenu()
{
	SceneManager::Instance()->IsolateScene("Main Menu");
	SceneManager::Instance()->GetScene("Main Menu")->SetStatus(ControllableObject::Status::Enabled);

	StopAllAudio();		
	PlayMenuMusic();
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

	// Player
	std::shared_ptr<Texture> redTankTexture{ Minigin::ResourceManager::Instance()->LoadTexture("Red Tank.png") };		
	std::shared_ptr<Texture> redBarrelTexture{ Minigin::ResourceManager::Instance()->LoadTexture("Red Barrel.png") };		
	PlayerTankComponent* playerTank{ tankManager->CreatePlayerTank(redTankTexture, redBarrelTexture, 4) };
	PlayerTankComponent::SetLivesShared(false);

	// Enemies
	std::shared_ptr<Texture> blueTankTexture{ ResourceManager::Instance()->LoadTexture("Blue Tank.png") };
	BlueTankComponent* enemyOne{ tankManager->CreateBlueTank(blueTankTexture) };
	BlueTankComponent* enemyTwo{ tankManager->CreateBlueTank(blueTankTexture) };		

	// Scoreboard
	std::shared_ptr<Minigin::Font> scoreFont{ Minigin::ResourceManager::Instance()->LoadFont("Arcade.otf", 30) };
	std::shared_ptr<Minigin::Texture> livesTexture{ Minigin::ResourceManager::Instance()->LoadTexture("Hearth.png") };	
	GameObject* scoreboardObject{ scene->CreateGameObject("Scoreboard") };
	ScoreboardComponent* scoreboard{ scoreboardObject->CreateComponent<ScoreboardComponent>(scoreFont, livesTexture, 0, playerTank->Lives()) };	
	scoreboardObject->SetLocalPosition(glm::ivec2{ 255, 550 });

	// Hooking scoreboard up to player tank
	playerTank->OnHit().AddObserver(std::bind(&ScoreboardComponent::UpdateLives, scoreboard, std::placeholders::_1));	
	enemyOne->OnDie().AddObserver(std::bind(&ScoreboardComponent::UpdateScore, scoreboard, std::placeholders::_1));
	enemyTwo->OnDie().AddObserver(std::bind(&ScoreboardComponent::UpdateScore, scoreboard, std::placeholders::_1));

	// Input for player tank
	CreateKeyboardAndMouseInput(playerTank);
	CreateControllerInput(playerTank, 0);

	// Audio
	playerTank->OnFire().AddObserver(&PlayFireSoundEffect);	
	playerTank->OnHit().AddObserver(&PlayHitSoundEffect);	
	enemyOne->OnFire().AddObserver(&PlayFireSoundEffect);	
	enemyTwo->OnFire().AddObserver(&PlayFireSoundEffect);	
	PlayGameMusic();	
}

void LoadLevelTwo()
{	
	SceneManager::Instance()->GetScene("Main Menu")->SetStatus(ControllableObject::Status::Disabled);

	ScoreboardComponent* oldScoreboard{ SceneManager::Instance()->GetScene("Level 1")->GetGameObject("Scoreboard")->GetComponent<ScoreboardComponent>() };	

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
	std::shared_ptr<Texture> redTankTexture{ Minigin::ResourceManager::Instance()->LoadTexture("Red Tank.png") };	
	std::shared_ptr<Texture> redBarrelTexture{ Minigin::ResourceManager::Instance()->LoadTexture("Red Barrel.png") };	
	PlayerTankComponent* playerTank{ tankManager->CreatePlayerTank(redTankTexture, redBarrelTexture, oldScoreboard->GetLives()) };
	PlayerTankComponent::SetLivesShared(false);	

	// Enemies
	std::shared_ptr<Texture> blueTankTexture{ ResourceManager::Instance()->LoadTexture("Blue Tank.png") };
	std::shared_ptr<Texture> purpleTankTexture{ ResourceManager::Instance()->LoadTexture("Purple Tank.png") };	
	BlueTankComponent* enemyOne{ tankManager->CreateBlueTank(blueTankTexture) };	
	BlueTankComponent* enemyTwo{ tankManager->CreateBlueTank(blueTankTexture) };	
	PurpleTankComponent* enemyThree{ tankManager->CreatePurpleTank(purpleTankTexture) };

	// Scoreboard
	std::shared_ptr<Minigin::Font> scoreFont{ Minigin::ResourceManager::Instance()->LoadFont("Arcade.otf", 30) };	
	std::shared_ptr<Minigin::Texture> livesTexture{ Minigin::ResourceManager::Instance()->LoadTexture("Hearth.png") };	
	GameObject* scoreboardObject{ scene->CreateGameObject("Scoreboard") };
	ScoreboardComponent* scoreboard{ scoreboardObject->CreateComponent<ScoreboardComponent>(scoreFont, livesTexture, oldScoreboard->GetScore(), oldScoreboard->GetLives()) };	
	scoreboardObject->SetLocalPosition(glm::ivec2{ 255, 550 });

	// Hooking scoreboard up to player tank
	playerTank->OnHit().AddObserver(std::bind(&ScoreboardComponent::UpdateLives, scoreboard, std::placeholders::_1));	
	enemyOne->OnDie().AddObserver(std::bind(&ScoreboardComponent::UpdateScore, scoreboard, std::placeholders::_1));
	enemyTwo->OnDie().AddObserver(std::bind(&ScoreboardComponent::UpdateScore, scoreboard, std::placeholders::_1));	
	enemyThree->OnDie().AddObserver(std::bind(&ScoreboardComponent::UpdateScore, scoreboard, std::placeholders::_1));	

	// Input for player tank
	CreateKeyboardAndMouseInput(playerTank);	
	CreateControllerInput(playerTank, 0);	

	// Remove level 2
	SceneManager::Instance()->RemoveScene("Level 1");

	// Audio
	playerTank->OnFire().AddObserver(&PlayFireSoundEffect);	
	playerTank->OnHit().AddObserver(&PlayHitSoundEffect);	
	enemyOne->OnFire().AddObserver(&PlayFireSoundEffect);	
	enemyTwo->OnFire().AddObserver(&PlayFireSoundEffect);
	enemyThree->OnFire().AddObserver(&PlayFireSoundEffect);
	StopAllAudio();
	PlayGameMusic();
}

void LoadLevelThree()
{
	SceneManager::Instance()->GetScene("Main Menu")->SetStatus(ControllableObject::Status::Disabled);

	ScoreboardComponent* oldScoreboard{ SceneManager::Instance()->GetScene("Level 2")->GetGameObject("Scoreboard")->GetComponent<ScoreboardComponent>() };		

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
	std::shared_ptr<Texture> redTankTexture{ Minigin::ResourceManager::Instance()->LoadTexture("Red Tank.png") };	
	std::shared_ptr<Texture> redBarrelTexture{ Minigin::ResourceManager::Instance()->LoadTexture("Red Barrel.png") };
	PlayerTankComponent* playerTank{ tankManager->CreatePlayerTank(redTankTexture, redBarrelTexture, oldScoreboard->GetLives()) };
	PlayerTankComponent::SetLivesShared(false);	

	// Enemies
	std::shared_ptr<Texture> blueTankTexture{ ResourceManager::Instance()->LoadTexture("Blue Tank.png") };
	std::shared_ptr<Texture> purpleTankTexture{ ResourceManager::Instance()->LoadTexture("Purple Tank.png") };
	BlueTankComponent* enemyOne{ tankManager->CreateBlueTank(blueTankTexture) };
	BlueTankComponent* enemyTwo{ tankManager->CreateBlueTank(blueTankTexture) };
	PurpleTankComponent* enemyThree{ tankManager->CreatePurpleTank(purpleTankTexture) };				
	PurpleTankComponent* enemyFour{ tankManager->CreatePurpleTank(purpleTankTexture) };	

	// Scoreboard
	std::shared_ptr<Minigin::Font> scoreFont{ Minigin::ResourceManager::Instance()->LoadFont("Arcade.otf", 30) };
	std::shared_ptr<Minigin::Texture> livesTexture{ Minigin::ResourceManager::Instance()->LoadTexture("Hearth.png") };
	GameObject* scoreboardObject{ scene->CreateGameObject("Scoreboard") };
	ScoreboardComponent* scoreboard{ scoreboardObject->CreateComponent<ScoreboardComponent>(scoreFont, livesTexture, oldScoreboard->GetScore(), oldScoreboard->GetLives()) };	
	scoreboardObject->SetLocalPosition(glm::ivec2{ 255, 550 });

	// Hooking scoreboard up to player tank
	playerTank->OnHit().AddObserver(std::bind(&ScoreboardComponent::UpdateLives, scoreboard, std::placeholders::_1));	
	enemyOne->OnDie().AddObserver(std::bind(&ScoreboardComponent::UpdateScore, scoreboard, std::placeholders::_1));
	enemyTwo->OnDie().AddObserver(std::bind(&ScoreboardComponent::UpdateScore, scoreboard, std::placeholders::_1));	
	enemyThree->OnDie().AddObserver(std::bind(&ScoreboardComponent::UpdateScore, scoreboard, std::placeholders::_1));	
	enemyFour->OnDie().AddObserver(std::bind(&ScoreboardComponent::UpdateScore, scoreboard, std::placeholders::_1));	

	// Input for player tank
	CreateKeyboardAndMouseInput(playerTank);
	CreateControllerInput(playerTank, 0);

	// Remove level 2
	SceneManager::Instance()->RemoveScene("Level 2");

	// Audio	
	playerTank->OnFire().AddObserver(&PlayFireSoundEffect);	
	playerTank->OnHit().AddObserver(&PlayHitSoundEffect);	
	enemyOne->OnFire().AddObserver(&PlayFireSoundEffect);	
	enemyTwo->OnFire().AddObserver(&PlayFireSoundEffect);	
	enemyThree->OnFire().AddObserver(&PlayFireSoundEffect);
	enemyFour->OnFire().AddObserver(&PlayFireSoundEffect);
	StopAllAudio();	
	PlayGameMusic();	
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
	tankManager->OnGameOver().AddObserver(&LoadMainMenu);	
	tankManager->OnLevelCompleted().AddObserver(&LoadMainMenu);	

	// Player one	
	std::shared_ptr<Texture> redTankTexture{ Minigin::ResourceManager::Instance()->LoadTexture("Red Tank.png") };	
	std::shared_ptr<Texture> redBarrelTexture{ Minigin::ResourceManager::Instance()->LoadTexture("Red Barrel.png") };	
	PlayerTankComponent* playerOne{ tankManager->CreatePlayerTank(redTankTexture, redBarrelTexture, 4) };	

	// Player two
	std::shared_ptr<Texture> yellowTankTexture{ Minigin::ResourceManager::Instance()->LoadTexture("Yellow Tank.png") };	
	std::shared_ptr<Texture> yellowBarrelTexture{ Minigin::ResourceManager::Instance()->LoadTexture("Yellow Barrel.png") };	
	PlayerTankComponent* playerTwo{ tankManager->CreatePlayerTank(yellowTankTexture, yellowBarrelTexture, 4) };				

	PlayerTankComponent::SetLivesShared(true);
	PlayerTankComponent::SetSharedLives(4);

	// Enemies
	std::shared_ptr<Texture> blueTankTexture{ ResourceManager::Instance()->LoadTexture("Blue Tank.png") };	
	std::shared_ptr<Texture> purpleTankTexture{ ResourceManager::Instance()->LoadTexture("Purple Tank.png") };	
	BlueTankComponent* enemyOne{ tankManager->CreateBlueTank(blueTankTexture) };		
	PurpleTankComponent* enemyTwo{ tankManager->CreatePurpleTank(purpleTankTexture) };	
	PurpleTankComponent* enemyThree{ tankManager->CreatePurpleTank(purpleTankTexture) };	

	// Scoreboard	
	std::shared_ptr<Minigin::Font> scoreFont{ Minigin::ResourceManager::Instance()->LoadFont("Arcade.otf", 30) };	
	std::shared_ptr<Minigin::Texture> livesTexture{ Minigin::ResourceManager::Instance()->LoadTexture("Hearth.png") };	
	GameObject* scoreboardObject{ scene->CreateGameObject("Scoreboard") };
	ScoreboardComponent* scoreboard{ scoreboardObject->CreateComponent<ScoreboardComponent>(scoreFont, livesTexture, 0, PlayerTankComponent::SharedLives(), false) };			
	scoreboardObject->SetLocalPosition(glm::ivec2{ 255, 550 });

	// Hooking scoreboard up to player tank
	playerOne->OnHit().AddObserver(std::bind(&ScoreboardComponent::UpdateLives, scoreboard, std::placeholders::_1));
	playerTwo->OnHit().AddObserver(std::bind(&ScoreboardComponent::UpdateLives, scoreboard, std::placeholders::_1));

	// Input for player tank
	CreateKeyboardAndMouseInput(playerOne);
	CreateControllerInput(playerOne, 1);
	CreateControllerInput(playerTwo, 0);

	// Audio	
	playerOne->OnFire().AddObserver(&PlayFireSoundEffect);	
	playerOne->OnHit().AddObserver(&PlayHitSoundEffect);
	playerTwo->OnFire().AddObserver(&PlayFireSoundEffect);
	playerTwo->OnHit().AddObserver(&PlayHitSoundEffect);	
	enemyOne->OnFire().AddObserver(&PlayFireSoundEffect);	
	enemyTwo->OnFire().AddObserver(&PlayFireSoundEffect);	
	enemyThree->OnFire().AddObserver(&PlayFireSoundEffect);	
	PlayGameMusic();
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
	tankManager->OnGameOver().AddObserver(&LoadMainMenu);	

	// Player one
	std::shared_ptr<Texture> redTankTexture{ Minigin::ResourceManager::Instance()->LoadTexture("Red Tank.png") };
	std::shared_ptr<Texture> redBarrelTexture{ Minigin::ResourceManager::Instance()->LoadTexture("Red Barrel.png") };
	PlayerTankComponent* playerOne{ tankManager->CreatePlayerTank(redTankTexture, redBarrelTexture, 4) };

	// Player two
	std::shared_ptr<Texture> yellowTankTexture{ Minigin::ResourceManager::Instance()->LoadTexture("Yellow Tank.png") };	
	std::shared_ptr<Texture> yellowBarrelTexture{ Minigin::ResourceManager::Instance()->LoadTexture("Yellow Barrel.png") };	
	PlayerTankComponent* playerTwo{ tankManager->CreatePlayerTank(yellowTankTexture, yellowBarrelTexture, 4) };

	PlayerTankComponent::SetLivesShared(false);

	std::pair<glm::ivec2, glm::ivec2> scoreboardPositions{ CalculateVersusScoreboardPositions() };

	std::shared_ptr<Minigin::Font> scoreFont{ Minigin::ResourceManager::Instance()->LoadFont("Arcade.otf", 30) };	
	std::shared_ptr<Minigin::Texture> livesTexture{ Minigin::ResourceManager::Instance()->LoadTexture("Hearth.png") };	

	// Scoreboard player one
	GameObject* scoreboardOneObject{ scene->CreateGameObject("Scoreboard One") };	
	ScoreboardComponent* scoreboardOne{ scoreboardOneObject->CreateComponent<ScoreboardComponent>(scoreFont, livesTexture, 0, playerOne->Lives(), false) };		
	playerOne->OnHit().AddObserver(std::bind(&ScoreboardComponent::UpdateLives, scoreboardOne, std::placeholders::_1));
	playerOne->OnDie().AddObserver(std::bind(&TankManagerComponent::RemoveAllPlayers, tankManager));		
	scoreboardOneObject->SetLocalPosition(scoreboardPositions.first);	

	// Scoreboard player two
	GameObject* scoreboardTwoObject{ scene->CreateGameObject("Scoreboard Two") };
	ScoreboardComponent* scoreboardTwo{ scoreboardTwoObject->CreateComponent<ScoreboardComponent>(scoreFont, livesTexture, 0, playerTwo->Lives(), false) };			
	playerTwo->OnHit().AddObserver(std::bind(&ScoreboardComponent::UpdateLives, scoreboardTwo, std::placeholders::_1));
	playerTwo->OnDie().AddObserver(std::bind(&TankManagerComponent::RemoveAllPlayers, tankManager));			
	scoreboardTwoObject->SetLocalPosition(scoreboardPositions.second);	

	// Input for player tank
	CreateKeyboardAndMouseInput(playerOne);
	CreateControllerInput(playerOne, 1);
	CreateControllerInput(playerTwo, 0);

	// Audio
	playerOne->OnFire().AddObserver(&PlayFireSoundEffect);		
	playerOne->OnHit().AddObserver(&PlayHitSoundEffect);		
	playerTwo->OnFire().AddObserver(&PlayFireSoundEffect);	
	playerTwo->OnHit().AddObserver(&PlayHitSoundEffect);	
	PlayGameMusic();	
}

void LoadScoreboard()
{
	SceneManager::Instance()->IsolateScene("Main Menu");		
	SceneManager::Instance()->GetScene("Main Menu")->SetStatus(ControllableObject::Status::Disabled);

	Scene* scene{ SceneManager::Instance()->CreateScene("Scoreboard") };
	
	GameObject* scoreboardOjbect{scene->CreateGameObject("Scoreboard")};
	scoreboardOjbect->CreateComponent<HighscoresComponent>();
}

std::pair<glm::ivec2, glm::ivec2> CalculateVersusScoreboardPositions()	
{
	std::pair<glm::ivec2, glm::ivec2> positions{};

	const glm::ivec2 windowSize{ Minigin::Engine::GetWindowSize() };
	const int offset{ 50 };

	positions.first = glm::ivec2{ windowSize.x / 4, windowSize.y - offset };
	positions.second = glm::ivec2{ windowSize.x - (windowSize.x / 4), windowSize.y - offset };

	return positions;
}
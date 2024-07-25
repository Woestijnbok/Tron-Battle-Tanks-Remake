#include <iostream>
#include <format>

#include "CustomCommands.h"
#include "GameObject.h"
#include "AudioManager.h"
#include "TestObserver.h"

using namespace Minigin;

void TestMusic1::Execute()
{
	AudioManager::Instance()->PlayMusic("test.mp3");	
}

void TestMusic2::Execute()
{
	AudioManager::Instance()->PlayMusic("harmony.mp3");	
}

void TestSoundEffect1::Execute()
{
	AudioManager::Instance()->PlayEffect("sweep.wav");	
}

void TestSoundEffect2::Execute()
{
	AudioManager::Instance()->PlayEffect("game over.wav");		
}

void StopMusic::Execute()
{
	AudioManager::Instance()->StopMusic();	
}

void StopAll::Execute()
{
	AudioManager::Instance()->StopAll();
}

TestLenAbi::TestLenAbi(GameObject* object) :
	GameObjectCommand{ object }
{

}

void TestLenAbi::Execute()
{
	GetGameObject()->GetComponent<TestObserverComponent>()->TestTester();
}

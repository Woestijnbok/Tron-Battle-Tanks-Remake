#include <iostream>
#include <format>

#include "CustomCommands.h"
#include "GameObject.h"
#include "Locator.h"
#include "TestObserver.h"

using namespace Minigin;

void TestMusic1::Execute()
{
	Locator::GetAudio()->PlayMusic("test.mp3");
}

void TestMusic2::Execute()
{
	Locator::GetAudio()->PlayMusic("harmony.mp3");
}

void TestSoundEffect1::Execute()
{
	Locator::GetAudio()->PlaySound("sweep.wav");
}

void TestSoundEffect2::Execute()
{
	Locator::GetAudio()->PlaySound("game over.wav");
}

void StopMusic::Execute()
{
	Locator::GetAudio()->StopMusic();
}

void StopAll::Execute()
{
	Locator::GetAudio()->StopAll();
}

TestLenAbi::TestLenAbi(GameObject* object) :
	GameObjectCommand{ object }
{

}

void TestLenAbi::Execute()
{
	GetGameObject()->GetComponent<TestObserverComponent>()->TestTester();
}

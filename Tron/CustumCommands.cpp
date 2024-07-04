#include <iostream>
#include <format>

#include "CustumCommands.h"
#include "GameObject.h"
#include "Locator.h"

void TestMusic1::Execute(std::chrono::milliseconds deltaTime) const
{
	Locator::GetAudio()->PlayMusic("test.mp3");

	deltaTime;
}

void TestMusic2::Execute(std::chrono::milliseconds deltaTime) const
{
	Locator::GetAudio()->PlayMusic("harmony.mp3");

	deltaTime;
}

void TestSoundEffect1::Execute(std::chrono::milliseconds deltaTime) const
{
	Locator::GetAudio()->PlaySound("sweep.wav");

	deltaTime;
}

void TestSoundEffect2::Execute(std::chrono::milliseconds deltaTime) const
{
	Locator::GetAudio()->PlaySound("game over.wav");

	deltaTime;
}

void StopMusic::Execute(std::chrono::milliseconds deltaTime) const
{
	Locator::GetAudio()->StopMusic();

	deltaTime;
}

void StopAll::Execute(std::chrono::milliseconds deltaTime) const
{
	Locator::GetAudio()->StopAll();

	deltaTime;
}
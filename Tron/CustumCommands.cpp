#include <iostream>
#include <format>

#include "CustumCommands.h"
#include "GameObject.h"
#include "Locator.h"

using namespace Minigin;

void TestMusic1::Execute() const
{
	Locator::GetAudio()->PlayMusic("test.mp3");
}

void TestMusic2::Execute() const
{
	Locator::GetAudio()->PlayMusic("harmony.mp3");
}

void TestSoundEffect1::Execute() const
{
	Locator::GetAudio()->PlaySound("sweep.wav");
}

void TestSoundEffect2::Execute() const
{
	Locator::GetAudio()->PlaySound("game over.wav");
}

void StopMusic::Execute() const
{
	Locator::GetAudio()->StopMusic();
}

void StopAll::Execute() const
{
	Locator::GetAudio()->StopAll();
}
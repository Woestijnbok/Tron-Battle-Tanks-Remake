#include "AudioManager.h"

#include "AudioHelpers.h"

void StopAllAudio()	
{
	Minigin::AudioManager::Instance()->StopAll();
}

void PlayMenuMusic()
{
	Minigin::AudioManager::Instance()->PlayMusic("Menu Music.mp3");
}

void PlayGameMusic()
{
	Minigin::AudioManager::Instance()->PlayMusic("Game Music.mp3");
}

void PlayFireSoundEffect()
{
	Minigin::AudioManager::Instance()->PlayEffect("Fire.wav");
}

void PlayHitSoundEffect(int)
{
	Minigin::AudioManager::Instance()->PlayEffect("Hit.wav");
}
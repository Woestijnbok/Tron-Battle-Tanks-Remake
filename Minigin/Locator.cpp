#include "Locator.h"

using namespace Minigin;

std::unique_ptr<Audio> Locator::m_Audio{};

void Locator::ProvideAudio(Audio* audio)
{
	m_Audio.reset(audio);
}

Audio* Locator::GetAudio()
{
	if (m_Audio.get() == nullptr)
	{
		throw std::runtime_error("Service locater trying to get non provided audio service!");
	}

	return m_Audio.get();
}

void Locator::DestroyAudio()
{
	m_Audio.reset();
}
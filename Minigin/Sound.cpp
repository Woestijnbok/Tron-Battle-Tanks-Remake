#include "Sound.h"

#include <iostream>
#include <thread>
#include <SDL.h>
#include <algorithm>

SoundRequest::SoundRequest(SoundAction action, SoundType type, const std::string& name) :
	m_Action{ action },
	m_Type{ type },
	m_SoundName{ name }
{

}

SoundAction SoundRequest::GetSoundAction() const
{
	return m_Action;
}

SoundType SoundRequest::GetSoundType() const
{
	return m_Type;
}

std::string SoundRequest::GetSoundName() const
{
	return m_SoundName;
}

SDLMixerAudio::SDLMixerAudio(const std::filesystem::path& audioPath) :
	Audio{},
	m_AudioPath{ audioPath },
	m_SoundRequest{},
	m_Music{},
	m_SoundChannels
	{
		std::make_pair(static_cast<Mix_Chunk*>(nullptr), 0),
		std::make_pair(static_cast<Mix_Chunk*>(nullptr), 1),
		std::make_pair(static_cast<Mix_Chunk*>(nullptr), 2),
		std::make_pair(static_cast<Mix_Chunk*>(nullptr), 3),
		std::make_pair(static_cast<Mix_Chunk*>(nullptr), 4),
	},
	m_Mutex{}
{
	if (!std::filesystem::is_directory(m_AudioPath))
	{
		throw std::runtime_error("SDL Mixer Audio constructed with invalid audio asset folder!");
	}

	if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_WAVPACK) == 0)
	{
		throw std::runtime_error(std::string("Mix_Init Error: ") + Mix_GetError());
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, SDL_MIXER_AUDIO_NUMBER_OF_CHANNELS, 2048) == -1)
	{
		throw std::runtime_error(std::string("Mix_OpenAudio Error: ") + Mix_GetError());	
	}
}

SDLMixerAudio::~SDLMixerAudio()
{
	Mix_FreeMusic(m_Music);

	for (const auto& pair : m_SoundChannels)
	{
		Mix_FreeChunk(pair.first);
	}

	Mix_CloseAudio();
	Mix_Quit();
}

void SDLMixerAudio::Update()
{
	std::unique_lock lock{ m_Mutex };

	while (!m_SoundRequest.empty())
	{
		ProcessSoundRequest(m_SoundRequest.front());

		m_SoundRequest.pop();
	}

	CheckSoundChannels();
}

void SDLMixerAudio::PlayMusic(const std::string& name)
{
	m_SoundRequest.push(SoundRequest{ SoundAction::Play, SoundType::Music, name });
}

void SDLMixerAudio::PlaySound(const std::string& name)
{
	m_SoundRequest.push(SoundRequest{ SoundAction::Play, SoundType::Effect, name });
}

void SDLMixerAudio::StopMusic()
{
	m_SoundRequest.push(SoundRequest{ SoundAction::Stop, SoundType::Music, "" });
}

void SDLMixerAudio::StopAll()
{
	m_SoundRequest.push(SoundRequest{ SoundAction::Stop, SoundType::All, "" });
}

void SDLMixerAudio::ProcessSoundRequest(const SoundRequest& request)
{
	const std::string path{ m_AudioPath.string() + '/' + request.GetSoundName() };

	switch (request.GetSoundType())
	{
	case SoundType::Music:
		// either play or stop music
		if (request.GetSoundAction() == SoundAction::Play)
		{
			StartPlayingMusic(path);
		}
		else if (request.GetSoundAction() == SoundAction::Stop)
		{
			StopPlayingMusic();
		}
		break;
	case SoundType::Effect:
		// only play effect
		StartPlayingSound(path);
		break;
	case SoundType::All:
		// only stop all
		StopAllSoundsAndMusic();
		break;
	}
}

void SDLMixerAudio::StartPlayingMusic(const std::string& path)
{
	Mix_FreeMusic(m_Music);
	m_Music = nullptr;

	m_Music = Mix_LoadMUS(path.c_str());
	if (!m_Music)
	{
		throw std::runtime_error("failed to load music - " + path);
	}

	if (Mix_PlayMusic(m_Music, -1) == -1)
	{
		throw std::runtime_error("failed to play music - " + path);
	}
}

void SDLMixerAudio::StartPlayingSound(const std::string& path)
{
	const auto it{ std::ranges::find_if(m_SoundChannels, [](const std::pair<Mix_Chunk*, int>& pair) -> bool { return pair.first == nullptr; }) };
	if (it == m_SoundChannels.end())
	{
		throw std::runtime_error("failed find open sound channel - " + path);
	}

	Mix_Chunk* sound{ Mix_LoadWAV(path.c_str()) };
	if (!sound)
	{
		throw std::runtime_error("failed to load sound - " + path);
	}

	it->first = sound;
	if (Mix_PlayChannel(it->second, it->first, 0) == -1)
	{
		throw std::runtime_error("failed to play sound - " + path);
	}
}

void SDLMixerAudio::StopPlayingMusic()
{
	Mix_FreeMusic(m_Music);
	m_Music = nullptr;
}

void SDLMixerAudio::CheckSoundChannels()
{
	std::ranges::for_each
	(
		m_SoundChannels, [](std::pair<Mix_Chunk*, int>& pair) -> void
		{
			if (pair.first != nullptr)
			{
				if (Mix_Playing(pair.second) == 0)
				{
					Mix_FreeChunk(pair.first);
					pair.first = nullptr;
				}
			}
		}
	);
}

void SDLMixerAudio::StopAllSoundsAndMusic()
{
	StopPlayingMusic();

	std::ranges::for_each
	(
		m_SoundChannels, [](std::pair<Mix_Chunk*, int>& pair) -> void
		{
			Mix_FreeChunk(pair.first);
			pair.first = nullptr;
		}
	);
}
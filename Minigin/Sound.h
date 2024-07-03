#ifndef SOUND_AUDIO
#define SOUND_AUDIO

#define SDL_MIXER_AUDIO_NUMBER_OF_CHANNELS 5

#include <string>
#include <SDL_mixer.h>
#include <filesystem>
#include <array>
#include <queue>
#include <mutex>

enum class SoundAction
{
	Play,
	Stop,
};

enum class SoundType
{
	Music,	
	Effect,	
	All						
};

class Audio
{
public:
	Audio() = default;
	virtual ~Audio() = default;

	Audio(const Audio&) = delete;
	Audio(Audio&&) = delete;
	Audio& operator= (const Audio&) = delete;
	Audio& operator= (const Audio&&) = delete;

	virtual void Update() = 0;
	virtual void PlayMusic(const std::string& name) = 0;
	virtual void PlaySound(const std::string& name) = 0;	
	virtual void StopMusic() = 0;
	virtual void StopAll() = 0;

protected:


private:

};

class SoundRequest final
{
public:
	SoundRequest(SoundAction action, SoundType type, const std::string& name);
	virtual ~SoundRequest() = default;

	SoundRequest(const SoundRequest&) = default;
	SoundRequest(SoundRequest&&) = default;
	SoundRequest& operator= (const SoundRequest&) = delete;
	SoundRequest& operator= (const SoundRequest&&) = delete;

	SoundAction GetSoundAction() const;
	SoundType GetSoundType() const;
	std::string GetSoundName() const;

private:
	const SoundAction m_Action;
	const SoundType m_Type;
	const std::string m_SoundName;

};

class SDLMixerAudio final : public Audio
{
public:
	SDLMixerAudio();
	virtual ~SDLMixerAudio();

	SDLMixerAudio(const SDLMixerAudio&) = delete;
	SDLMixerAudio(SDLMixerAudio&&) = delete;
	SDLMixerAudio& operator= (const SDLMixerAudio&) = delete;
	SDLMixerAudio& operator= (const SDLMixerAudio&&) = delete;

	virtual void Update() override;
	virtual void PlayMusic(const std::string& name) override;
	virtual void PlaySound(const std::string& name) override;
	virtual void StopMusic() override;
	virtual void StopAll() override;

private:
	std::queue<SoundRequest> m_SoundRequest;
	Mix_Music* m_Music;
	std::array<std::pair<Mix_Chunk*, int>, SDL_MIXER_AUDIO_NUMBER_OF_CHANNELS> m_SoundChannels;
	std::mutex m_Mutex;

	void ProcessSoundRequest(const SoundRequest& request);
	void StartPlayingMusic(const std::string& file);
	void StartPlayingSound(const std::string& file);
	void StopPlayingMusic();
	void StopAllSoundsAndMusic();
	void CheckSoundChannels();
};

#endif
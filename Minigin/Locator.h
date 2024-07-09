#pragma once

#include "Sound.h"

namespace Minigin
{
	class Locator final
	{
	public:
		Locator() = default;
		~Locator() = default;

		Locator(const Locator&) = delete;
		Locator(Locator&&) = delete;
		Locator& operator= (const Locator&) = delete;
		Locator& operator= (const Locator&&) = delete;

		static void ProvideAudio(Audio* audio);
		static Audio* GetAudio();
		static void DestroyAudio();

	private:
		static std::unique_ptr<Audio> m_Audio;

	};
}
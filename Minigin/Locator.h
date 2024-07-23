#pragma once

#include "Sound.h"

namespace Minigin
{
	class Locator final
	{
	public:
		explicit Locator() = default;
		~Locator() = default;

		Locator(const Locator&) = delete;
		Locator(Locator&&) noexcept = delete;
		Locator& operator= (const Locator&) = delete;
		Locator& operator= (const Locator&&) noexcept = delete;

		static void ProvideAudio(Audio* audio);
		static Audio* GetAudio();
		static void DestroyAudio();

	private:
		static std::unique_ptr<Audio> m_Audio;

	};
}
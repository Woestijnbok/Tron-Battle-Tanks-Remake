#pragma once

#if _DEBUG
#include <vld.h>
#endif

#include <string>
#include <functional>
#include <chrono>

struct SDL_Window;

namespace Minigin	
{
	class Engine
	{
	public:

		Engine() = delete;
		~Engine() = delete;

		Engine(const Engine& other) = delete;
		Engine(Engine&& other) = delete;
		Engine& operator=(const Engine& other) = delete;
		Engine& operator=(Engine&& other) = delete;

		static void Initialize(const std::string& nameWindow);
		static void Run(const std::function<void()>& load);
		static void Destroy();

	private:

		static SDL_Window* m_Window;
		static const int m_TargetFrameRate;
		static const std::chrono::milliseconds m_TargetFrameDuration;
	};
}
#pragma once

#if _DEBUG
#include <vld.h>
#endif

#include <string>
#include <functional>
#include <chrono>

struct SDL_Window;

class Minigin
{
public:

	Minigin() = delete;
	~Minigin() = delete;

	Minigin(const Minigin& other) = delete;
	Minigin(Minigin&& other) = delete;
	Minigin& operator=(const Minigin& other) = delete;
	Minigin& operator=(Minigin&& other) = delete;

	static void Initialize(const std::string& nameWindow);	
	static void Run(const std::function<void()>& load);	
	static void Destroy();

private:

	static SDL_Window* m_Window;	
	static const int m_TargetFrameRate;
	static const std::chrono::milliseconds m_TargetFrameDuration;			
};
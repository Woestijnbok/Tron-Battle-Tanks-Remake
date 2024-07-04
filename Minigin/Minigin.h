#ifndef MINIGIN
#define MINIGIN

#if _DEBUG
#include <vld.h>
#endif

#include <string>
#include <functional>
#include <chrono>

#include "Component.h"

class GameObject;
struct SDL_Window;

class Minigin
{
public:

	static const int m_TargetFrameRate;
	static const std::chrono::milliseconds m_FixedFrameDuration;

	static void Initialize(const std::string& nameWindow);	
	static void Run(const std::function<void()>& load);	
	static void Destroy();

private:

	static SDL_Window* m_Window;	
	static const std::chrono::milliseconds m_TargetFrameDuration;	

	Minigin() = delete;	
	~Minigin() = delete;	

	Minigin(const Minigin& other) = delete;	
	Minigin(Minigin&& other) = delete;	
	Minigin& operator=(const Minigin& other) = delete;		
	Minigin& operator=(Minigin&& other) = delete;		
};

#endif
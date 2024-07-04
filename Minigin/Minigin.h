#ifndef MINIGIN
#define MINIGIN

#if _DEBUG
#include <vld.h>
#endif

#include <string>
#include <functional>
#include <chrono>

class GameObject;
struct SDL_Window;

class Minigin
{
public:

	explicit Minigin(const std::string& nameWindow);
	~Minigin();

	Minigin(const Minigin& other) = delete;
	Minigin(Minigin&& other) = delete;
	Minigin& operator=(const Minigin& other) = delete;
	Minigin& operator=(Minigin&& other) = delete;

	void Run(const std::function<void()>& load);

private:

	SDL_Window* m_Window;
	const int m_TargetFrameRate;
	const std::chrono::milliseconds m_TargetFrameDuration;
	const std::chrono::milliseconds m_FixedFrameDuration;
};

#endif
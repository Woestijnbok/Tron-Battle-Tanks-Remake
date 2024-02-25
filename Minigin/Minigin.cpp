#define WIN32_LEAN_AND_MEAN 

#include <stdexcept>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <thread>
#include <memory>
#include <iostream>

#include "Minigin.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TextComponent.h"

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

Minigin::Minigin(const std::string &dataPath) :
	m_Window{},
	m_MaxFrameRate{ 60 },
	m_MinFrameDuration{ CalculateMinFrameDuration(m_MaxFrameRate) },
	m_FixedDuration{ 20 },
	m_FPSCounter{}
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);

	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
	ResourceManager::GetInstance().Init(dataPath);
}

Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void Minigin::Run(const std::function<void()>& load)
{
	load();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();

	// FPS counter game object
	m_FPSCounter = std::make_shared<GameObject>();
	m_FPSCounter->AddComponent<RenderComponent>(
		std::make_shared<RenderComponent>(m_FPSCounter)
	);
	auto font{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 25) };
	m_FPSCounter->AddComponent<TextComponent>(std::make_shared<TextComponent>(
		m_FPSCounter, "0.0 FPS", font)
	);
	m_FPSCounter->SetPosition(0.0f, 0.0f);
	sceneManager.GetScene("Demo")->Add(m_FPSCounter);

	bool doContinue{ true };
	std::chrono::steady_clock::time_point lastTime{ std::chrono::high_resolution_clock::now() };
	std::chrono::milliseconds lag{};
	while (doContinue)
	{
		const std::chrono::steady_clock::time_point currentTime{ std::chrono::high_resolution_clock::now() };
		const std::chrono::milliseconds deltaTime{ std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime) };
		lastTime = currentTime;
		lag += deltaTime;

		doContinue = input.ProcessInput();
		while (lag >= m_FixedDuration)
		{
			sceneManager.FixedUpdate(m_FixedDuration);
			lag -= m_FixedDuration;
		}
		sceneManager.Update(deltaTime);
		renderer.Render();

		const auto sleepTime{ currentTime + m_MinFrameDuration - std::chrono::high_resolution_clock::now() };
		std::this_thread::sleep_for(sleepTime);

		// Updating the fps counter
		const auto durationCurrentFrame{ std::chrono::high_resolution_clock::now() - currentTime };
		const float framesPerSeconds{ 1.0f / std::chrono::duration<float>(durationCurrentFrame).count() };
		std::ostringstream stream{};
		stream << std::fixed << std::setprecision(1) << framesPerSeconds << " FPS";
		auto text{ m_FPSCounter->GetComponent<TextComponent>() };
		if(text != nullptr) text->SetText(stream.str());
	}
}

std::chrono::milliseconds Minigin::CalculateMinFrameDuration(int frameRate)
{
	if (frameRate <= 0) throw std::runtime_error("Invalid max frame rate!");
	else return std::chrono::milliseconds(static_cast<long long>(1000) / frameRate);
}
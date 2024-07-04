#define WIN32_LEAN_AND_MEAN 

#include <stdexcept>
#include <SDL.h>
#include <thread>
#include <memory>
#include <iostream>

#include "Minigin.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "Locator.h"
#include "Sound.h"

const int Minigin::m_TargetFrameRate{ 60 };
const std::chrono::milliseconds Minigin::m_FixedFrameDuration{ 20 };
SDL_Window* Minigin::m_Window{ nullptr };
const std::chrono::milliseconds Minigin::m_TargetFrameDuration{ 1000 / m_TargetFrameRate };

void Minigin::Initialize(const std::string& nameWindow)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow
	(
		nameWindow.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480,
		SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_INPUT_GRABBED
		| SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_MOUSE_CAPTURE
	);

	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	// Initialize engine features
	Renderer::GetInstance().Init(m_Window);
	ResourceManager::GetInstance().Init();
	Locator::ProvideAudio(new SDLMixerAudio{});
	SceneManager::GetInstance();
	InputManager::GetInstance();
	EventManager::GetInstance();

	std::cout << "Use the escape key to exit the game." << std::endl;
}

void Minigin::Run(const std::function<void()>& load)
{
	load();

	// Cashe engine features
	auto& inputManager{ InputManager::GetInstance() };
	auto& sceneManager{ SceneManager::GetInstance() };
	auto& renderer{ Renderer::GetInstance() };

	bool exit{ false };
	std::chrono::steady_clock::time_point lastTime{ std::chrono::high_resolution_clock::now() };
	std::chrono::milliseconds lag{};
	while (!exit)
	{
		const std::chrono::steady_clock::time_point currentTime{ std::chrono::high_resolution_clock::now() };
		const std::chrono::milliseconds deltaTime{ std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime) };
		lastTime = currentTime;
		lag += deltaTime;

		exit = inputManager.ProcessInput(deltaTime);
		while (lag >= m_FixedFrameDuration)
		{
			sceneManager.FixedUpdate();
			lag -= m_FixedFrameDuration;
		}
		sceneManager.Update(deltaTime);
		EventManager::GetInstance().Update();
		std::thread soundThread{ &Audio::Update, Locator::GetAudio() };
		soundThread.detach();
		renderer.Render();

		std::this_thread::sleep_for(currentTime + m_TargetFrameDuration - std::chrono::high_resolution_clock::now());
	}
}

void Minigin::Destroy()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	Locator::DestroyAudio();
	SDL_Quit();
}
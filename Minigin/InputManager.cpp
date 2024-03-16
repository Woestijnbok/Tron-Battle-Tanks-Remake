#include <iostream>

#include "InputManager.h"
#include "../3rdParty/imgui-1.90.4/backends/imgui_impl_sdl2.h"

InputManager::~InputManager()
{
	for (auto& mapping : m_InputMappingContexts)
	{
		delete mapping.second;
	}
}

bool InputManager::ProcessInput(std::chrono::milliseconds deltaTime)
{
	SDL_Event event{};

	while (SDL_PollEvent(&event)) 
	{
		if (event.type == SDL_QUIT) 
		{
			return false;
		}
		if (event.type == SDL_KEYDOWN)
		{
			for (auto& mapping : m_InputMappingContexts)
			{
				for (const auto& inputAction : mapping.second->GetInputActions())
				{
					if ((event.key.keysym.sym == inputAction.GetSDLKeyCode()) and (inputAction.GetInputTrigger() == InputTrigger::down))
					{
						inputAction.GetCommand()->Execute(deltaTime);
					}
				}
			}
		}
		if (event.type == SDL_KEYUP)
		{
			for (auto& mapping : m_InputMappingContexts)
			{
				for (const auto& inputAction : mapping.second->GetInputActions())
				{
					if ((event.key.keysym.sym == inputAction.GetSDLKeyCode()) and (inputAction.GetInputTrigger() == InputTrigger::up))
					{
						inputAction.GetCommand()->Execute(deltaTime);
					}
				}
			}
		}

		const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

		for (auto& mapping : m_InputMappingContexts)
		{
			for (const auto& inputAction : mapping.second->GetInputActions())
			{
				if ((keyboardState[SDL_GetScancodeFromKey(inputAction.GetSDLKeyCode())]) and (inputAction.GetInputTrigger() == InputTrigger::pressed))
				{
					inputAction.GetCommand()->Execute(deltaTime);
				}
			}
		}

		ImGui_ImplSDL2_ProcessEvent(&event);
		
	}

	return true;
}

void InputManager::AddInputMappingContext(GameObject* gameObject)
{
	m_InputMappingContexts.emplace(std::make_pair(gameObject, new InputMappingContext{ gameObject }));

	gameObject;
}

InputMappingContext* InputManager::GetInputMappingContext(GameObject* gameObject)
{
	return m_InputMappingContexts[gameObject];
}
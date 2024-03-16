#include <SDL.h>

#include "InputManager.h"
#include "../3rdParty/imgui-1.90.4/backends/imgui_impl_sdl2.h"

InputManager::~InputManager()
{
	for (auto& mapping : m_InputMappingContexts)
	{
		delete mapping.second;
	}
}

bool InputManager::ProcessInput()
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
					if (event.key.keysym.sym == inputAction.GetSDLKeyCode())
					{
						inputAction.GetCommand()->Execute();
					}
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
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
	CopyMemory(&m_PreviousXState, &m_CurrentXState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentXState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentXState);

	auto buttonChanges{ m_CurrentXState.Gamepad.wButtons ^ m_PreviousXState.Gamepad.wButtons };
	auto buttonsPressedThisFrame{ buttonChanges & m_CurrentXState.Gamepad.wButtons };
	auto buttonsReleasedThisFrame{ buttonChanges & (~m_CurrentXState.Gamepad.wButtons) };

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
					if ((event.key.keysym.sym == inputAction.GetSDLKeyCode()) and 
						(inputAction.GetInputTrigger() == InputTrigger::down) and
						(!inputAction.IsControllerInputAction()))
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
					if ((event.key.keysym.sym == inputAction.GetSDLKeyCode()) and 
						(inputAction.GetInputTrigger() == InputTrigger::up) and
						(!inputAction.IsControllerInputAction()))
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
				if ((keyboardState[SDL_GetScancodeFromKey(inputAction.GetSDLKeyCode())]) and 
					(inputAction.GetInputTrigger() == InputTrigger::pressed) and
					(!inputAction.IsControllerInputAction()))
				{
					inputAction.GetCommand()->Execute(deltaTime);
				}
			}
		}

		ImGui_ImplSDL2_ProcessEvent(&event);
		
	}

	for (auto& mapping : m_InputMappingContexts)
	{
		for (const auto& inputAction : mapping.second->GetInputActions())
		{
			if (inputAction.IsControllerInputAction())
			{
				switch (inputAction.GetInputTrigger())
				{
				case InputTrigger::up:
					if (buttonsReleasedThisFrame & inputAction.GetXInputButton())
					{
						inputAction.GetCommand()->Execute(deltaTime);
					}
					break;
				case InputTrigger::pressed:
					if (m_CurrentXState.Gamepad.wButtons & inputAction.GetXInputButton())
					{
						inputAction.GetCommand()->Execute(deltaTime);
					}
					break;
				case InputTrigger::down:
					if (buttonsPressedThisFrame & inputAction.GetXInputButton())
					{
						inputAction.GetCommand()->Execute(deltaTime);
					}
					break;
				}
			}
		}
	}

	SDL_CONTROLLER_BUTTON_A;

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
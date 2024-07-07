#pragma once

#include <unordered_map>
#include <Xinput.h>

#include "Singleton.h"

class InputMappingContext;
class GameObject;

class InputManager final : public Singleton<InputManager>
{
public:
	InputManager() = default;
	~InputManager();

	InputManager(const InputManager&) = delete;
	InputManager(InputManager&&) = delete;
	InputManager& operator= (const InputManager&) = delete;
	InputManager& operator= (const InputManager&&) = delete;

	bool ProcessInput();
	void AddInputMappingContext(GameObject* gameObject);
	InputMappingContext* GetInputMappingContext(GameObject* gameObject);

private:
	std::unordered_map<GameObject*, InputMappingContext*> m_InputMappingContexts;
	XINPUT_STATE m_PreviousXState;
	XINPUT_STATE m_CurrentXState;
};
#ifndef INPUT_MANAGER
#define INPUT_MANAGER

#include <vector>
#include <unordered_map>
#include <optional>
#include <SDL.h>
#include <Windows.h>
#include <Xinput.h>

#include "Singleton.h"
#include "InputMappingContext.h"
#include "Component.h"

class InputManager final : public Singleton<InputManager>
{
public:
	InputManager() = default;
	~InputManager();

	InputManager(const InputManager&) = delete;
	InputManager(InputManager&&) = delete;
	InputManager& operator= (const InputManager&) = delete;
	InputManager& operator= (const InputManager&&) = delete;

	bool ProcessInput(std::chrono::milliseconds deltaTime);
	void AddInputMappingContext(GameObject* gameObject);
	InputMappingContext* GetInputMappingContext(GameObject* gameObject);

private:
	std::unordered_map<GameObject*, InputMappingContext*> m_InputMappingContexts;
	XINPUT_STATE m_PreviousXState;
	XINPUT_STATE m_CurrentXState;
};

#endif
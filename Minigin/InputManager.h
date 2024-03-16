#ifndef INPUT_MANAGER
#define INPUT_MANAGER

#include <vector>
#include <unordered_map>
#include <optional>

#include "Singleton.h"
#include "InputMappingContext.h"

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
};

#endif
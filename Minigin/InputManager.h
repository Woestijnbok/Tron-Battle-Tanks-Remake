#ifndef INPUT_MANAGER
#define INPUT_MANAGER

#include "Singleton.h"

class InputManager final : public Singleton<InputManager>
{
public:
	InputManager() = default;
	~InputManager() = default;

	InputManager(const InputManager&) = delete;
	InputManager(InputManager&&) = delete;
	InputManager& operator= (const InputManager&) = delete;
	InputManager& operator= (const InputManager&&) = delete;

	bool ProcessInput();
};

#endif
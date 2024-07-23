#pragma once

#include <vector>

#include "Singleton.h"
#include "Keyboard.h"
#include "Controller.h"

namespace Minigin
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		friend class Singleton<InputManager>;	

		~InputManager();

		InputManager(const InputManager&) = delete;
		InputManager(InputManager&&) noexcept = delete;
		InputManager& operator= (const InputManager&) = delete;
		InputManager& operator= (const InputManager&&) noexcept = delete;

		bool ProcessInput();
		void AddController();
		Keyboard& GetKeyboard();
		Controller& GetController(unsigned int index);

	private:
		Keyboard m_Keyboard;
		std::vector<Controller> m_Controllers;

		explicit InputManager();

	};
}
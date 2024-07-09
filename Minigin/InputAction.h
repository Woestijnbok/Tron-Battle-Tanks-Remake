#pragma once

#include <SDL_keycode.h>
#include <memory>

namespace Minigin
{
	class GameObject;
	class Command;

	enum class InputTrigger
	{
		up,
		pressed,
		down
	};

	class InputAction final
	{
	public:
		InputAction(bool isController, unsigned int button, InputTrigger trigger, Command* command);
		~InputAction() = default;

		InputAction(const InputAction&) = delete;
		InputAction(InputAction&&) noexcept = default;
		InputAction& operator= (const InputAction&) = delete;
		InputAction& operator= (const InputAction&&) = delete;

		bool IsControllerInputAction() const;
		SDL_KeyCode GetSDLKeyCode() const;
		unsigned int GetXInputButton() const;
		InputTrigger GetInputTrigger() const;
		Command* GetCommand() const;
		std::weak_ptr<GameObject> GetGameObject();

		bool operator==(const InputAction& rhs) const;
		bool operator<(const InputAction& rhs) const;

		friend struct std::hash<InputAction>;

	private:
		bool m_IsControllerInputAction;
		unsigned int m_Button;
		InputTrigger m_Trigger;
		std::unique_ptr<Command> m_Command;

	};
}

template<>
struct std::hash<Minigin::InputAction>
{
	std::size_t operator()(const Minigin::InputAction& inputAction) const;
};
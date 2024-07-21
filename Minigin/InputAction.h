#pragma once

#include <memory>

namespace Minigin
{
	class Command;

	class InputAction final
	{
	public:
		enum class Trigger : unsigned int
		{
			Up,			// When key is released this frame.
			Pressed,	// When key is pressed this frame.
			Down        // When key is down.
		};

		InputAction(unsigned int button, InputAction::Trigger trigger, Command* command);
		~InputAction() = default;

		InputAction(const InputAction&) = delete;
		InputAction(InputAction&&) noexcept = default;
		InputAction& operator= (const InputAction&) = delete;
		InputAction& operator= (const InputAction&&) = delete;

		unsigned int GetButton() const;
		InputAction::Trigger GetTrigger() const;
		Command* GetCommand() const;

	private:
		unsigned int m_Button;
		InputAction::Trigger m_Trigger;
		std::unique_ptr<Command> m_Command;

	};
}
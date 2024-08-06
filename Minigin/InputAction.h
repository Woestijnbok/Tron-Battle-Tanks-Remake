#pragma once

#include <variant>
#include <memory>
#include <utility>
#include <vec2.hpp>

namespace Minigin
{
	class Command;

	class InputAction final
	{
	public:
		using Value = std::variant<bool, float, glm::vec2>;

		enum class Trigger : unsigned int
		{
			Up,			// When key is released this frame.
			Pressed,	// When key is pressed this frame.
			Down        // When key is down.
		};

		/*
		*  @param valueType can be bool, float and glm::vec2.
		*  We are using a std::variant to denote the possible types.
		*/
		explicit InputAction(unsigned int button, const Value& valueType, InputAction::Trigger trigger, const std::shared_ptr<Command>& command, bool negate, bool swizzle);
		~InputAction() = default;

		InputAction(const InputAction&) = delete;
		InputAction(InputAction&&) noexcept = default;
		InputAction& operator= (const InputAction&) = delete;
		InputAction& operator= (const InputAction&&) noexcept = delete;
		
		unsigned int GetButton() const;
		const Value& GetValueType() const;
		Trigger GetTrigger() const;
		Command* GetCommand() const;
		bool HasNegate() const;
		bool HasSwizzle() const;

	private:
		const unsigned int m_Button;
		const Value m_ValueType;
		const InputAction::Trigger m_Trigger;
		const std::shared_ptr<Command> m_Command;		
		const bool m_Negate;
		const bool m_Swizzle;
	};
}
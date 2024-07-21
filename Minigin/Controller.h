#pragma once

#include <memory>

#include "InputAction.h"

namespace Minigin	
{
	class Controller final
	{
	public:
		enum class Button : unsigned int
		{
			Y,
			B,
			A,
			X,
			DpadUp,
			DpadRight,
			DpadDown,
			DpadLeft,
			RightShoulder,
			RightTrigger,
			LeftShoulder,
			LeftTrigger,
			Start,
			Back
		};

		Controller(unsigned int index);
		~Controller();

		Controller(const Controller& other) = delete;
		Controller(Controller&& other) noexcept;
		Controller& operator=(const Controller& other) = delete;
		Controller& operator=(Controller&& other) noexcept = delete;

		void ProcessInput();
		void AddInputAction(Controller::Button button, InputAction::Trigger trigger, Command* command);
		void ClearInputActions();
		unsigned int GetIndex() const;

	private:
		class Impl;
		std::unique_ptr<Controller::Impl> m_Pimpl;

	};
}
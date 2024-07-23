#include <vector>
#include <windows.h>
#include <Xinput.h>

#include "Controller.h"
#include "Command.h"

using namespace Minigin;

class Controller::Impl
{
public:
	explicit Impl(unsigned int index);	
	~Impl() = default;		

	Impl(const Impl& other) = delete;
	Impl(Impl&& other) noexcept = default;
	Impl& operator=(const Impl& other) = delete;
	Impl& operator=(Impl&& other) noexcept = delete;

	void ProcessInput();
	void AddInputAction(Controller::Button button, InputAction::Trigger trigger, Command* command);
	void ClearInputActions();
	unsigned int GetIndex() const;

private:
	unsigned int m_Index;
	std::vector<InputAction> m_InputActions;
	XINPUT_STATE m_PreviousState;
	XINPUT_STATE m_CurrentState;

	unsigned int ConvertButton(Controller::Button button) const;

};

Controller::Impl::Impl(unsigned int index) :
	m_Index{ index },
	m_InputActions{},
	m_PreviousState{},
	m_CurrentState{}
{

}

void Controller::Impl::ProcessInput()
{
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));

	if(XInputGetState(static_cast<DWORD>(m_Index), &m_CurrentState) != ERROR_SUCCESS) return;	
		
	WORD buttonChanges{ static_cast<WORD>(m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons) };		
	WORD buttonsPressedThisFrame{ static_cast<WORD>(buttonChanges & m_CurrentState.Gamepad.wButtons) };		
	WORD buttonsReleasedThisFrame{ static_cast<WORD>(buttonChanges & (~m_CurrentState.Gamepad.wButtons)) };			

	for (const InputAction& inputAction : m_InputActions)
	{
		switch (inputAction.GetTrigger())
		{
		case InputAction::Trigger::Down:
			if (m_CurrentState.Gamepad.wButtons & static_cast<WORD>(inputAction.GetButton()))
			{
				inputAction.GetCommand()->Execute();	
			}
			break;
		case InputAction::Trigger::Pressed:
			if (buttonsPressedThisFrame & static_cast<WORD>(inputAction.GetButton()))
			{
				inputAction.GetCommand()->Execute();	
			}
			break;
		case InputAction::Trigger::Up:	
			if (buttonsReleasedThisFrame & static_cast<WORD>(inputAction.GetButton()))
			{
				inputAction.GetCommand()->Execute();
			}
			break;
		}
	}
}

void Controller::Impl::AddInputAction(Controller::Button button, InputAction::Trigger trigger, Command* command)
{
	m_InputActions.emplace_back(ConvertButton(button), trigger, command);	
}

void Controller::Impl::ClearInputActions()
{
	m_InputActions.clear();
}

unsigned int Controller::Impl::GetIndex() const
{
	return m_Index;
}

unsigned int Controller::Impl::ConvertButton(Controller::Button button) const
{
	switch (button)
	{
	case Minigin::Controller::Button::Y:
		return static_cast<unsigned int>(XINPUT_GAMEPAD_Y);
		break;
	case Minigin::Controller::Button::B:
		return static_cast<unsigned int>(XINPUT_GAMEPAD_B);	
		break;
	case Minigin::Controller::Button::A:
		return static_cast<unsigned int>(XINPUT_GAMEPAD_A);	
		break;
	case Minigin::Controller::Button::X:
		return static_cast<unsigned int>(XINPUT_GAMEPAD_X);	
		break;	
	case Minigin::Controller::Button::DpadUp:
		return static_cast<unsigned int>(XINPUT_GAMEPAD_DPAD_UP);		
		break;
	case Minigin::Controller::Button::DpadRight:
		return static_cast<unsigned int>(XINPUT_GAMEPAD_DPAD_RIGHT);	
		break;
	case Minigin::Controller::Button::DpadDown:
		return static_cast<unsigned int>(XINPUT_GAMEPAD_DPAD_DOWN);	
		break;
	case Minigin::Controller::Button::DpadLeft:
		return static_cast<unsigned int>(XINPUT_GAMEPAD_DPAD_LEFT);
		break;
	case Minigin::Controller::Button::RightShoulder:
		return static_cast<unsigned int>(XINPUT_GAMEPAD_RIGHT_SHOULDER);	
		break;
	case Minigin::Controller::Button::RightTrigger:
		return static_cast<unsigned int>(XINPUT_GAMEPAD_RIGHT_THUMB);
		break;
	case Minigin::Controller::Button::LeftShoulder:
		return static_cast<unsigned int>(XINPUT_GAMEPAD_LEFT_SHOULDER);	
		break;
	case Minigin::Controller::Button::LeftTrigger:
		return static_cast<unsigned int>(XINPUT_GAMEPAD_LEFT_THUMB);	
		break;
	case Minigin::Controller::Button::Start:
		return static_cast<unsigned int>(XINPUT_GAMEPAD_START);
		break;
	case Minigin::Controller::Button::Back:
		return static_cast<unsigned int>(XINPUT_GAMEPAD_BACK);
		break;
	default:
		return 0U;
		break;
	}
}

Controller::Controller(unsigned int index) :	
	m_Pimpl{ std::make_unique<Controller::Impl>(index) }
{

}

Controller::~Controller() = default;

Controller::Controller(Controller&& other) noexcept = default;

void Controller::ProcessInput()
{
	m_Pimpl->ProcessInput();
}

void Controller::AddInputAction(Controller::Button button, InputAction::Trigger trigger, Command* command)
{
	m_Pimpl->AddInputAction(button, trigger, command);
}

void Controller::ClearInputActions()
{
	m_Pimpl->ClearInputActions();
}

unsigned int Controller::GetIndex() const
{
	return m_Pimpl->GetIndex();
}
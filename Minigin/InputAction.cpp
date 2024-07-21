#include "InputAction.h"
#include "Command.h"
#include "GameObject.h"

using namespace Minigin;

InputAction::InputAction(unsigned int button, InputAction::Trigger trigger, Command* command) :
	m_Button{ button },
	m_Trigger{ trigger },
	m_Command{ command }
{

}

Command* InputAction::GetCommand() const
{
	return m_Command.get();
}

unsigned int InputAction::GetButton() const
{
	return m_Button;
}

InputAction::Trigger InputAction::GetTrigger() const
{
	return m_Trigger;
}
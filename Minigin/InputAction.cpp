#include "InputAction.h"
#include "Command.h"
#include "GameObject.h"

using namespace Minigin;

InputAction::InputAction(unsigned int button, const Value& valueType, InputAction::Trigger trigger, const std::shared_ptr<Command>& command, bool negate, bool swizzle) :
	m_Button{ button },	
	m_ValueType{ valueType },		
	m_Trigger{ trigger },
	m_Command{ command },
	m_Negate{ negate },
	m_Swizzle{ /*std::holds_alternative<glm::ivec2>(valueType) ? swizzle : false*/ swizzle }	
{
	
}

unsigned int InputAction::GetButton() const
{
	return m_Button;
}

const InputAction::Value& InputAction::GetValueType() const	
{
	return m_ValueType;
}

InputAction::Trigger InputAction::GetTrigger() const
{
	return m_Trigger;
}

Command* InputAction::GetCommand() const
{
	return m_Command.get();	
}

bool InputAction::HasNegate() const
{
	return m_Negate;
}

bool InputAction::HasSwizzle() const
{
	return m_Swizzle;
}
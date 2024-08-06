#include "InputManager.h"

using namespace Minigin;

InputManager::InputManager() :
	m_Mouse{},	
	m_Keyboard{},	
	m_Controllers{}	
{
	m_Keyboard.SetMouse(&m_Mouse);
}

bool InputManager::ProcessInput()
{
	if (m_Keyboard.ProcessInput()) return true;
	else
	{
		m_Mouse.ProcessInput();

		for (Controller& controller : m_Controllers)
		{
			controller.ProcessInput();	
		}

		return false;
	}
}

void Minigin::InputManager::AddController()
{
	m_Controllers.emplace_back(static_cast<unsigned int>(m_Controllers.size()));
}

Keyboard& Minigin::InputManager::GetKeyboard()
{
	return m_Keyboard;
}

Mouse& Minigin::InputManager::GetMouse()
{
	return m_Mouse;
}

Controller& Minigin::InputManager::GetController(unsigned int index)
{
	return m_Controllers.at(static_cast<size_t>(index));	
}
#include "InputManager.h"

using namespace Minigin;


InputManager::InputManager() :		
	m_Keyboard{},
	m_Controllers{}	
{

}

InputManager::~InputManager() = default;

bool InputManager::ProcessInput()
{
	if (m_Keyboard.ProcessInput()) return true;
	else
	{
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

Controller& Minigin::InputManager::GetController(unsigned int index)
{
	return m_Controllers.at(static_cast<size_t>(index));	
}
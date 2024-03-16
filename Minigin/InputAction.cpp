#include "InputAction.h"

InputAction::InputAction(SDL_KeyCode keyCode, InputTrigger trigger, Command* command):
	m_KeyCode{ keyCode },
	m_Command{ command },
	m_Trigger{ trigger }
{

}

std::weak_ptr<GameObject> InputAction::GetGameObject()
{
	std::weak_ptr<GameObject> gameObject{ std::shared_ptr<GameObject>{ nullptr } };

	GameObjectCommand* gameObjectCommand{ dynamic_cast<GameObjectCommand*>(m_Command.get()) };
	if (gameObjectCommand != nullptr)
	{
		gameObject = std::shared_ptr<GameObject>{ gameObjectCommand->GetGameObject() };
	}

	return gameObject;
}

Command* InputAction::GetCommand() const
{
	return m_Command.get();
}

SDL_KeyCode InputAction::GetSDLKeyCode() const
{
	return m_KeyCode;
}

InputTrigger InputAction::GetInputTrigger() const
{
	return m_Trigger;
}

bool InputAction::operator==(const InputAction& rhs) const
{
	return m_KeyCode == rhs.m_KeyCode;
}

bool InputAction::operator<(const InputAction& rhs) const
{
	return m_KeyCode < rhs.m_KeyCode;
}

std::size_t std::hash<InputAction>::operator()(const InputAction& inputAction) const
{
	return std::hash<int>()(inputAction.m_KeyCode);
}
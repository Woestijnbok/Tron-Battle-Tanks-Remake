#include "InputAction.h"
#include "Command.h"
#include "GameObject.h"

InputAction::InputAction(bool isController, unsigned int button, InputTrigger trigger, Command* command) :
	m_IsControllerInputAction{ isController },
	m_Button{ button },
	m_Trigger{ trigger },
	m_Command{ command }
{

}

bool InputAction::IsControllerInputAction() const
{
	return m_IsControllerInputAction;
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
	return static_cast<SDL_KeyCode>(m_Button);
}

unsigned int InputAction::GetXInputButton() const
{
	return m_Button;
}

InputTrigger InputAction::GetInputTrigger() const
{
	return m_Trigger;
}

bool InputAction::operator==(const InputAction& rhs) const
{
	return m_Button == rhs.m_Button;
}

bool InputAction::operator<(const InputAction& rhs) const
{
	return m_Button < rhs.m_Button;
}

std::size_t std::hash<InputAction>::operator()(const InputAction& inputAction) const
{
	return std::hash<int>()(inputAction.m_Button);
}
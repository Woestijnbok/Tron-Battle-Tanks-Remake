#include "InputMappingContext.h"

using namespace Minigin;

InputMappingContext::InputMappingContext(GameObject* gameObject) :
	m_GameObject{  gameObject },
	m_LinkedToGameObjet{ gameObject != nullptr },
	m_InputActions{}
{

}

std::unordered_set<InputAction>& InputMappingContext::GetInputActions()
{
	return m_InputActions;
}

bool InputMappingContext::operator==(const InputMappingContext& rhs) const
{
	return m_GameObject == rhs.m_GameObject;
}

std::size_t std::hash<InputMappingContext>::operator()(const InputMappingContext& mapping) const
{
	return reinterpret_cast<std::size_t>(mapping.m_GameObject);
}
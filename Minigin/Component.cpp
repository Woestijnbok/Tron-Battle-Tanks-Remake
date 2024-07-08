#include "Component.h"

Component::Component(GameObject* owner) :
	ControllableObject{},
	m_Owner{ owner }
{
	
}

void Component::Update()
{

}

void Component::FixedUpdate()
{

}

void Component::LateUpdate()
{

}

void Component::Render() const
{

}

GameObject* Component::GetOwner() const
{
	return m_Owner;
}
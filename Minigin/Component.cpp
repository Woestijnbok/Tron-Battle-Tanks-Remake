#include "Component.h"

Component::Component(GameObject* owner) :
	m_Owner{ owner }
{
	
}

void Component::Update(std::chrono::milliseconds /*deltaTime*/)
{

}

void Component::FixedUpdate()
{

}

void Component::Render() const
{

}
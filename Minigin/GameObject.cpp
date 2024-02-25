#include <string>

#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"

GameObject::~GameObject() = default;

void GameObject::Update(std::chrono::milliseconds deltaTime)
{
	std::ranges::for_each(m_Components, [&deltaTime](std::shared_ptr<Component> component) -> void { component->Update(deltaTime); });
}

void GameObject::FixedUpdate(std::chrono::milliseconds deltaTime)
{
	std::ranges::for_each(m_Components, [&deltaTime](std::shared_ptr<Component> component) -> void { component->FixedUpdate(deltaTime); });
}

void GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

const Transform& GameObject::GetTransform() const
{
	return m_Transform;
}
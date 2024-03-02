#include <string>
#include <algorithm>
#include <stdexcept>
#include <memory>

#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"

GameObject::~GameObject() = default;

void GameObject::Update(std::chrono::milliseconds deltaTime)
{
	/*std::ranges::for_each(m_Components, [&deltaTime](std::shared_ptr<Component> component) -> void { component->Update(deltaTime); });*/
	for (auto& component : m_Components)
	{
		component->Update(deltaTime);
	}
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

GameObject* GameObject::GetParent() const
{
	return m_Parent;
}

void GameObject::SetParent(GameObject* parent)
{
	// Check if the new parent is valid
	if ((m_Parent != parent) and 
		(std::ranges::none_of(m_Children, [parent](GameObject* child) -> bool { return child == parent; })) and
		(parent != this))
	{
		// Remove itself from the previous parent
		if (m_Parent != nullptr)
		{
			auto it = std::find(m_Parent->m_Children.begin(), m_Parent->m_Children.end(), this);

			if (it != m_Parent->m_Children.end())
			{
				m_Parent->m_Children.erase(it);
			}
		}

		// Set the given parent
		m_Parent = parent;

		// Add itself as a child to the given parent
		if (parent != nullptr)
		{
			parent->m_Children.push_back(this);
		}
	}
	else
	{
		throw std::runtime_error("GameObject::SetParent() - Invalid parent given");
	}
}

size_t GameObject::GetChildCount() const
{
	return m_Children.size();
}

GameObject* GameObject::GetChild(size_t index) const 
{
	return m_Children.at(index);
}
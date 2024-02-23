#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <memory>
#include <chrono>
#include <algorithm>

#include "Transform.h"

class Component;
class Texture2D;

class GameObject final
{
public:

	GameObject() = default;
	virtual ~GameObject();

	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

	void Update(std::chrono::milliseconds deltaTime);
	void FixedUpdate(std::chrono::milliseconds deltaTime);
	void Render() const;
	void SetPosition(float x, float y);

	template<typename Type>
	bool AddComponent(std::shared_ptr<Type> component)
	{
		if ((!HasComponent<Type>()) && (dynamic_cast<Component*>(component.get()) != nullptr))
		{
			m_Components.emplace_back(component);
			return true;
		}
		else return false;
	}

	template<typename Type>
	bool RemoveComponent()
	{
		auto it = std::ranges::remove_if(m_Components, [](const std::shared_ptr<Component> component) -> bool
			{
				return dynamic_cast<Type*>(component.get()) != nullptr;
			}
		);

		if (it != std::cend(m_Components))
		{
			m_Components.erase(it, m_Components.end());
			return true;
		}
		else return false;
	}

	template<typename Type>
	std::shared_ptr<Component> GetComponent()
	{
		auto it = std::ranges::find_if(m_Components, [](const std::shared_ptr<Component> component) -> bool
			{
				return dynamic_cast<Type*>(component.get()) != nullptr;
			}
		);

		if (it != std::cend(m_Components)) return *it;
		else return nullptr;
	}

	template<typename Type>
	bool HasComponent()
	{
		auto it = std::ranges::find_if(m_Components, [](const std::shared_ptr<Component> component) -> bool
			{
				return dynamic_cast<Type*>(component.get()) != nullptr;
			}
		);

		return it != std::cend(m_Components);
	}


private:

	Transform m_Transform{};
	std::vector<std::shared_ptr<Component>> m_Components;
};

#endif
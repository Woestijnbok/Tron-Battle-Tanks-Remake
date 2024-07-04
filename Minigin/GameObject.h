#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <memory>
#include <chrono>
#include <algorithm>
#include <type_traits>

#include "Transform.h"
#include "Scene.h"

class Component;
class Texture2D;

class GameObject final
{
public:

	friend GameObject* Scene::CreateGameObject();	

	~GameObject() = default;

	void Update(std::chrono::milliseconds deltaTime);
	void FixedUpdate();
	void Render() const;
	void SetLocalPosition(float x, float y);
	const Transform& GetWorldTransform();
	const Transform& GetLocalTransform() const;
	void SetLocalTransform(const Transform& transform);
	GameObject* GetParent() const;
	void SetParent(GameObject* parent);
	size_t GetChildCount() const;
	GameObject* GetChild(size_t index) const;

	template<typename Type, typename... Arguments>
	bool AddComponent(Arguments&&... arguments)	
	{
		if ((!HasComponent<Type>()) && (std::is_base_of<Component, Type>::value))	
		{
			m_Components.emplace_back(new Type{ this, std::forward<Arguments>(arguments)... });
			return true;
		}
		else return false;
	}

	template<typename Type>
	bool RemoveComponent()
	{
		auto it = std::ranges::find_if(m_Components, [](const std::unique_ptr<Component> component) -> bool
			{
				return std::dynamic_pointer_cast<Type>(component) != nullptr;
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
	Type* GetComponent()
	{
		auto it = std::ranges::find_if(m_Components, [](const std::unique_ptr<Component> component) -> bool
			{
				return std::dynamic_pointer_cast<Type>(component) != nullptr;
			}
		);

		if (it != std::end(m_Components)) return dynamic_cast<Type*>(it->get());	
		else return nullptr;
	}

	template<typename Type>
	bool HasComponent()
	{
		auto it = std::ranges::find_if(m_Components, [](const std::unique_ptr<Component>& component) -> bool
			{
				return dynamic_cast<Type*>(component.get()) != nullptr;
			}
		);

		return it != std::end(m_Components);
	}


private:

	Transform m_LocalTransform;
	std::pair<bool, Transform> m_WorldTransform;
	std::vector<std::unique_ptr<Component>> m_Components;
	std::vector<GameObject*> m_Children;
	GameObject* m_Parent;

	explicit GameObject() = default;	

	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

	void FlagWorldTransform();
};

#endif
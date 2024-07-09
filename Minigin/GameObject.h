#pragma once

#include <algorithm>
#include <concepts>
#include <type_traits>
#include <memory>
#include <vector>

#include "Transform.h"
#include "Component.h"
#include "ObjectController.h"

namespace Minigin
{
	class Scene;

	template<typename Type>
	concept IsComponent = std::is_base_of_v<Component, Type>;

	class GameObject final : public ControllableObject, public ObjectController<Component>
	{
	public:

		explicit GameObject(Scene* scene);
		~GameObject() = default;

		void SetLocalPosition(float x, float y);
		const Transform& GetWorldTransform();
		const Transform& GetLocalTransform() const;
		void SetLocalTransform(const Transform& transform);
		GameObject* GetParent() const;
		void SetParent(GameObject* parent);
		size_t GetChildCount() const;
		GameObject* GetChild(size_t index) const;

		template<typename Type, typename... Arguments>
			requires IsComponent<Type>
		Type* CreateComponent(Arguments&&... arguments);

		template<typename Type>
			requires IsComponent<Type>
		Type* GetComponent();

	private:

		Transform m_LocalTransform;
		std::pair<bool, Transform> m_WorldTransform;
		std::vector<std::unique_ptr<Component>> m_Components;
		std::vector<GameObject*> m_Children;
		GameObject* m_Parent;
		Scene* const m_Scene;

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void FlagWorldTransform();
	};

	template<typename Type, typename ...Arguments>
		requires IsComponent<Type>
	Type* GameObject::CreateComponent(Arguments && ...arguments)
	{
		if (GetComponent<Type>() == nullptr)
		{
			Component* component{ new Type{ this, std::forward<Arguments>(arguments)... } };
			AddControllableObject(component);

			return dynamic_cast<Type*>(component);
		}
		else return nullptr;
	}

	template<typename Type>
		requires IsComponent<Type>
	Type* GameObject::GetComponent()
	{
		Component* component
		{
			GetControllableObject
			(
				[](Component* component) -> bool
				{
					return dynamic_cast<Type*>(component) != nullptr;
				}
			)
		};

		return dynamic_cast<Type*>(component);
	}
}
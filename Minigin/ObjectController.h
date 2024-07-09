#pragma once

#include <concepts>
#include <type_traits>
#include <vector>
#include <memory>
#include <functional>

#include "ControllableObject.h"

namespace Minigin
{
	template<typename Type>
	concept Controllable = std::is_base_of_v<ControllableObject, Type>;

	template <typename Type>
	concept Updatable = requires(Type object)
	{
		{ object.FixedUpdate() } -> std::same_as<void>;
		{ object.Update() } -> std::same_as<void>;
		{ object.LateUpdate() } -> std::same_as<void>;
	};

	template <typename Type>
	concept Renderable = requires(const Type object)
	{
		{ object.Render() } -> std::same_as<void>;
	};

	template<typename ObjectType>
		requires Controllable<ObjectType>&& Updatable<ObjectType>&& Renderable<ObjectType>
	class ObjectController
	{
	public:

		void FixedUpdate();
		void Update();
		void LateUpdate();
		void Render() const;

	protected:

		void AddControllableObject(ObjectType* object);
		ObjectType* GetControllableObject(const std::function<bool(ObjectType*)>& predicate);

	private:

		size_t m_InitialObjectCount;
		std::vector<std::unique_ptr<ObjectType>> m_EnabledObjects;
		std::vector<std::unique_ptr<ObjectType>> m_DisabledObjects;

		void CheckDestroyedObjects();
		void CheckDisabledObjects();
		void CheckEnabledObjects();

	};

	template<typename ObjectType>
		requires Controllable<ObjectType>&& Updatable<ObjectType>&& Renderable<ObjectType>
	void ObjectController<ObjectType>::FixedUpdate()
	{
		m_InitialObjectCount = m_EnabledObjects.size();

		for (size_t i{}; i < m_InitialObjectCount; ++i)
		{
			if (m_EnabledObjects.at(i)->GetStatus() == ControllableObject::Status::Enabled)
			{
				m_EnabledObjects.at(i)->FixedUpdate();
			}
		}

	}

	template<typename ObjectType>
		requires Controllable<ObjectType>&& Updatable<ObjectType>&& Renderable<ObjectType>
	void ObjectController<ObjectType>::Update()
	{
		m_InitialObjectCount = m_EnabledObjects.size();

		for (size_t i{}; i < m_InitialObjectCount; ++i)
		{
			if (m_EnabledObjects.at(i)->GetStatus() == ControllableObject::Status::Enabled)
			{
				m_EnabledObjects.at(i)->Update();
			}
		}
	}

	template<typename ObjectType>
		requires Controllable<ObjectType>&& Updatable<ObjectType>&& Renderable<ObjectType>
	void ObjectController<ObjectType>::LateUpdate()
	{
		m_InitialObjectCount = m_EnabledObjects.size();

		for (size_t i{}; i < m_InitialObjectCount; ++i)
		{
			if (m_EnabledObjects.at(i)->GetStatus() == ControllableObject::Status::Enabled)
			{
				m_EnabledObjects.at(i)->LateUpdate();
			}
		}

		CheckDestroyedObjects();
		CheckDisabledObjects();
		CheckEnabledObjects();
	}

	template<typename ObjectType>
		requires Controllable<ObjectType>&& Updatable<ObjectType>&& Renderable<ObjectType>
	void ObjectController<ObjectType>::Render() const
	{
		for (const auto& object : m_EnabledObjects)
		{
			object->Render();
		}
	}

	template<typename ObjectType>
		requires Controllable<ObjectType>&& Updatable<ObjectType>&& Renderable<ObjectType>
	void ObjectController<ObjectType>::AddControllableObject(ObjectType* object)
	{
		if (object->GetStatus() == ControllableObject::Status::Enabled)
		{
			m_EnabledObjects.emplace_back(object);
		}
		else
		{
			m_DisabledObjects.emplace_back(object);
		}
	}

	template<typename ObjectType>
		requires Controllable<ObjectType>&& Updatable<ObjectType>&& Renderable<ObjectType>
	ObjectType* ObjectController<ObjectType>::GetControllableObject(const std::function<bool(ObjectType*)>& predicate)
	{
		auto it
		{
			std::ranges::find_if
			(
				m_EnabledObjects,
				[&predicate](const std::unique_ptr<ObjectType>& object) -> bool
				{
					return predicate(object.get());
				}
			)
		};

		if (it == std::end(m_EnabledObjects))
		{
			it = std::ranges::find_if
			(
				m_DisabledObjects,
				[&predicate](const std::unique_ptr<ObjectType>& object) -> bool
				{
					return predicate(object.get());
				}
			);
		}

		if (it == std::end(m_DisabledObjects)) return nullptr;
		else return it->get();
	}

	template<typename ObjectType>
		requires Controllable<ObjectType>&& Updatable<ObjectType>&& Renderable<ObjectType>
	void ObjectController<ObjectType>::CheckDestroyedObjects()
	{
		m_EnabledObjects.erase
		(
			std::remove_if
			(
				std::begin(m_EnabledObjects), std::end(m_EnabledObjects), [](const std::unique_ptr<ObjectType>& object) -> bool { return object->GetStatus() == ControllableObject::Status::Destroyed; }
			)
			, m_EnabledObjects.end()
		);

		m_DisabledObjects.erase
		(
			std::remove_if
			(
				std::begin(m_DisabledObjects), std::end(m_DisabledObjects), [](const std::unique_ptr<ObjectType>& object) -> bool { return object->GetStatus() == ControllableObject::Status::Destroyed; }
			)
			, m_DisabledObjects.end()
		);
	}

	template<typename ObjectType>
		requires Controllable<ObjectType>&& Updatable<ObjectType>&& Renderable<ObjectType>
	void ObjectController<ObjectType>::CheckDisabledObjects()
	{
		auto it = std::remove_if
		(
			std::begin(m_EnabledObjects),
			std::end(m_EnabledObjects),
			[](const std::unique_ptr<ObjectType>& object) -> bool { return object->GetStatus() == ControllableObject::Status::Disabled; }
		);

		if (it != m_EnabledObjects.end())
		{
			m_DisabledObjects.push_back(std::move(*it));
			m_EnabledObjects.erase(it);
		}
	}

	template<typename ObjectType>
		requires Controllable<ObjectType>&& Updatable<ObjectType>&& Renderable<ObjectType>
	void ObjectController<ObjectType>::CheckEnabledObjects()
	{
		auto it = std::remove_if
		(
			std::begin(m_DisabledObjects),
			std::end(m_DisabledObjects),
			[](const std::unique_ptr<ObjectType>& object) -> bool { return object->GetStatus() == ControllableObject::Status::Enabled; }
		);

		if (it != m_DisabledObjects.end())
		{
			m_EnabledObjects.push_back(std::move(*it));
			m_DisabledObjects.erase(it);
		}
	}
}
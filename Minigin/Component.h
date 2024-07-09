#pragma once

#include "ControllableObject.h"

namespace Minigin
{
	class GameObject;

	class Component : public ControllableObject
	{
	public:
		Component(GameObject* owner);
		virtual ~Component() = default;

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Update();
		virtual void FixedUpdate();
		virtual void LateUpdate();
		virtual void Render() const;

	protected:

		GameObject* GetOwner() const;

	private:

		GameObject* const m_Owner;
	};
}
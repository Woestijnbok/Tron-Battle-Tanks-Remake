#ifndef COMPONENT
#define COMPONENT

#include <chrono>

#include "GameObject.h"

class Component
{
public:

	Component(std::weak_ptr<GameObject> owner);
	virtual ~Component() = default;

	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;

	virtual void Update(std::chrono::milliseconds deltaTime) = 0;
	virtual void FixedUpdate(std::chrono::milliseconds deltaTime) = 0;

protected:

	const std::weak_ptr<GameObject> m_Owner;
};

#endif
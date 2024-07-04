#ifndef COMPONENT
#define COMPONENT

#include <chrono>

class GameObject;

class Component
{
public:

	Component(GameObject* owner);
	virtual ~Component() = default;

	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;

	virtual void Update(std::chrono::milliseconds deltaTime);
	virtual void FixedUpdate();
	virtual void Render() const;

protected:

	GameObject * const m_Owner;
};

#endif
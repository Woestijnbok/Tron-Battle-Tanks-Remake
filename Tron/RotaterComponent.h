#ifndef ROTATER_COMPONENT
#define ROTATER_COMPONENT

#include "Component.h"

class RotaterComponent : public Component 
{
public:

	RotaterComponent(std::weak_ptr<GameObject> owner, const glm::vec2& center);
	virtual ~RotaterComponent() = default;

	RotaterComponent(const RotaterComponent&) = delete;
	RotaterComponent(RotaterComponent&&) = delete;
	RotaterComponent& operator= (const RotaterComponent&) = delete;
	RotaterComponent& operator= (const RotaterComponent&&) = delete;

	virtual void Update(std::chrono::milliseconds deltaTime) override;
	virtual void FixedUpdate(std::chrono::milliseconds deltaTime) override;

private:

	const glm::vec2 m_Center;
	const float m_Radius;
	const float m_RotationalSpeed;
	float m_Angle;
};

#endif
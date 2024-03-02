#include <iostream>
#include <chrono>

#include "RotaterComponent.h"

RotaterComponent::RotaterComponent(std::weak_ptr<GameObject> owner, const glm::vec2& center) :
	Component{ owner },
	m_Center{ center },
	m_Radius{ 30 },
	m_RotationalSpeed{ 360.0f },
	m_Angle{ 0.0f }
{
	m_Owner.lock()->SetLocalPosition(center.x, center.y);
}

void RotaterComponent::Update(std::chrono::milliseconds deltaTime)
{
	deltaTime;
}

void RotaterComponent::FixedUpdate(std::chrono::milliseconds deltaTime)
{
	float seconds{ std::chrono::duration_cast<std::chrono::duration<float>>(deltaTime).count() };
	m_Angle += seconds * m_RotationalSpeed;
	if (m_Angle > 360.0f) m_Angle -= 360.0f;

	const float x{ m_Center.x + (m_Radius * glm::cos(glm::radians(m_Angle))) };
	const float y{ m_Center.y + (m_Radius * glm::sin(glm::radians(m_Angle))) };

	m_Owner.lock()->SetLocalPosition(x, y);

	/*auto pos = m_Owner.lock()->GetLocalTransform().GetPosition();
	pos += (seconds * 100);
	m_Owner.lock()->SetLocalPosition(pos.x, pos.y);*/
}
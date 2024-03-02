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
	m_Angle += deltaTime * m_RotationalSpeed;

	const float x{ m_Center.x + (m_Radius * glm::cos(glm::radians(m_RotationalSpeed))) };
	const float y{ m_Center.y + (m_Radius * glm::sin(glm::radians(m_RotationalSpeed))) };

	m_Owner.lock()->SetLocalPosition(x, y);
}
#include "Transform.h"

const glm::vec3& Transform::GetPosition() const
{
	return m_Position; 
}

void Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}
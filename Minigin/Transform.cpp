#include "Transform.h"

Transform::Transform(glm::vec3 position) :
	m_Position{ position }
{

}

Transform::Transform(const Transform& rhs) :
	m_Position{ rhs.m_Position }
{

}

Transform::Transform(Transform&& rhs) :
	m_Position{ rhs.m_Position }
{

}

Transform& Transform::operator=(const Transform& rhs)
{
	m_Position = rhs.m_Position;

	return *this;
}

Transform& Transform::operator=(const Transform&& rhs)
{
	m_Position = rhs.m_Position;

	return *this;
}


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

Transform Transform::operator+(const Transform& rhs) const
{
	glm::vec3 position{ this->m_Position + rhs.m_Position };

	return Transform{ position };
}
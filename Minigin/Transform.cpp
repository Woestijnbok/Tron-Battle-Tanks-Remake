#include "Transform.h"

using namespace Minigin;

Transform::Transform(glm::vec2 position) noexcept :
	m_Position{ position }
{

}

Transform::Transform(const Transform& rhs) noexcept :
	m_Position{ rhs.m_Position }
{

}

Transform::Transform(Transform&& rhs) noexcept :
	m_Position{ rhs.m_Position }
{

}

Transform& Transform::operator=(const Transform& rhs) noexcept
{
	m_Position = rhs.m_Position;

	return *this;
}

Transform& Transform::operator=(const Transform&& rhs) noexcept
{
	m_Position = rhs.m_Position;

	return *this;
}


const glm::vec2& Transform::GetPosition() const
{
	return m_Position; 
}

void Transform::SetPosition(const glm::vec2& position)
{
	m_Position = position;
}

Transform Transform::operator+(const Transform& rhs) const
{
	return Transform{ m_Position + rhs.m_Position };
}

Transform Minigin::Transform::operator-(const Transform& rhs) const
{
	return Transform{ m_Position - rhs.m_Position };
}
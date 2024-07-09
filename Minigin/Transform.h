#pragma once

#include <vec3.hpp>	

namespace Minigin
{
	class Transform final
	{
	public:

		Transform() = default;
		Transform(glm::vec3 position);
		~Transform() = default;

		Transform(const Transform& rhs);
		Transform(Transform&& rhs);
		Transform& operator=(const Transform& rhs);
		Transform& operator=(const Transform&& rhs);

		Transform operator+(const Transform& rhs) const;

		const glm::vec3& GetPosition() const;
		void SetPosition(float x, float y, float z);

	private:

		glm::vec3 m_Position;
	};
}
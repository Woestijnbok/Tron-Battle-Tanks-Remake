#pragma once

#include <vec2.hpp>	

namespace Minigin
{
	class Transform final
	{
	public:

		Transform() noexcept = default;
		Transform(glm::vec2 position) noexcept;
		~Transform() = default;

		Transform(const Transform& rhs) noexcept;
		Transform(Transform&& rhs) noexcept;
		Transform& operator=(const Transform& rhs) noexcept;
		Transform& operator=(const Transform&& rhs) noexcept;

		Transform operator+(const Transform& rhs) const;
		Transform operator-(const Transform& rhs) const;

		const glm::vec2& GetPosition() const;
		void SetPosition(const glm::vec2& position);

	private:

		glm::vec2 m_Position;
	};
}
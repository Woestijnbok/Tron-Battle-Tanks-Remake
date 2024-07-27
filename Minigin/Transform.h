#pragma once

#include <vec2.hpp>	
#include <mat4x4.hpp>

namespace Minigin
{
	class Transform final
	{
	public:
		explicit Transform();
		explicit Transform(glm::ivec2 position, glm::ivec2 rotation, glm::vec2 scale);	
		~Transform() = default;

		Transform(const Transform& rhs);
		Transform(Transform&& rhs) noexcept;
		Transform& operator=(const Transform& rhs);
		Transform& operator=(const Transform&& rhs) noexcept;

		void SetPosition(const glm::ivec2& position);
		void SetRotation(const glm::ivec2& rotation);	
		void SetScale(const glm::vec2& scale);
		const glm::ivec2& GetPosition() const;
		const glm::ivec2& GetRotation() const;		
		const glm::vec2& GetScale() const;
			
	private:
		glm::ivec2 m_Position;
		glm::ivec2 m_Rotation;	
		glm::vec2 m_Scale;
	};
}
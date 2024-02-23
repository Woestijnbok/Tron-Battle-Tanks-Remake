#ifndef TRANSFORM
#define TRANSFORM

#include <glm/glm.hpp>

class Transform final
{
public:

	Transform() = default;
	~Transform() = default;

	Transform(const Transform&) = delete;
	Transform(Transform&&) = delete;
	Transform& operator= (const Transform&) = delete;
	Transform& operator= (const Transform&&) = delete;

	const glm::vec3& GetPosition() const;
	void SetPosition(float x, float y, float z);

private:

	glm::vec3 m_Position;
};

#endif
#include <cmath>

#include "Collision.h"

bool Minigin::PointInsideRectangle(const glm::ivec2& point, const glm::ivec2& bottomLeft, const glm::ivec2 topRight)	
{
	// Not too high
	if (point.y <= topRight.y)
	{
		// Not too right
		if (point.x <= topRight.x)
		{
			// Not too low
			if (point.y >= bottomLeft.y)
			{
				// Not too left
				if (point.x >= bottomLeft.x)
				{
					return true;
				}
			}
		}
	}

	return false;
}

std::optional<glm::ivec2> Minigin::LinesIntersect(const glm::ivec2& a, const glm::ivec2& b, const glm::ivec2& c, const glm::ivec2& d)
{
	std::optional<glm::ivec2> intersection{};

	const glm::vec2 directionOne{ b - a }; // Direction vector of the first line segment						
	const glm::vec2 directionTwo{ d - c }; // Direction vector of the second line segment					

	const float determinant{ directionOne.x * directionTwo.y - directionOne.y * directionTwo.x }; // Determinant				
	const float cross{ (c - a).x * directionOne.y - (c - a).y * directionOne.x }; // Cross product of vectors							

	if (std::fabs(determinant) < std::numeric_limits<float>::epsilon())
	{
		return intersection; // Lines are parallel or collinear	
	}

	const float t{ cross / determinant };
	const float u{ ((c - a).x * directionTwo.y - (c - a).y * directionTwo.x) / determinant };

	if (t >= 0.0f && t <= 1.0f && u >= 0.0f && u <= 1.0f)
	{
		intersection = a + glm::ivec2{ t * directionOne };
		return intersection;
	}
	else return intersection;
}

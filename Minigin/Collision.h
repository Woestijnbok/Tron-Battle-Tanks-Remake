#pragma once

#include <vec2.hpp>
#include <optional>

namespace Minigin
{
	/*
	* @brief returns true if points is inside the rectangle, if the points is on of the edges it also counts as inside
	*/
	bool PointInsideRectangle(const glm::ivec2& point, const glm::ivec2& bottomLeft, const glm::ivec2 topRight);

	/*
	* @checks if two lines intersect if so returns the point of intersection
	*/
	std::optional<glm::ivec2> LinesIntersect(const glm::ivec2& a, const glm::ivec2& b, const glm::ivec2& c, const glm::ivec2& d);
}
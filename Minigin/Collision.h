#pragma once

#include <vec2.hpp>
#include <optional>

namespace Minigin
{
	struct Rectangle final
	{
		glm::ivec2 BottomLeft;
		glm::ivec2 TopRight;
	};

	// Is really a line segment
	struct Line
	{
		glm::ivec2 Start;
		glm::ivec2 End;
	};

	/*
	* @brief returns true if points is inside the rectangle, if the points is on of the edges it also counts as inside
	*/
	bool PointInsideRectangle(const glm::ivec2& point, const Rectangle& rectangle);	

	/*
	* @checks if two lines intersect if so returns the point of intersection
	*/
	std::optional<glm::ivec2> LinesIntersect(const Line& a, const Line& b);	

	/*
	* @checks if two lines intersect if so returns the point of intersection
	*/
	bool RectanglesOverlap(const Rectangle& a, const Rectangle& b);
}
#pragma once

#include <vec2.hpp>

namespace Minigin
{
	/*
	* @brief returns true if points is inside the rectangle, if the points is on of the edges it also counts as inside
	*/
	bool PointInsideRectangle(const glm::ivec2& point, const glm::ivec2& bottomLeft, const glm::ivec2 topRight);	
}
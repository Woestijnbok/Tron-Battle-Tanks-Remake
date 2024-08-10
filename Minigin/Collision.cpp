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
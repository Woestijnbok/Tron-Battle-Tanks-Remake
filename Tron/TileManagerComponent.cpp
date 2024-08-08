#include <exception>
#include <algorithm>
#include <optional>
#include <iostream>
#include <format>

#include "TileManagerComponent.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "GameObject.h"
#include "Renderer.h"
#include "BulletComponent.h"
#include "Scene.h"

TileManagerComponent::TileManagerComponent(Minigin::GameObject* owner, int tileSize) :
	Component{ owner },
	m_Tiles{},
	m_TileZero{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Tiles/Tile Zero.png") },
	m_TileOne{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Tiles/Tile One.png") },
	m_TileTwoCorner{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Tiles/Tile Two Corner.png") },
	m_TileTwoStraight{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Tiles/Tile Two Straight.png") },
	m_TileThree{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Tiles/Tile Three.png") },
	m_TileFour{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Tiles/Tile Four.png") },
	m_TileSize{ tileSize },
	m_CollisionOffset{ 10 }
{
	CreateTiles();
}

glm::ivec2 TileManagerComponent::GetStartPosition() const
{
	return glm::ivec2{ m_TileSize * (int(m_Tiles.size()) / 2), m_TileSize * (int(m_Tiles.size()) / 2) };	
}

bool TileManagerComponent::CanMove(TankComponent const* tank, MoveCommand::Direction direction) const
{
	bool canMove{ false };

	const glm::ivec2 tankPosition{ tank->GetOwner()->GetLocalTransform().GetPosition() };

	const int row{ tankPosition.y / m_TileSize };	
	const int collumn{ tankPosition.x / m_TileSize };	

	switch (direction)
	{
	case MoveCommand::Direction::Up:
		if (tankPosition.x % m_TileSize == 0)
		{
			// cross road
			if (tankPosition.y% m_TileSize == 0)
			{
				// not top edge
				if (row < static_cast<int>(m_Tiles.size()))
				{
					// check if at right edge
					if (collumn == static_cast<int>(m_Tiles.size())) canMove = m_Tiles.at(row).at(collumn - 1)->CanPass(TileComponent::Side::Left);		
					else canMove = m_Tiles.at(row).at(collumn)->CanPass(TileComponent::Side::Left);		
				}
			}
			// between two
			else
			{
				// check if at right edge
				if (collumn == static_cast<int>(m_Tiles.size())) canMove = m_Tiles.at(row).at(collumn - 1)->CanPass(TileComponent::Side::Left);		
				else canMove = m_Tiles.at(row).at(collumn)->CanPass(TileComponent::Side::Left);	
			}
		}
		break;
	case MoveCommand::Direction::Right:
		if (tankPosition.y % m_TileSize == 0)
		{
			// cross road
			if (tankPosition.x % m_TileSize == 0)
			{
				// not right edge
				if (collumn < static_cast<int>(m_Tiles.size()))
				{
					// check if at top edge
					if (row == static_cast<int>(m_Tiles.size())) canMove = m_Tiles.at(row - 1).at(collumn)->CanPass(TileComponent::Side::Bottom);	
					else canMove = m_Tiles.at(row).at(collumn)->CanPass(TileComponent::Side::Bottom);	
				}
			}
			// between two
			else
			{
				// check if at top edge
				if (row == static_cast<int>(m_Tiles.size())) canMove = m_Tiles.at(row - 1).at(collumn)->CanPass(TileComponent::Side::Bottom);	
				else canMove = m_Tiles.at(row).at(collumn)->CanPass(TileComponent::Side::Bottom);	
			}
		}
		break;
	case MoveCommand::Direction::Down:
		if (tankPosition.x % m_TileSize == 0)
		{
			// cross road
			if (tankPosition.y % m_TileSize == 0)
			{
				// not bottom edge
				if (row > 0)
				{
					// check if at right edge
					if (collumn == static_cast<int>(m_Tiles.size())) canMove = m_Tiles.at(row - 1).at(collumn - 1)->CanPass(TileComponent::Side::Left);
					else canMove = m_Tiles.at(row - 1).at(collumn)->CanPass(TileComponent::Side::Left);
				}
			}
			// between two
			else
			{
				// check if at right edge
				if (collumn == static_cast<int>(m_Tiles.size())) canMove = m_Tiles.at(row).at(collumn - 1)->CanPass(TileComponent::Side::Left);
				else canMove = m_Tiles.at(row).at(collumn)->CanPass(TileComponent::Side::Left);
			}
		}
		break;
	case MoveCommand::Direction::Left:
		if (tankPosition.y % m_TileSize == 0)
		{
			// cross road	
			if (tankPosition.x % m_TileSize == 0)	
			{
				// not left edge
				if (collumn > 0)
				{
					// check if at top edge
					if (row == static_cast<int>(m_Tiles.size())) canMove = m_Tiles.at(row - 1).at(collumn - 1)->CanPass(TileComponent::Side::Bottom);	
					else canMove = m_Tiles.at(row).at(collumn - 1)->CanPass(TileComponent::Side::Bottom);	
				}
			}
			// between two
			else
			{
				// check if at top edge
				if (row == static_cast<int>(m_Tiles.size())) canMove = m_Tiles.at(row - 1).at(collumn)->CanPass(TileComponent::Side::Bottom);	
				else canMove = m_Tiles.at(row).at(collumn)->CanPass(TileComponent::Side::Bottom);	
			}
		}
		break;
	default:
		break;
	}

	return canMove;
}

void TileManagerComponent::CheckCollision(BulletComponent* bullet) const
{
	std::optional<glm::ivec2> intersection{};	// this is in tile manager space not world

	// We are inside the boundaries
	intersection = CheckBounds(bullet);
	if (!intersection)
	{
		// We did not hit the top collision zone of the tile some tiles have this
		intersection = CheckTop(bullet);
		if (!intersection)
		{
			// We did not hit the right collision zone of the tile some tiles have this
			intersection = CheckRight(bullet);
			if (!intersection)
			{
				// We did not hit the bottom collision zone of the tile some tiles have this
				intersection = CheckBottom(bullet);
				if (!intersection)
				{
					// We did not hit the bottom collision zone of the tile some tiles have this
					intersection = CheckLeft(bullet);
					if (!intersection)
					{
						// We did not hit the center collision zone of the current tile (every tile has one)
						intersection = CheckCenter(bullet);
						if (!intersection)
						{
							intersection;
						}
						else std::cout << "Hit Center" << std::endl;
					}
					else std::cout << "Hit Left" << std::endl;
				}
				else std::cout << "Hit Bottom" << std::endl;
			}
			else std::cout << "Hit Right" << std::endl;
		}
		else std::cout << "Hit Top" << std::endl;
	}
	else std::cout << "Hit bounds" << std::endl;

	if (intersection) bullet->GetOwner()->SetLocalPosition(intersection.value());
}

int TileManagerComponent::GetRotation(TileComponent* tile) const		
{
	int rotation{};
	const int closedSides{ 4 - tile->GetTotalOpenSides() };	

	switch (closedSides)
	{
	case 1:
		if (!tile->CanPass(TileComponent::Side::Bottom)) rotation = 90;	
		else if (!tile->CanPass(TileComponent::Side::Left)) rotation = 180;	
		else if (!tile->CanPass(TileComponent::Side::Top)) rotation = 270;	
		break;
	case 2:
		if (
			(tile->CanPass(TileComponent::Side::Top) and tile->CanPass(TileComponent::Side::Bottom)) or 
			(tile->CanPass(TileComponent::Side::Right) and tile->CanPass(TileComponent::Side::Left))
			)	
		{
			if (!tile->CanPass(TileComponent::Side::Top)) rotation = 90;	
		}
		else
		{
			if (!tile->CanPass(TileComponent::Side::Right) and !tile->CanPass(TileComponent::Side::Bottom)) rotation = 90;
			else if (!tile->CanPass(TileComponent::Side::Bottom) and !tile->CanPass(TileComponent::Side::Left)) rotation = 180;
			else if (!tile->CanPass(TileComponent::Side::Left) and !tile->CanPass(TileComponent::Side::Top)) rotation = 270;
		}
		break;
	case 3:
		if (tile->CanPass(TileComponent::Side::Left)) rotation = 90;
		else if (tile->CanPass(TileComponent::Side::Top)) rotation = 180;
		else if (tile->CanPass(TileComponent::Side::Right)) rotation = 270;

		break;
	default:
		break;
	}

	return rotation;	
}

glm::vec2 TileManagerComponent::GetScale(TileComponent* tile) const
{
	const glm::ivec2 textureSize{ tile->GetTexture()->GetSize()};	

	return glm::vec2{ static_cast<float>(m_TileSize) / textureSize.x, static_cast<float>(m_TileSize) / textureSize.y };
}

void TileManagerComponent::CreateTiles()
{
	const glm::ivec2 startPosition{ m_TileSize / 2, m_TileSize / 2 };
	Minigin::Scene* scene{ GetOwner()->GetScene() };

	for (size_t row{}; row < m_Tiles.size(); ++row)	
	{
		for (size_t collumn{}; collumn < m_Tiles.size(); ++collumn)	
		{
			Minigin::GameObject* object{ scene->CreateGameObject(std::format("Tile ({}, {})", row, collumn)) };
			object->SetParent(GetOwner());	
			auto tile{ object->CreateComponent<TileComponent>(m_TileZero.get()) };	

			object->SetLocalPosition(glm::ivec2{ startPosition.x + (collumn * m_TileSize), startPosition.y + (row * m_TileSize) });	
			object->SetLocalScale(GetScale(tile));	
			object->SetLocalRotation(GetRotation(tile));	

			m_Tiles.at(row).at(collumn) = tile;	
		}
	}
}

bool TileManagerComponent::PointInsideRectangle(const glm::ivec2& point, const glm::ivec2& bottom, const glm::ivec2 top) const
{
	// Not too high
	if (point.y <= top.y)
	{
		// Not too right
		if (point.x <= top.x)
		{
			// Not too low
			if (point.y >= bottom.y)
			{
				// Not too left
				if (point.x >= bottom.x)
				{
					return true;
				}
			}
		}
	}

	return false;
}

std::optional<glm::ivec2> TileManagerComponent::LinesIntersect(const glm::ivec2& a, const glm::ivec2& b, const glm::ivec2& c, const glm::ivec2& d) const
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

std::optional<glm::ivec2> TileManagerComponent::CheckBounds(BulletComponent* bullet) const
{
	std::optional<glm::ivec2> intersection{};
	const glm::ivec2 bulletPosition{ bullet->GetOwner()->GetLocalTransform().GetPosition() };

	// Did we hit or pass the top boundry
	if (bulletPosition.y >= int(m_TileSize * m_Tiles.size()))
	{
		intersection = glm::ivec2{ bulletPosition.x, int(m_TileSize * m_Tiles.size()) - 1 };
		bullet->Bounce(TileComponent::Side::Top);
	}
	// Did we hit or pass the right boundry
	else if (bulletPosition.x >= int(m_TileSize * m_Tiles.size()))
	{
		intersection = glm::ivec2{ int(m_TileSize * m_Tiles.size()) - 1, bulletPosition.y };
		bullet->Bounce(TileComponent::Side::Right);
	}
	// Did we hit or pass the bottom boundry
	else if (bulletPosition.y < 0)
	{
		intersection = glm::ivec2{ bulletPosition.x, 0 };
		bullet->Bounce(TileComponent::Side::Bottom);
	}
	// Did we hit or pass the left boundry
	else if (bulletPosition.x < 0)
	{
		intersection = glm::ivec2{ 0, bulletPosition.y };	
		bullet->Bounce(TileComponent::Side::Left);
	}

	return intersection;
}

std::optional<glm::ivec2> TileManagerComponent::CheckCenter(BulletComponent* bullet) const
{
	std::optional<glm::ivec2> intersection{};	// tile space

	const glm::ivec2 bulletPosition{ bullet->GetOwner()->GetLocalTransform().GetPosition() };

	const int row{ bulletPosition.y / m_TileSize };	
	const int collumn{ bulletPosition.x / m_TileSize };	

	const glm::ivec2 tileOffset{ (collumn * m_TileSize) , (row * m_TileSize) };	
	const glm::ivec2 bulletTilePosition{ bulletPosition - tileOffset }; // tile space				

	const glm::ivec2 bottomLeft{ m_CollisionOffset, m_CollisionOffset };	// tile space
	const glm::ivec2 topRight{ m_TileSize - m_CollisionOffset - 1, m_TileSize - m_CollisionOffset - 1 };	// tile space	

	// Is point in default collision center box of a tile all tiles have this
	if (PointInsideRectangle(bulletTilePosition, bottomLeft, topRight))
	{
		const glm::ivec2 bottomRight{ topRight.x, bottomLeft.y };	// tile space
		const glm::ivec2 topLeft{ bottomLeft.x, topRight.y };	// tile space

		// Start point of line we check for intersection will be 100 units before bullet was inside the rectangle
		const glm::ivec2 start{ bulletTilePosition - glm::ivec2{ bullet->GetDirection() * 100.0f } };

#pragma warning (push)
#pragma warning (disable : 4706) // C4706 assignment used as a condition

		// Did it pass the top side if so where
		if (intersection = LinesIntersect(topLeft, topRight, start, bulletTilePosition))
		{
			bullet->Bounce(TileComponent::Side::Top);
		}
		// Did it pass the right side if so where
		else if (intersection = LinesIntersect(topRight, bottomRight, start, bulletTilePosition))
		{
			bullet->Bounce(TileComponent::Side::Right);
		}
		// Did it pass the bottom side if so where
		else if (intersection = LinesIntersect(bottomLeft, bottomRight, start, bulletTilePosition))
		{
			bullet->Bounce(TileComponent::Side::Bottom);
		}
		// Has to have passed the left but where
		else
		{
			if (intersection = LinesIntersect(bottomLeft, topLeft, start, bulletTilePosition))
			{
				bullet->Bounce(TileComponent::Side::Left);
			}
			else
			{
				throw std::exception{ "TileManagerComponent::CheckCenter() - Bullet is in center collision zone but couldn't find entry side" };
			}
		}
#pragma warning (pop)
	}

	// tile space to tile manager space
	if (intersection) intersection.value() += tileOffset;

	return intersection;
}

std::optional<glm::ivec2> TileManagerComponent::CheckTop(BulletComponent* bullet) const
{
	std::optional<glm::ivec2> intersection{};	// tile space	

	const glm::ivec2 bulletPosition{ bullet->GetOwner()->GetLocalTransform().GetPosition() };	

	const int row{ bulletPosition.y / m_TileSize };	
	const int collumn{ bulletPosition.x / m_TileSize };	

	const glm::ivec2 tileOffset{ (collumn * m_TileSize) , (row * m_TileSize) };
	const glm::ivec2 bulletTilePosition{ bulletPosition - tileOffset }; // tile space		

	if (!m_Tiles.at(row).at(collumn)->CanPass(TileComponent::Side::Top))
	{
		const glm::ivec2 bottomLeft{ m_CollisionOffset, m_TileSize - m_CollisionOffset };	// tile space
		const glm::ivec2 topRight{ m_TileSize - m_CollisionOffset - 1, m_TileSize - 1 };	// tile space

		// Is point in default collision center box of a tile all tiles have this
		if (PointInsideRectangle(bulletTilePosition, bottomLeft, topRight))
		{
			const glm::ivec2 bottomRight{ topRight.x, bottomLeft.y };
			const glm::ivec2 topLeft{ bottomLeft.x, topRight.y };

			// Start point of line we check for intersection will be 100 units before bullet was inside the rectangle
			glm::ivec2 start{ bulletTilePosition - glm::ivec2{ bullet->GetDirection() * 100.0f } };

#pragma warning (push)
#pragma warning (disable : 4706) // C4706 assignment used as a condition

			// Dit it pass the left side if so where
			if (intersection = LinesIntersect(bottomLeft, topLeft, start, bulletTilePosition))
			{
				bullet->Bounce(TileComponent::Side::Left);
			}
			// Did it pass the top side if so where
			if (intersection = LinesIntersect(topLeft, topRight, start, bulletTilePosition))
			{
				bullet->Bounce(TileComponent::Side::Top);
			}
			// Has to have passed the right side but where
			else
			{
				if (intersection = LinesIntersect(topRight, bottomRight, start, bulletTilePosition))
				{
					bullet->Bounce(TileComponent::Side::Right);
				}
			}
#pragma warning (pop)
		}
	}

	// tile space to tile manager space
	if (intersection) intersection.value() += tileOffset;

	return intersection;
}

std::optional<glm::ivec2> TileManagerComponent::CheckRight(BulletComponent* bullet) const
{
	std::optional<glm::ivec2> intersection{};	// tile space	

	const glm::ivec2 bulletPosition{ bullet->GetOwner()->GetLocalTransform().GetPosition() };

	const int row{ bulletPosition.y / m_TileSize };
	const int collumn{ bulletPosition.x / m_TileSize };

	const glm::ivec2 tileOffset{ (collumn * m_TileSize) , (row * m_TileSize) };
	const glm::ivec2 bulletTilePosition{ bulletPosition - tileOffset }; // tile space		

	if (!m_Tiles.at(row).at(collumn)->CanPass(TileComponent::Side::Right))
	{
		const glm::ivec2 bottomLeft{ m_TileSize - m_CollisionOffset, m_CollisionOffset };	// tile space
		const glm::ivec2 topRight{ m_TileSize - 1, m_TileSize - m_CollisionOffset - 1 };	// tile space

		// Is point in default collision center box of a tile all tiles have this
		if (PointInsideRectangle(bulletTilePosition, bottomLeft, topRight))
		{
			const glm::ivec2 bottomRight{ topRight.x, bottomLeft.y };
			const glm::ivec2 topLeft{ bottomLeft.x, topRight.y };

			// Start point of line we check for intersection will be 100 units before bullet was inside the rectangle
			const glm::ivec2 start{ bulletTilePosition - glm::ivec2{ bullet->GetDirection() * 100.0f } };

#pragma warning (push)
#pragma warning (disable : 4706) // C4706 assignment used as a condition

			// Did it pass the top side if so where
			if (intersection = LinesIntersect(topLeft, topRight, start, bulletTilePosition))
			{
				bullet->Bounce(TileComponent::Side::Top);
			}
			// Did it pass the right side if so where
			else if (intersection = LinesIntersect(topRight, bottomRight, start, bulletTilePosition))
			{
				bullet->Bounce(TileComponent::Side::Right);
			}
			// Has to have passed the bottom but where
			else
			{
				if (intersection = LinesIntersect(bottomRight, bottomLeft, start, bulletTilePosition))
				{
					bullet->Bounce(TileComponent::Side::Bottom);
				}
			}
#pragma warning (pop)
		}
	}

	// tile space to tile manager space
	if (intersection) intersection.value() += tileOffset;

	return intersection;
}

std::optional<glm::ivec2> TileManagerComponent::CheckBottom(BulletComponent* bullet) const
{
	std::optional<glm::ivec2> intersection{};	// tile space	

	const glm::ivec2 bulletPosition{ bullet->GetOwner()->GetLocalTransform().GetPosition() };

	const int row{ bulletPosition.y / m_TileSize };	
	const int collumn{ bulletPosition.x / m_TileSize };	

	const glm::ivec2 tileOffset{ (collumn * m_TileSize) , (row * m_TileSize) };
	const glm::ivec2 bulletTilePosition{ bulletPosition - tileOffset }; // tile space		

	if (!m_Tiles.at(row).at(collumn)->CanPass(TileComponent::Side::Bottom))
	{
		const glm::ivec2 bottomLeft{ m_CollisionOffset, 0 };	// tile space
		const glm::ivec2 topRight{ m_TileSize - m_CollisionOffset - 1, m_CollisionOffset - 1 };	// tile space

		// Is point in default collision center box of a tile all tiles have this
		if (PointInsideRectangle(bulletTilePosition, bottomLeft, topRight))
		{
			const glm::ivec2 bottomRight{ topRight.x, bottomLeft.y };
			const glm::ivec2 topLeft{ bottomLeft.x, topRight.y };

			// Start point of line we check for intersection will be 100 units before bullet was inside the rectangle
			const glm::ivec2 start{ bulletTilePosition - glm::ivec2{ bullet->GetDirection() * 100.0f } };

#pragma warning (push)
#pragma warning (disable : 4706) // C4706 assignment used as a condition

			// Did it pass the left side if so where
			if (intersection = LinesIntersect(bottomLeft, topLeft, start, bulletTilePosition))
			{
				bullet->Bounce(TileComponent::Side::Left);
			}
			// Did it pass the right side if so where
			else if (intersection = LinesIntersect(topRight, bottomRight, start, bulletTilePosition))
			{
				bullet->Bounce(TileComponent::Side::Right);
			}
			// Has to have passed the bottom but where
			else
			{
				if (intersection = LinesIntersect(bottomRight, bottomLeft, start, bulletTilePosition))
				{
					bullet->Bounce(TileComponent::Side::Bottom);
				}
			}
#pragma warning (pop)
		}
	}

	// tile space to tile manager space
	if (intersection) intersection.value() += tileOffset;

	return intersection;
}

std::optional<glm::ivec2> TileManagerComponent::CheckLeft(BulletComponent* bullet) const
{
	std::optional<glm::ivec2> intersection{};	// tile space	

	const glm::ivec2 bulletPosition{ bullet->GetOwner()->GetLocalTransform().GetPosition() };

	const int row{ bulletPosition.y / m_TileSize };
	const int collumn{ bulletPosition.x / m_TileSize };

	const glm::ivec2 tileOffset{ (collumn * m_TileSize) , (row * m_TileSize) };
	const glm::ivec2 bulletTilePosition{ bulletPosition - tileOffset }; // tile space		

	if (!m_Tiles.at(row).at(collumn)->CanPass(TileComponent::Side::Left))	
	{
		const glm::ivec2 bottomLeft{ 0, m_CollisionOffset };	// tile space
		const glm::ivec2 topRight{ m_CollisionOffset - 1, m_TileSize - m_CollisionOffset - 1 };	// tile space

		// Is point in default collision center box of a tile all tiles have this
		if (PointInsideRectangle(bulletTilePosition, bottomLeft, topRight))
		{
			const glm::ivec2 bottomRight{ topRight.x, bottomLeft.y };
			const glm::ivec2 topLeft{ bottomLeft.x, topRight.y };

			// Start point of line we check for intersection will be 100 units before bullet was inside the rectangle
			const glm::ivec2 start{ bulletTilePosition - glm::ivec2{ bullet->GetDirection() * 100.0f } };

#pragma warning (push)
#pragma warning (disable : 4706) // C4706 assignment used as a condition

			// Did it pass the bottom side if so where
			if (intersection = LinesIntersect(bottomRight, bottomLeft, start, bulletTilePosition))
			{
				bullet->Bounce(TileComponent::Side::Bottom);
			}
			// Did it pass the Left side if so where
			else if (intersection = LinesIntersect(bottomLeft, topLeft, start, bulletTilePosition))
			{
				bullet->Bounce(TileComponent::Side::Left);
			}
			// Has to have passed the top but where
			else
			{
				if (intersection = LinesIntersect(topLeft, topRight, start, bulletTilePosition))
				{
					bullet->Bounce(TileComponent::Side::Top);
				}
			}
#pragma warning (pop)
		}
	}

	// tile space to tile manager space
	if (intersection) intersection.value() += tileOffset;

	return intersection;
}
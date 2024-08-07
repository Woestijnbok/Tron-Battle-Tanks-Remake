#include <exception>
#include <algorithm>

#include "TileManagerComponent.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Bullet.h"

TileManagerComponent::TileManagerComponent(Minigin::GameObject* owner, int tileSize) :
	Component{ owner },
	m_Tiles
	{ 
		std::array<Tile, 8>{ Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{} },
		std::array<Tile, 8>{ Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{} },	
		std::array<Tile, 8>{ Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{} },	
		std::array<Tile, 8>{ Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{} },	
		std::array<Tile, 8>{ Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{} },	
		std::array<Tile, 8>{ Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{} },	
		std::array<Tile, 8>{ Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{} },	
		std::array<Tile, 8>{ Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{} }
	},
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
	glm::ivec2 position{ GetOwner()->GetWorldTransform().GetPosition() };

	return glm::ivec2{ position.x + static_cast<int>(m_TileSize * (m_Tiles.size() / 2)), position.y + static_cast<int>(m_TileSize * (m_Tiles.size() / 2)) };	
}

bool TileManagerComponent::CanMove(TankComponent const* tank, MoveCommand::Direction direction) const	
{
	bool canMove{ false };

	const glm::ivec2 worldTankPosition{ tank->GetWorldPosition() };
	const glm::ivec2 offset{ GetOwner()->GetWorldTransform().GetPosition() };

	const int row{ (worldTankPosition.y - offset.y) / m_TileSize };
	const int collumn{ (worldTankPosition.x - offset.x) / m_TileSize };

	switch (direction)
	{
	case MoveCommand::Direction::Up:
		if ((worldTankPosition.x - offset.x) % m_TileSize == 0)
		{
			// cross road
			if ((worldTankPosition.y - offset.y) % m_TileSize == 0)
			{
				// not top edge
				if (row < static_cast<int>(m_Tiles.size()))	
				{
					// check if at right edge
					if(collumn == static_cast<int>(m_Tiles.size())) canMove = m_Tiles.at(row).at(collumn - 1).CanPass(Tile::Side::Left);	
					else canMove = m_Tiles.at(row).at(collumn).CanPass(Tile::Side::Left);	
				}	
			}
			// between two
			else
			{
				// check if at right edge
				if(collumn == static_cast<int>(m_Tiles.size())) canMove = m_Tiles.at(row).at(collumn - 1).CanPass(Tile::Side::Left);	
				else canMove = m_Tiles.at(row).at(collumn).CanPass(Tile::Side::Left);
			}
		}
		break;
	case MoveCommand::Direction::Right:
		if ((worldTankPosition.y - offset.y) % m_TileSize == 0)
		{
			// cross road
			if ((worldTankPosition.x - offset.x) % m_TileSize == 0)
			{
				// not right edge
				if (collumn < static_cast<int>(m_Tiles.size()))		
				{
					// check if at top edge
					if(row == static_cast<int>(m_Tiles.size())) canMove = m_Tiles.at(row - 1).at(collumn).CanPass(Tile::Side::Bottom);	
					else canMove = m_Tiles.at(row).at(collumn).CanPass(Tile::Side::Bottom);
				}
			}
			// between two
			else
			{
				// check if at top edge
				if (row == static_cast<int>(m_Tiles.size())) canMove = m_Tiles.at(row - 1).at(collumn).CanPass(Tile::Side::Bottom);	
				else canMove = m_Tiles.at(row).at(collumn).CanPass(Tile::Side::Bottom);
			}
		}
		break;
	case MoveCommand::Direction::Down:
		if ((worldTankPosition.x - offset.x) % m_TileSize == 0)
		{
			// cross road
			if ((worldTankPosition.y - offset.y) % m_TileSize == 0)
			{
				// not bottom edge
				if (row > 0)
				{
					// check if at right edge
					if (collumn == static_cast<int>(m_Tiles.size())) canMove = m_Tiles.at(row - 1).at(collumn - 1).CanPass(Tile::Side::Left);	
					else canMove = m_Tiles.at(row - 1).at(collumn).CanPass(Tile::Side::Left);
				}
			}
			// between two
			else
			{
				// check if at right edge
				if (collumn == static_cast<int>(m_Tiles.size())) canMove = m_Tiles.at(row).at(collumn - 1).CanPass(Tile::Side::Left);
				else canMove = m_Tiles.at(row).at(collumn).CanPass(Tile::Side::Left);
			}
		}
		break;
	case MoveCommand::Direction::Left:
		if ((worldTankPosition.y - offset.y) % m_TileSize == 0)
		{
			// cross road
			if ((worldTankPosition.x - offset.x) % m_TileSize == 0)
			{
				// not left edge
				if (collumn > 0)
				{
					// check if at top edge
					if (row == static_cast<int>(m_Tiles.size())) canMove = m_Tiles.at(row - 1).at(collumn - 1).CanPass(Tile::Side::Bottom);	
					else canMove = m_Tiles.at(row).at(collumn - 1).CanPass(Tile::Side::Bottom);
				}
			}
			// between two
			else
			{
				// check if at top edge
				if (row == static_cast<int>(m_Tiles.size())) canMove = m_Tiles.at(row - 1).at(collumn).CanPass(Tile::Side::Bottom);	
				else canMove = m_Tiles.at(row).at(collumn).CanPass(Tile::Side::Bottom);
			}
		}
		break;
	default:
		break;
	}

	return canMove;
}

bool TileManagerComponent::CheckCollision(Bullet* bullet) const
{
	const glm::ivec2 offset{ GetOwner()->GetWorldTransform().GetPosition() };
	const glm::ivec2 bulletPosition{ bullet->GetPosition() - offset };		// this is tile - space not world space

	if (bulletPosition.y >= int(m_TileSize * m_Tiles.size()))	
	{
		return bullet->Bounce(Tile::Side::Top);
	}
	else if (bulletPosition.x >= int(m_TileSize * m_Tiles.size()))	
	{
		return bullet->Bounce(Tile::Side::Right);
	}
	else if (bulletPosition.y < 0)
	{
		return bullet->Bounce(Tile::Side::Bottom);
	}
	else if(bulletPosition.x < 0)
	{
		return bullet->Bounce(Tile::Side::Left);
	}
	else
	{
		const int row{ bulletPosition.y / m_TileSize };
		const int collumn{ bulletPosition.x / m_TileSize };

		const glm::ivec2 bottomLeft{ m_CollisionOffset + (collumn * m_TileSize), m_CollisionOffset + (row * m_TileSize) };
		const glm::ivec2 topRight{ (m_TileSize + (collumn * m_TileSize) - 1) - m_CollisionOffset, (m_TileSize + (row * m_TileSize) - 1) - m_CollisionOffset };

		if (PointInsideRectangle(bulletPosition, bottomLeft, topRight))
		{
			const glm::ivec2 bottomRight{ topRight.x, bottomLeft.y };
			const glm::ivec2 topLeft{ bottomLeft.x, topRight.y };

			const glm::ivec2 end{ bulletPosition - glm::ivec2{ bullet->GetDirection() * 8.0f } };

			if (LinesIntersect(topLeft, topRight, bulletPosition, end))
			{
				return bullet->Bounce(Tile::Side::Top);	
			}
			else if (LinesIntersect(topRight, bottomRight, bulletPosition, end))		
			{
				return bullet->Bounce(Tile::Side::Right);	
			}
			else if (LinesIntersect(bottomLeft, bottomRight, bulletPosition, end))	
			{
				return bullet->Bounce(Tile::Side::Bottom);	
			}
			else if(LinesIntersect(bottomLeft, topLeft, bulletPosition, end))	
			{
				return bullet->Bounce(Tile::Side::Left);	
			}
		}
	}	

	bullet;
	return false;
}

void TileManagerComponent::Render() const
{
	glm::ivec2 position{ GetOwner()->GetWorldTransform().GetPosition() };
	const glm::ivec2 startPosition{ position.x + (m_TileSize / 2), position.y + (m_TileSize / 2) };
	std::pair<Minigin::Texture const*, Minigin::Transform> renderInfo{};

	for (int row{}; row < static_cast<int>(m_Tiles.size()); ++row)	
	{
		for (int collumn{}; collumn < static_cast<int>(m_Tiles.at(row).size()); ++collumn)
		{
			renderInfo = GetRenderInfo(m_Tiles.at(row).at(collumn));

			renderInfo.second.SetPosition(glm::ivec2{ startPosition.x + (collumn * m_TileSize), startPosition.y + (row * m_TileSize) });

			renderInfo.first->Render(renderInfo.second);
		}
	}
}

std::pair<Minigin::Texture const*, Minigin::Transform> TileManagerComponent::GetRenderInfo(const Tile& tile) const
{
	std::pair<Minigin::Texture const*, Minigin::Transform> info{ std::make_pair<Minigin::Texture const*, Minigin::Transform>(nullptr, Minigin::Transform{}) };

	const int closedSides{ 4 - tile.GetTotalOpenSides() };

	switch (closedSides)
	{
	case 0:
		info.first = m_TileZero.get();
		info.second.SetScale(GetScale(m_TileZero.get()));

		break;
	case 1:
		info.first = m_TileOne.get();
		info.second.SetScale(GetScale(m_TileOne.get()));

		if (!tile.CanPass(Tile::Side::Bottom)) info.second.SetRotation(90);
		else if (!tile.CanPass(Tile::Side::Left)) info.second.SetRotation(180);
		else if (!tile.CanPass(Tile::Side::Top)) info.second.SetRotation(270);

		break;
	case 2:
		if ((tile.CanPass(Tile::Side::Top) and tile.CanPass(Tile::Side::Bottom)) or (tile.CanPass(Tile::Side::Right) and tile.CanPass(Tile::Side::Left)))
		{
			info.first = m_TileTwoStraight.get();
			info.second.SetScale(GetScale(m_TileTwoStraight.get()));

			if (!tile.CanPass(Tile::Side::Top)) info.second.SetRotation(90);
		}
		else
		{
			info.first = m_TileTwoCorner.get();
			info.second.SetScale(GetScale(m_TileTwoCorner.get()));

			if (!tile.CanPass(Tile::Side::Right) and !tile.CanPass(Tile::Side::Bottom)) info.second.SetRotation(90);
			else if (!tile.CanPass(Tile::Side::Bottom) and !tile.CanPass(Tile::Side::Left)) info.second.SetRotation(180);
			else if (!tile.CanPass(Tile::Side::Left) and !tile.CanPass(Tile::Side::Top)) info.second.SetRotation(270);
		}

		break;
	case 3:
		info.first = m_TileThree.get();
		info.second.SetScale(GetScale(m_TileThree.get()));

		if (tile.CanPass(Tile::Side::Left)) info.second.SetRotation(90);
		else if (tile.CanPass(Tile::Side::Top)) info.second.SetRotation(180);
		else if (tile.CanPass(Tile::Side::Right)) info.second.SetRotation(270);

		break;
	case 4:
		info.first = m_TileFour.get();
		info.second.SetScale(GetScale(m_TileFour.get()));

		break;
	default:
		throw std::exception{ "TileManagerComponent::GetTuleTexture() - Invalid amount of closed sides." };
		break;
	}

	return info;
}

glm::vec2 TileManagerComponent::GetScale(Minigin::Texture const* texture) const
{
	const glm::ivec2 textureSize{ texture->GetSize() };

	return glm::vec2{ static_cast<float>(m_TileSize) / textureSize.x, static_cast<float>(m_TileSize) / textureSize.y };
}

void TileManagerComponent::CreateTiles()
{
	std::array<std::array<Tile, 8>, 8> tiles
	{
		std::array<Tile, 8>{ Tile{ true, true, true, false }, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{} },
		std::array<Tile, 8>{ Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{} },
		std::array<Tile, 8>{ Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{} },
		std::array<Tile, 8>{ Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{} },
		std::array<Tile, 8>{ Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{} },
		std::array<Tile, 8>{ Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{} },
		std::array<Tile, 8>{ Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{} },
		std::array<Tile, 8>{ Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{} },
	};

	m_Tiles = tiles;
}

bool TileManagerComponent::PointInsideRectangle(const glm::ivec2& point, const glm::ivec2& bottom, const glm::ivec2 top) const
{
	return (point.x >= bottom.x) and (point.x <= top.x) and (point.y >= bottom.y) and (point.y <= top.y);	
}

bool TileManagerComponent::LinesIntersect(const glm::ivec2& a, const glm::ivec2& b, const glm::ivec2& c, const glm::ivec2& d) const
{
	glm::vec2 r = b - a; // Direction vector of the first line segment		
	glm::vec2 s = d - c; // Direction vector of the second line segment	

	float rxs = r.x * s.y - r.y * s.x; // Determinant
	float qpxr = (c - a).x * r.y - (c - a).y * r.x; // Cross product of vectors

	if (rxs == 0.0f) return false; // Lines are parallel or collinear	

	float t = qpxr / rxs;
	float u = ((c - a).x * s.y - (c - a).y * s.x) / rxs;	

	if (t >= 0.0f && t <= 1.0f && u >= 0.0f && u <= 1.0f)
	{
		return true;
	}
	else return false;
}

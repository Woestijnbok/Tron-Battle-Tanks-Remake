#include <exception>
#include <algorithm>
#include <optional>
#include <iostream>
#include <format>
#include <random>
#include <fstream>
#include <regex>

#include "TileManagerComponent.h"
#include "BulletManagerComponent.h"
#include "TankManagerComponent.h"
#include "TileComponent.h"
#include "BulletComponent.h"
#include "MiddleTileComponent.h"
#include "TankComponent.h"

#include "ResourceManager.h"
#include "Transform.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Scene.h"
#include "Collision.h"

bool TileManagerComponent::m_Alive{ false };

TileManagerComponent::TileManagerComponent(Minigin::GameObject* owner, int tileSize, const std::filesystem::path& path) :
	Component{ owner },
	m_Tiles{},
	m_MiddleTile{  },
	m_TileZero{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Tiles/Tile Zero.png") },
	m_TileOne{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Tiles/Tile One.png") },
	m_TileTwoCorner{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Tiles/Tile Two Corner.png") },
	m_TileTwoStraight{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Tiles/Tile Two Straight.png") },
	m_TileThree{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Tiles/Tile Three.png") },
	m_TileFour{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Tiles/Tile Four.png") },
	m_Border{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Tiles/Border.png") },
	m_TileSize{ tileSize },
	m_CollisionOffset{ 10 },
	m_BulletManager{},
	m_TankManager{}
{
	m_Alive = true;
	CreateTiles(path);	
	CreateMiddleTile();
}   

TileManagerComponent::~TileManagerComponent()
{
	for (size_t row{}; row < m_Tiles.size(); ++row)
	{
		for (size_t collumn{}; collumn < m_Tiles.at(row).size(); ++collumn)
		{
			m_Tiles.at(row).at(collumn)->GetOwner()->SetStatus(ControllableObject::Status::Destroyed);
			m_Tiles.at(row).at(collumn)->SetStatus(ControllableObject::Status::Destroyed);
		}
	}

	m_Alive = false;
}

void TileManagerComponent::SetManagers(BulletManagerComponent* bulletManager, TankManagerComponent* tankManager)
{
	m_BulletManager = bulletManager;
	m_TankManager = tankManager;
}

glm::ivec2 TileManagerComponent::GetRandomPosition() const
{
	const int tiles{ static_cast<int>(m_Tiles.size()) };
	std::random_device random{};
	std::mt19937 generator{ random() };
	std::uniform_int_distribution<> distributer{ 0, tiles - 1 };	

	int row{ -1 };
	int collumn{ -1 };
	while ((row == tiles / 4 and collumn == tiles / 4) or (row == -1 and collumn == -1))
	{
		row = distributer(generator);
		collumn = distributer(generator);
	}

	return glm::ivec2{ m_TileSize * collumn, m_TileSize * row };			
}

bool TileManagerComponent::CanMove(TankComponent* tank, MoveCommand::Direction direction) const
{
	bool canMove{ false };

	if (m_MiddleTile->CheckCollision(tank))
	{
		tank->GetOwner()->SetLocalPosition(GetRandomPosition());	
		return canMove;
	}

	canMove = CanMove(tank->GetOwner()->GetLocalTransform().GetPosition(), direction);		

	return canMove;
}

bool TileManagerComponent::CanMove(const glm::ivec2& position, MoveCommand::Direction direction) const
{
	bool canMove{ false };

	const int row{ position.y / m_TileSize };
	const int collumn{ position.x / m_TileSize };

	switch (direction)
	{
	case MoveCommand::Direction::Up:
		if (position.x % m_TileSize == 0)	
		{
			// cross road
			if (position.y % m_TileSize == 0)	
			{
				// not top edge
				if (row < static_cast<int>(m_Tiles.size()))
				{
					// check if at right edge
					if (collumn == static_cast<int>(m_Tiles.size())) canMove = m_Tiles.at(row).at(collumn - 1)->CanPass(TileComponent::Side::Right);	
					else canMove = m_Tiles.at(row).at(collumn)->CanPass(TileComponent::Side::Left);
				}
			}
			// between two
			else
			{
				// check if at right edge
				if (collumn == static_cast<int>(m_Tiles.size())) canMove = m_Tiles.at(row).at(collumn - 1)->CanPass(TileComponent::Side::Right);	
				else canMove = m_Tiles.at(row).at(collumn)->CanPass(TileComponent::Side::Left);
			}
		}
		break;
	case MoveCommand::Direction::Right:
		if (position.y % m_TileSize == 0)
		{
			// cross road
			if (position.x % m_TileSize == 0)
			{
				// not right edge
				if (collumn < static_cast<int>(m_Tiles.size()))
				{
					// check if at top edge
					if (row == static_cast<int>(m_Tiles.size())) canMove = m_Tiles.at(row - 1).at(collumn)->CanPass(TileComponent::Side::Top);	
					else canMove = m_Tiles.at(row).at(collumn)->CanPass(TileComponent::Side::Bottom);
				}
			}
			// between two
			else
			{
				// check if at top edge
				if (row == static_cast<int>(m_Tiles.size())) canMove = m_Tiles.at(row - 1).at(collumn)->CanPass(TileComponent::Side::Top);	
				else canMove = m_Tiles.at(row).at(collumn)->CanPass(TileComponent::Side::Bottom);
			}
		}
		break;
	case MoveCommand::Direction::Down:
		if (position.x % m_TileSize == 0)
		{
			// cross road
			if (position.y % m_TileSize == 0)	
			{
				// not bottom edge
				if (row > 0)
				{
					// check if at right edge
					if (collumn == static_cast<int>(m_Tiles.size())) canMove = m_Tiles.at(row - 1).at(collumn - 1)->CanPass(TileComponent::Side::Right);	
					else canMove = m_Tiles.at(row - 1).at(collumn)->CanPass(TileComponent::Side::Left);
				}
			}
			// between two
			else
			{
				// check if at right edge	
				if (collumn == static_cast<int>(m_Tiles.size())) canMove = m_Tiles.at(row).at(collumn - 1)->CanPass(TileComponent::Side::Right);	
				else canMove = m_Tiles.at(row).at(collumn)->CanPass(TileComponent::Side::Left);
			}
		}
		break;
	case MoveCommand::Direction::Left:
		if (position.y % m_TileSize == 0)	
		{
			// cross road	
			if (position.x % m_TileSize == 0)	
			{
				// not left edge
				if (collumn > 0)
				{
					// check if at top edge
					if (row == static_cast<int>(m_Tiles.size())) canMove = m_Tiles.at(row - 1).at(collumn - 1)->CanPass(TileComponent::Side::Top);
					else canMove = m_Tiles.at(row).at(collumn - 1)->CanPass(TileComponent::Side::Bottom);
				}
			}
			// between two
			else
			{
				// check if at top edge
				if (row == static_cast<int>(m_Tiles.size())) canMove = m_Tiles.at(row - 1).at(collumn)->CanPass(TileComponent::Side::Top);
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
					}
				}
			}
		}
	}

	if (intersection) bullet->GetOwner()->SetLocalPosition(intersection.value());
}

int TileManagerComponent::GetTileSize() const
{
	return m_TileSize;
}

int TileManagerComponent::GetTileArraySize() const
{
	return static_cast<int>(m_Tiles.size());
}

void TileManagerComponent::RemoveTile(TileComponent* tile)
{
	for (size_t row{}; row < m_Tiles.size(); ++row)
	{
		for (size_t collumn{}; collumn < m_Tiles.at(row).size(); ++collumn)
		{
			if (m_Tiles.at(row).at(collumn) == tile) m_Tiles.at(row).at(collumn) = nullptr;
		}
	}
}

void TileManagerComponent::Update()
{
	if (!m_Alive) m_Alive = true;
}

void TileManagerComponent::Render() const
{
	Minigin::Transform transform{ GetOwner()->GetWorldTransform() };
	const glm::ivec2 center{ static_cast<int>(m_Tiles.size()) * m_TileSize / 2 };
	transform.SetPosition(transform.GetPosition() + center);
	m_Border->Render(transform);
}

bool TileManagerComponent::Alive()
{
	return m_Alive;
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

void TileManagerComponent::CreateTiles(const std::filesystem::path& path)
{
	CreateTiles();	

	const std::filesystem::path fullPath{ Minigin::ResourceManager::Instance()->GetFileRootPath() / path };

	if (std::filesystem::exists(fullPath))	
	{
		if (std::filesystem::is_regular_file(fullPath))	
		{
			std::ifstream file{ fullPath };

			if (file.is_open() and file.good())	
			{	
				int lineCounter{};
				std::string line{};
				const std::regex pattern{ R"((\w),\s(\w),\s(\w),\s(\w),\s(\w),\s(\w),\s(\w),\s(\w))"  };		

				while (std::getline(file, line) and lineCounter < m_Tiles.size())	
				{
					++lineCounter;	

					std::smatch match{};
					if (std::regex_match(line, match, pattern))
					{
						for (size_t i{}; i < m_Tiles.size(); ++i)
						{
							CreateTile(8 - lineCounter, int(i), match[i + 1].str().at(0));
						}
					}
					else throw std::runtime_error(std::format("TileManagerComponent::CreatTiles() - {} failed to read.", fullPath.generic_string().c_str()));
				}
			}
			else throw std::runtime_error(std::format("TileManagerComponent::CreatTiles() - {} failed to open.", fullPath.generic_string().c_str()));	
		}
		else throw std::runtime_error(std::format("TileManagerComponent::CreatTiles() - {} isn't a regular file.", fullPath.generic_string().c_str()));	
	}
	else throw std::runtime_error(std::format("TileManagerComponent::CreatTiles() - {} doesn't exist.", fullPath.generic_string().c_str()));	
}

void TileManagerComponent::CreateTile(int row, int collumn, char character)
{
	TileComponent* tile{ m_Tiles.at(row).at(collumn) };

	switch (character)
	{
	case 'a':
		tile->SetSides(std::array<bool, 4>{ true, true, true, true });
		tile->SetTexture(m_TileZero.get());
		tile->GetOwner()->SetLocalRotation(0);
		break;
	case 'b':
		tile->SetSides(std::array<bool, 4>{ false, true, true, true });	
		tile->SetTexture(m_TileOne.get());	
		tile->GetOwner()->SetLocalRotation(270);	
		break;
	case 'c':
		tile->SetSides(std::array<bool, 4>{ true, false, true, true });
		tile->SetTexture(m_TileOne.get());	
		tile->GetOwner()->SetLocalRotation(0);
		break;
	case 'd':
		tile->SetSides(std::array<bool, 4>{ true, true, false, true });
		tile->SetTexture(m_TileOne.get());	
		tile->GetOwner()->SetLocalRotation(90);
		break;
	case 'e':
		tile->SetSides(std::array<bool, 4>{ true, true, true, false });	
		tile->SetTexture(m_TileOne.get());		
		tile->GetOwner()->SetLocalRotation(180);	
		break;
	case 'f':	
		tile->SetSides(std::array<bool, 4>{ true, false, true, false });	
		tile->SetTexture(m_TileTwoStraight.get());		
		tile->GetOwner()->SetLocalRotation(0);	
		break;
	case 'g':
		tile->SetSides(std::array<bool, 4>{ false, true, false, true });	
		tile->SetTexture(m_TileTwoStraight.get());	
		tile->GetOwner()->SetLocalRotation(90);		
		break;
	case 'h':
		tile->SetSides(std::array<bool, 4>{ true, true, false, false });	
		tile->SetTexture(m_TileTwoCorner.get());		
		tile->GetOwner()->SetLocalRotation(180);	
		break;
	case 'i':
		tile->SetSides(std::array<bool, 4>{ false, true, true, false });	
		tile->SetTexture(m_TileTwoCorner.get());		
		tile->GetOwner()->SetLocalRotation(270);		
		break;
	case 'j':
		tile->SetSides(std::array<bool, 4>{ false, false, true, true });	
		tile->SetTexture(m_TileTwoCorner.get());	
		tile->GetOwner()->SetLocalRotation(0);		
		break;
	case 'k':
		tile->SetSides(std::array<bool, 4>{ true, false, false, true });
		tile->SetTexture(m_TileTwoCorner.get());	
		tile->GetOwner()->SetLocalRotation(90);	
		break;
	case 'l':
		tile->SetSides(std::array<bool, 4>{ true, false, false, false });	
		tile->SetTexture(m_TileThree.get());	
		tile->GetOwner()->SetLocalRotation(180);	
		break;
	case 'm':
		tile->SetSides(std::array<bool, 4>{ false, true, false, false });
		tile->SetTexture(m_TileThree.get());	
		tile->GetOwner()->SetLocalRotation(270);	
		break;
	case 'n':
		tile->SetSides(std::array<bool, 4>{ false, false, true, false });	
		tile->SetTexture(m_TileThree.get());	
		tile->GetOwner()->SetLocalRotation(0);		
		break;
	case 'o':
		tile->SetSides(std::array<bool, 4>{ false, false, false, true });	
		tile->SetTexture(m_TileThree.get());	
		tile->GetOwner()->SetLocalRotation(90);
		break;
	case 'p':
		tile->SetSides(std::array<bool, 4>{ false, false, false, false });	
		tile->SetTexture(m_TileFour.get());	
		tile->GetOwner()->SetLocalRotation(0);		
		break;
	default:
		throw std::runtime_error("TileManagerComponent::CreatTile() - invalid character");
	};
}

void TileManagerComponent::CreateMiddleTile()
{
	Minigin::GameObject* object{ GetOwner()->GetScene()->CreateGameObject("Middle Tile") };	
	object->SetParent(GetOwner());	
	MiddleTileComponent* middle{ object->CreateComponent<MiddleTileComponent>() };	
	object->SetLocalPosition(glm::ivec2{ static_cast<int>(m_Tiles.size()) * m_TileSize / 2 });	

	m_MiddleTile = middle;	
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
	if (Minigin::PointInsideRectangle(bulletTilePosition, Minigin::Rectangle{ bottomLeft, topRight }))	
	{
		const glm::ivec2 bottomRight{ topRight.x, bottomLeft.y };	// tile space
		const glm::ivec2 topLeft{ bottomLeft.x, topRight.y };	// tile space

		// Start point of line we check for intersection will be 100 units before bullet was inside the rectangle
		const glm::ivec2 start{ bulletTilePosition - glm::ivec2{ bullet->GetDirection() * 100.0f } };

#pragma warning (push)
#pragma warning (disable : 4706) // C4706 assignment used as a condition

		// Did it pass the top side if so where
		if (intersection = Minigin::LinesIntersect(Minigin::Line{ topLeft, topRight }, Minigin::Line{ start, bulletTilePosition }))
		{
			bullet->Bounce(TileComponent::Side::Top);
		}
		// Did it pass the right side if so where
		else if (intersection = Minigin::LinesIntersect(Minigin::Line{ topRight, bottomRight }, Minigin::Line{ start, bulletTilePosition }))	
		{
			bullet->Bounce(TileComponent::Side::Right);
		}
		// Did it pass the bottom side if so where
		else if (intersection = Minigin::LinesIntersect(Minigin::Line{ bottomLeft, bottomRight }, Minigin::Line{ start, bulletTilePosition }))	
		{
			bullet->Bounce(TileComponent::Side::Bottom);
		}
		// Has to have passed the left but where
		else
		{
			if (intersection = Minigin::LinesIntersect(Minigin::Line{ bottomLeft, topLeft }, Minigin::Line{ start, bulletTilePosition }))
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
		if (Minigin::PointInsideRectangle(bulletTilePosition, Minigin::Rectangle{ bottomLeft, topRight }))
		{
			const glm::ivec2 bottomRight{ topRight.x, bottomLeft.y };
			const glm::ivec2 topLeft{ bottomLeft.x, topRight.y };

			// Start point of line we check for intersection will be 100 units before bullet was inside the rectangle
			glm::ivec2 start{ bulletTilePosition - glm::ivec2{ bullet->GetDirection() * 100.0f } };

#pragma warning (push)
#pragma warning (disable : 4706) // C4706 assignment used as a condition

			// Dit it pass the left side if so where
			if (intersection = Minigin::LinesIntersect(Minigin::Line{ bottomLeft, topLeft }, Minigin::Line{ start, bulletTilePosition }))
			{
				bullet->Bounce(TileComponent::Side::Left);
			}
			// Did it pass the top side if so where
			if (intersection = Minigin::LinesIntersect(Minigin::Line{ topLeft, topRight }, Minigin::Line{ start, bulletTilePosition }))
			{
				bullet->Bounce(TileComponent::Side::Top);
			}
			// Has to have passed the right side but where
			else
			{
				if (intersection = Minigin::LinesIntersect(Minigin::Line{ topRight, bottomRight }, Minigin::Line{ start, bulletTilePosition }))
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
		if (Minigin::PointInsideRectangle(bulletTilePosition, Minigin::Rectangle{ bottomLeft, topRight }))
		{
			const glm::ivec2 bottomRight{ topRight.x, bottomLeft.y };
			const glm::ivec2 topLeft{ bottomLeft.x, topRight.y };

			// Start point of line we check for intersection will be 100 units before bullet was inside the rectangle
			const glm::ivec2 start{ bulletTilePosition - glm::ivec2{ bullet->GetDirection() * 100.0f } };

#pragma warning (push)
#pragma warning (disable : 4706) // C4706 assignment used as a condition

			// Did it pass the top side if so where
			if (intersection = Minigin::LinesIntersect(Minigin::Line{ topLeft, topRight }, Minigin::Line{ start, bulletTilePosition }))
			{
				bullet->Bounce(TileComponent::Side::Top);
			}
			// Did it pass the right side if so where
			else if (intersection = Minigin::LinesIntersect(Minigin::Line{ topRight, bottomRight }, Minigin::Line{ start, bulletTilePosition }))
			{
				bullet->Bounce(TileComponent::Side::Right);
			}
			// Has to have passed the bottom but where
			else
			{
				if (intersection = Minigin::LinesIntersect(Minigin::Line{ bottomRight, bottomLeft }, Minigin::Line{ start, bulletTilePosition }))
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
		if (Minigin::PointInsideRectangle(bulletTilePosition, Minigin::Rectangle{ bottomLeft, topRight }))
		{
			const glm::ivec2 bottomRight{ topRight.x, bottomLeft.y };
			const glm::ivec2 topLeft{ bottomLeft.x, topRight.y };

			// Start point of line we check for intersection will be 100 units before bullet was inside the rectangle
			const glm::ivec2 start{ bulletTilePosition - glm::ivec2{ bullet->GetDirection() * 100.0f } };

#pragma warning (push)
#pragma warning (disable : 4706) // C4706 assignment used as a condition

			// Did it pass the left side if so where
			if (intersection = Minigin::LinesIntersect(Minigin::Line{ bottomLeft, topLeft }, Minigin::Line{ start, bulletTilePosition }))
			{
				bullet->Bounce(TileComponent::Side::Left);
			}
			// Did it pass the right side if so where
			else if (intersection = Minigin::LinesIntersect(Minigin::Line{ topRight, bottomRight }, Minigin::Line{ start, bulletTilePosition }))
			{
				bullet->Bounce(TileComponent::Side::Right);
			}
			// Has to have passed the bottom but where
			else
			{
				if (intersection = Minigin::LinesIntersect(Minigin::Line{ bottomRight, bottomLeft }, Minigin::Line{ start, bulletTilePosition }))
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
		if (Minigin::PointInsideRectangle(bulletTilePosition, Minigin::Rectangle{ bottomLeft, topRight }))
		{
			const glm::ivec2 bottomRight{ topRight.x, bottomLeft.y };
			const glm::ivec2 topLeft{ bottomLeft.x, topRight.y };

			// Start point of line we check for intersection will be 100 units before bullet was inside the rectangle
			const glm::ivec2 start{ bulletTilePosition - glm::ivec2{ bullet->GetDirection() * 100.0f } };

#pragma warning (push)
#pragma warning (disable : 4706) // C4706 assignment used as a condition

			// Did it pass the bottom side if so where
			if (intersection = Minigin::LinesIntersect(Minigin::Line{ bottomRight, bottomLeft }, Minigin::Line{ start, bulletTilePosition }))
			{
				bullet->Bounce(TileComponent::Side::Bottom);
			}
			// Did it pass the Left side if so where
			else if (intersection = Minigin::LinesIntersect(Minigin::Line{ bottomLeft, topLeft }, Minigin::Line{ start, bulletTilePosition }))
			{
				bullet->Bounce(TileComponent::Side::Left);
			}
			// Has to have passed the top but where
			else
			{
				if (intersection = Minigin::LinesIntersect(Minigin::Line{ topLeft, topRight }, Minigin::Line{ start, bulletTilePosition }))
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
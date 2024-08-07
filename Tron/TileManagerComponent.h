#pragma once

#include <array>
#include <memory>
#include <utility>
#include <vec2.hpp>

#include "Component.h"
#include "Tile.h"
#include "Texture.h"
#include "MoveCommand.h"
#include "TankComponent.h"

class Bullet;

class TileManagerComponent final : public Minigin::Component
{
public:	
	explicit TileManagerComponent(Minigin::GameObject* owner, int tileSize);
	virtual ~TileManagerComponent() = default;

	TileManagerComponent(const TileManagerComponent&) = delete;
	TileManagerComponent(TileManagerComponent&&) noexcept = delete;
	TileManagerComponent& operator= (const TileManagerComponent&) = delete;
	TileManagerComponent& operator= (const TileManagerComponent&&) noexcept = delete;

	glm::ivec2 GetStartPosition() const;
	bool CanMove(TankComponent const * tank, MoveCommand::Direction direction) const;
	bool CheckCollision(Bullet* bullet) const;

	virtual void Render() const override;

private:
	std::array<std::array<Tile, 8>, 8> m_Tiles;	
	const std::unique_ptr<const Minigin::Texture> m_TileZero;	
	const std::unique_ptr<const Minigin::Texture> m_TileOne;
	const std::unique_ptr<const Minigin::Texture> m_TileTwoCorner;
	const std::unique_ptr<const Minigin::Texture> m_TileTwoStraight;
	const std::unique_ptr<const Minigin::Texture> m_TileThree;
	const std::unique_ptr<const Minigin::Texture> m_TileFour;
	const int m_TileSize;
	const int m_CollisionOffset;

	/*
	* @brief Helper function to get the correct texture and rotation for a tile.
	* @return A pair with the first element being the texture and the second the angle the texture needs to be rotated by.
	*/
	std::pair<Minigin::Texture const *, Minigin::Transform> GetRenderInfo(const Tile& tile) const;	
	glm::vec2 GetScale(Minigin::Texture const* texture) const;
	void CreateTiles();
	/*
	* @param point is the point that needs to be checked.
	* bottom is the bottom left point of the rectangle.
	* top is the top right point of the rectangle
	*/
	bool PointInsideRectangle(const glm::ivec2& point, const glm::ivec2& bottom, const glm::ivec2 top) const;
	bool LinesIntersect(const glm::ivec2& a, const glm::ivec2& b, const glm::ivec2& c, const glm::ivec2& d) const;	
};
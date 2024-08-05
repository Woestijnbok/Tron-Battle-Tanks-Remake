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

	virtual void Render() const override;

private:
	const std::array<const std::array<const Tile, 8>, 8> m_Tiles;
	const std::unique_ptr<const Minigin::Texture> m_TileZero;	
	const std::unique_ptr<const Minigin::Texture> m_TileOne;
	const std::unique_ptr<const Minigin::Texture> m_TileTwoCorner;
	const std::unique_ptr<const Minigin::Texture> m_TileTwoStraight;
	const std::unique_ptr<const Minigin::Texture> m_TileThree;
	const std::unique_ptr<const Minigin::Texture> m_TileFour;
	const int m_TileSize;

	/*
	* @brief Helper function to get the correct texture and rotation for a tile.
	* @return A pair with the first element being the texture and the second the angle the texture needs to be rotated by.
	*/
	std::pair<Minigin::Texture const *, Minigin::Transform> GetRenderInfo(const Tile& tile) const;	
	glm::vec2 GetScale(Minigin::Texture const* texture) const;
};
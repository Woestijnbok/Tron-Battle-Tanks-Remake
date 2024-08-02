#pragma once

#include <array>
#include <memory>
#include <utility>

#include "Component.h"
#include "Tile.h"
#include "Texture.h"

class TileManagerComponent final : public Minigin::Component
{
public:
	explicit TileManagerComponent(Minigin::GameObject* owner);
	virtual ~TileManagerComponent() = default;

	TileManagerComponent(const TileManagerComponent&) = delete;
	TileManagerComponent(TileManagerComponent&&) noexcept = delete;
	TileManagerComponent& operator= (const TileManagerComponent&) = delete;
	TileManagerComponent& operator= (const TileManagerComponent&&) noexcept = delete;

	virtual void Render() const override;

private:
	const std::array<const std::array<const Tile, 8>, 8> m_Tiles;
	const std::unique_ptr<const Minigin::Texture> m_TileZero;	
	const std::unique_ptr<const Minigin::Texture> m_TileOne;
	const std::unique_ptr<const Minigin::Texture> m_TileTwoCorner;
	const std::unique_ptr<const Minigin::Texture> m_TileTwoStraight;
	const std::unique_ptr<const Minigin::Texture> m_TileThree;
	const std::unique_ptr<const Minigin::Texture> m_TileFour;

	/*
	* @brief Helper function to get the correct texture and rotation for a tile.
	* @return A pair with the first element being the texture and the second the angle the texture needs to be rotated by.
	*/
	std::pair<Minigin::Texture const *, int> GetRenderInfo(const Tile& tile) const;	
};
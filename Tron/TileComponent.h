#pragma once

#include <array>

#include "Component.h"
#include "Texture.h"

class TileComponent final : public Minigin::Component
{
public:
	enum class Side
	{
		Top,
		Right,
		Bottom,
		Left
	};

	explicit TileComponent(Minigin::GameObject* owner, Minigin::Texture* texture, const std::array<bool, 4>& sides);
	explicit TileComponent(Minigin::GameObject* owner, Minigin::Texture* texture);
	virtual ~TileComponent() = default;

	TileComponent(const TileComponent&) = delete;
	TileComponent(TileComponent&&) noexcept = delete;
	TileComponent& operator= (const TileComponent&) = default;
	TileComponent& operator= (const TileComponent&& rhs) noexcept = delete;

	bool CanPass(Side side) const;
	int GetTotalOpenSides() const;
	Minigin::Texture* GetTexture() const;
	void SetSide(Side side, bool pass);
	void SetTexture(Minigin::Texture* texture);

	virtual void Render() const override;

private:
	/*
	* @brief array of 4 bools if true that means a tank can pass that side.
	* the order of sides is top, right, bottom and left.
	*/
	std::array<bool, 4> m_Sides;
	Minigin::Texture* m_Texture;
};
#pragma once

#include <array>

class Tile final
{
public:
	enum class Side
	{
		Top,
		Right,
		Bottom,
		Left
	};

	explicit Tile(bool top, bool right, bool bottom, bool left);
	explicit Tile();
	~Tile() = default;

	Tile(const Tile&) = default;
	Tile(Tile&&) noexcept = default;
	Tile& operator= (const Tile&) = delete;
	Tile& operator= (const Tile&&) noexcept = delete;

	bool CanPass(Side side) const;
	void SetPass(Side side, bool pass);
	int GetTotalOpenSides() const;

private:
	/*
	* @brief array of 4 bools if true that means a tank can pass that side.
	* the order of sides is top, right, bottom and lastly left.
	*/
	std::array<bool, 4> m_Sides;

};
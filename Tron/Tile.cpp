#include <algorithm>

#include "Tile.h"

Tile::Tile(bool top, bool right, bool bottom, bool left) :
	m_Sides{ top, right, bottom, left }	
{
}

Tile::Tile() :
	m_Sides{ true, true, true, true }
{

}

bool Tile::CanPass(Side side) const
{
	return m_Sides.at(static_cast<int>(side));
}

void Tile::SetPass(Side side, bool pass)
{
	m_Sides.at(static_cast<int>(side)) = pass;
}

int Tile::GetTotalOpenSides() const
{
	return static_cast<int>(std::ranges::count(m_Sides, true));		
}
#include <algorithm>

#include "TileComponent.h"
#include "GameObject.h"
#include "TileManagerComponent.h"

TileComponent::TileComponent(Minigin::GameObject* owner, Minigin::Texture* texture, const std::array<bool, 4>& sides) :	
	Component{ owner },
	m_Sides{ sides },	
	m_Texture{ texture }
{

}

TileComponent::TileComponent(Minigin::GameObject* owner, Minigin::Texture* texture) :
	Component{ owner },
	m_Sides{ true, true, true, true },
	m_Texture{ texture }
{
	
}

bool TileComponent::CanPass(Side side) const
{
	return m_Sides.at(static_cast<int>(side));
}

int TileComponent::GetTotalOpenSides() const
{
	return static_cast<int>(std::ranges::count(m_Sides, true));			
}

Minigin::Texture* TileComponent::GetTexture() const	
{
	return m_Texture;
}

void TileComponent::SetSide(Side side, bool pass)	
{
	m_Sides.at(static_cast<int>(side)) = pass;
}

void TileComponent::SetTexture(Minigin::Texture* texture)
{
	m_Texture = texture;
}

void TileComponent::Render() const
{
	m_Texture->Render(GetOwner()->GetWorldTransform());
}
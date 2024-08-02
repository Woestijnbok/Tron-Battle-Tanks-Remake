#include <exception>

#include "TileManagerComponent.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "GameObject.h"
#include "Renderer.h"

TileManagerComponent::TileManagerComponent(Minigin::GameObject* owner) :
	Component{ owner },
	m_Tiles
	{
		std::array<const Tile, 8>{ Tile{ true, false, false, true }, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{} },	
		std::array<const Tile, 8>{ Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{} },
		std::array<const Tile, 8>{ Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{} },
		std::array<const Tile, 8>{ Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{} },
		std::array<const Tile, 8>{ Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{} },
		std::array<const Tile, 8>{ Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{} },
		std::array<const Tile, 8>{ Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{} },
		std::array<const Tile, 8>{ Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{}, Tile{} },
	},
	m_TileZero{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Tiles/Tile Zero.png") },	
	m_TileOne{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Tiles/Tile One.png") },	
	m_TileTwoCorner{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Tiles/Tile Two Corner.png") },	
	m_TileTwoStraight{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Tiles/Tile Two Straight.png") },	
	m_TileThree{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Tiles/Tile Three.png") },	
	m_TileFour{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Tiles/Tile Four.png") }	
{

}

void TileManagerComponent::Render() const
{
	glm::ivec2 startPosition{ GetOwner()->GetLocalTransform().GetPosition() };
	Minigin::Transform transform{};
	std::pair<Minigin::Texture const*, int> renderInfo{};

	for (int row{}; row < m_Tiles.size(); ++row)
	{
		for (int collumn{}; collumn < m_Tiles.at(row).size(); ++collumn)	
		{
			renderInfo = GetRenderInfo(m_Tiles.at(row).at(collumn));

			transform.SetPosition(glm::ivec2{ startPosition.x + (row * 50), startPosition.y - (collumn * 50) });
			transform.SetRotation(renderInfo.second);

			renderInfo.first->Render(transform);
		}
	}
}

std::pair<Minigin::Texture const*, int> TileManagerComponent::GetRenderInfo(const Tile& tile) const	
{
	std::pair<Minigin::Texture const*, int> info{ std::make_pair<Minigin::Texture const*, int>(nullptr, 0) };

	const int closedSides{ 4 - tile.GetTotalOpenSides() };

	switch (closedSides)
	{
	case 0:
		info.first = m_TileZero.get();	

		break;
	case 1:
		info.first = m_TileOne.get();
			
		if (!tile.CanPass(Tile::Side::Bottom)) info.second = 90;
		else if (!tile.CanPass(Tile::Side::Left))info.second = 180;				
		else if (!tile.CanPass(Tile::Side::Top)) info.second = 270;	

		break;
	case 2:
		if ((tile.CanPass(Tile::Side::Top) and tile.CanPass(Tile::Side::Bottom)) or (tile.CanPass(Tile::Side::Right) and tile.CanPass(Tile::Side::Left)))	
		{
			info.first = m_TileTwoStraight.get();

			if (!tile.CanPass(Tile::Side::Top)) info.second = 90;
		}
		else 
		{
			info.first = m_TileTwoCorner.get();	

			if (!tile.CanPass(Tile::Side::Right) and !tile.CanPass(Tile::Side::Bottom)) info.second = 90;
			else if (!tile.CanPass(Tile::Side::Bottom) and !tile.CanPass(Tile::Side::Left)) info.second = 180;	
			else if (!tile.CanPass(Tile::Side::Left) and !tile.CanPass(Tile::Side::Top)) info.second = 270;	
		}

		break;
	case 3:
		info.first = m_TileThree.get();	

		if (tile.CanPass(Tile::Side::Left)) info.second = 90;
		else if (tile.CanPass(Tile::Side::Top)) info.second = 190;
		else if (tile.CanPass(Tile::Side::Right)) info.second = 270;

		break;
	case 4:	
		info.first = m_TileFour.get();		
		break;
	default :
		throw std::exception{ "TileManagerComponent::GetTuleTexture() - Invalid amount of closed sides." };
		break;
	}

	return info;
}
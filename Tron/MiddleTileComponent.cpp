#include "MiddleTileComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TankComponent.h"

MiddleTileComponent::MiddleTileComponent(Minigin::GameObject* owner) :
	Component{ owner },
	m_Texture{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Tiles/Tile Middle.png") },
	m_Offset{ 20 }
{

}

bool MiddleTileComponent::CheckCollision(TankComponent* tank)	
{
	const glm::ivec2 tankPosition{ tank->GetOwner()->GetLocalTransform().GetPosition() };
	const glm::ivec2 position{ GetOwner()->GetLocalTransform().GetPosition() };

	// Not too high	
	if (tankPosition.y <= position.y + m_Offset)		
	{
		// Not too right
		if (tankPosition.x <= position.x + m_Offset)	
		{
			// Not too low
			if (tankPosition.y >= position.y - m_Offset)		
			{
				// Not too left
				if (tankPosition.x >= position.x - m_Offset)			
				{
					return true;
				}
			}
		}
	}

	return false;
}

void MiddleTileComponent::Render() const
{
	m_Texture->Render(GetOwner()->GetWorldTransform());
}
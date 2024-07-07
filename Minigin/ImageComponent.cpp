#include "ImageComponent.h"
#include "Texture.h"
#include "Renderer.h"
#include "GameObject.h"	

ImageComponent::ImageComponent(GameObject* owner, std::shared_ptr<Texture> texture) :	
	Component{ owner },
	m_Texture{ texture }
{

}

void ImageComponent::Render() const
{
	if ((GetOwner() != nullptr) and (m_Texture.get() != nullptr))
	{
		auto position{ GetOwner()->GetWorldTransform().GetPosition() };
		Renderer::GetInstance().RenderTexture(*m_Texture.get(), position.x, position.y);
	}
}

const std::shared_ptr<Texture> ImageComponent::GetTexture() const
{
	return m_Texture;
}
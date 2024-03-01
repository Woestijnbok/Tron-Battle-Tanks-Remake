#include "ImageComponent.h"
#include "Texture.h"

ImageComponent::ImageComponent(std::weak_ptr<GameObject> owner, std::shared_ptr<Texture> texture) :
	Component{ owner },
	m_Texture{ texture }
{

}

void ImageComponent::Update(std::chrono::milliseconds deltaTime)
{
	++deltaTime;
}

void ImageComponent::FixedUpdate(std::chrono::milliseconds deltaTime)
{
	++deltaTime;
}

const std::shared_ptr<Texture> ImageComponent::GetTexture() const
{
	return m_Texture;
}
#include "ImageComponent.h"
#include "Texture.h"
#include "Renderer.h"

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

void ImageComponent::Render() const
{
	std::shared_ptr<GameObject> owner = m_Owner.lock();
	if ((owner != nullptr) and (m_Texture.get() != nullptr))
	{
		auto position{ owner->GetWorldTransform().GetPosition() };
		Renderer::GetInstance().RenderTexture(*m_Texture.get(), position.x, position.y);
	}
}

const std::shared_ptr<Texture> ImageComponent::GetTexture() const
{
	return m_Texture;
}
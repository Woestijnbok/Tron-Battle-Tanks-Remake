#include "RenderComponent.h"
#include "Renderer.h"
#include "ImageComponent.h"
#include "TextComponent.h"

RenderComponent::RenderComponent(std::shared_ptr<GameObject> owner) :
	Component{ owner }
{

}

void RenderComponent::Update(std::chrono::milliseconds deltaTime)
{
	++deltaTime;
}

void RenderComponent::FixedUpdate(std::chrono::milliseconds deltaTime)
{
	++deltaTime;
}

void RenderComponent::Render() const
{
	auto image{ m_Owner->GetComponent<ImageComponent>() };

	if (image != nullptr)
	{
		const auto& position{ m_Owner->GetTransform().GetPosition() };
		Renderer::GetInstance().RenderTexture(*image->GetTexture(), position.x, position.y);
	}

	auto text{ m_Owner->GetComponent<TextComponent>() };

	if (text != nullptr)
	{
		if (text->GetTexture() != nullptr)
		{
			const auto& position{ m_Owner->GetTransform().GetPosition() };
			Renderer::GetInstance().RenderTexture(*text->GetTexture(), position.x, position.y);
		}
	}
}
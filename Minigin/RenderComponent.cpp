#include <iostream>

#include "RenderComponent.h"
#include "Renderer.h"
#include "ImageComponent.h"
#include "TextComponent.h"
#include "FPSCounterComponent.h"

RenderComponent::RenderComponent(std::weak_ptr<GameObject> owner) :
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
	if (auto owner = m_Owner.lock()) 
	{
		auto image{ owner->GetComponent<ImageComponent>() };

		if (image != nullptr)
		{
			const auto& position{ owner->GetWorldTransform().GetPosition() };
			Renderer::GetInstance().RenderTexture(*image->GetTexture(), position.x, position.y);
		}

		auto text{ owner->GetComponent<TextComponent>() };

		if (text != nullptr)
		{
			if (text->GetTexture() != nullptr)
			{
				const auto& position{ owner->GetWorldTransform().GetPosition() };
				Renderer::GetInstance().RenderTexture(*text->GetTexture(), position.x, position.y);
			}
		}

		auto fpsCounter{ owner->GetComponent<FPSCounterComponent>() };

		if (fpsCounter != nullptr)
		{
			if (fpsCounter->GetTexture() != nullptr)
			{
				const auto& position{ owner->GetWorldTransform().GetPosition() };
				Renderer::GetInstance().RenderTexture(*fpsCounter->GetTexture(), position.x, position.y);
			}
		}
	}
	else 
	{
		std::cout << "Weak ptr is invalid RenderComponent::Render()" << std::endl;
	}
}
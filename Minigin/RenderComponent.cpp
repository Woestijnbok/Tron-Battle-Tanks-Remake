#include "RenderComponent.h"
#include "Renderer.h"
#include "Texture2D.h"

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
	auto texture{ m_Owner->GetComponent<Texture2D>() };

	if (texture != nullptr)
	{
		const auto& position{ m_Owner->GetTransform().GetPosition() };
		Renderer::GetInstance().RenderTexture(*texture, position.x, position.y);
	}
}
#include "RenderComponent.h"
#include "Renderer.h"

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
	/*std::shared_ptr<Texture2D> texture{ m_Owner->GetComponent<Texture2D>() };

	if (texture != nullptr)
	{
		const auto& pos = m_Owner->GetTransform().GetPosition();
		Renderer::GetInstance().RenderTexture(*texture, pos.x, pos.y);
	}*/
}
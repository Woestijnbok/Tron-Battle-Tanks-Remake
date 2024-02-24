#include <string>

#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

GameObject::~GameObject() = default;

void GameObject::Update(std::chrono::milliseconds deltaTime)
{
	deltaTime++;
}

void GameObject::FixedUpdate(std::chrono::milliseconds deltaTime)
{
	deltaTime++;
}

void GameObject::Render() const
{
	/*const auto& pos = m_transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);*/
}

//void GameObject::SetTexture(const std::string& filename)
//{
//	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
//}

void GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

const Transform& GameObject::GetTransform() const
{
	return m_Transform;
}
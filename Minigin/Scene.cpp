#include <algorithm>

#include "Scene.h"
#include "GameObject.h"
#include "RenderComponent.h"

unsigned int Scene::m_IdCounter{ 0 };

Scene::Scene(const std::string& name) : 
	m_Name{ name },
	m_Objects{}
{

}

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_Objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), object), m_Objects.end());
}

void Scene::RemoveAll()
{
	m_Objects.clear();
}

void Scene::Update(std::chrono::milliseconds deltaTime)
{
	for(auto& object : m_Objects)
	{
		object->Update(deltaTime);
	}
}

void Scene::FixedUpdate(std::chrono::milliseconds deltaTime)
{
	for (auto& object : m_Objects)
	{
		object->Update(deltaTime);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		auto renderComoponent{ object->GetComponent<RenderComponent>() };

		if (renderComoponent != nullptr) renderComoponent->Render();
	}
}

const std::string& Scene::GetName() const
{
	return m_Name;
}
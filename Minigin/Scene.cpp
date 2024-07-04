#include <algorithm>

#include "Scene.h"
#include "GameObject.h"

Scene::Scene(const std::string& name) : 
	m_Name{ name },
	m_Objects{}
{

}

GameObject* Scene::CreateGameObject()
{
	return m_Objects.emplace_back(new GameObject{}).get();
}

void Scene::RemoveGameObject(GameObject* object)
{
	m_Objects.erase
	(
		std::remove_if
		(
			std::begin(m_Objects), std::end(m_Objects), [object](const std::unique_ptr<GameObject>& ptr) -> bool { return ptr.get() == object; }
		)
		, m_Objects.end()
	);
}

void Scene::Clear()
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

void Scene::FixedUpdate()
{
	for (auto& object : m_Objects)
	{
		object->FixedUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

const std::string& Scene::GetName() const
{
	return m_Name;
}
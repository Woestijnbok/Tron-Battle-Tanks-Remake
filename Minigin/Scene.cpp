#include <algorithm>

#include "Scene.h"
#include "SceneManager.h"

Scene::Scene(const std::string& name) : 
	m_Name{ name },
	m_ActiveObjects{},
	m_InactiveObjects{},
	m_InitialObjectCount{}
{

}

GameObject* Scene::CreateGameObject(bool active)
{
	if (active) return m_ActiveObjects.emplace_back(new GameObject{ this }).get();
	else return m_InactiveObjects.emplace_back(new GameObject{ this }).get();
}

void Scene::Clear()
{
	m_ActiveObjects.clear();
	m_InactiveObjects.clear();
}

void Scene::Update()
{
	m_InitialObjectCount = m_ActiveObjects.size();

	for (size_t i{}; i < m_InitialObjectCount; ++i)
	{
		if (!m_ActiveObjects.at(i)->IsMarkedForDestroy())
		{
			m_ActiveObjects.at(i)->Update();	
		}
	}

	m_ActiveObjects.erase
	(
		std::remove_if
		(
			std::begin(m_ActiveObjects), std::end(m_ActiveObjects), [](const std::unique_ptr<GameObject>& ptr) -> bool { return ptr->IsMarkedForDestroy(); }
		)
		, m_ActiveObjects.end()
	);

	m_InactiveObjects.erase
	(
		std::remove_if
		(
			std::begin(m_InactiveObjects), std::end(m_InactiveObjects), [](const std::unique_ptr<GameObject>& ptr) -> bool { return ptr->IsMarkedForDestroy(); }
		)
		, m_InactiveObjects.end()
	);
}

void Scene::FixedUpdate()
{
	m_InitialObjectCount = m_ActiveObjects.size();

	for (size_t i{}; i < m_InitialObjectCount; ++i)
	{
		if (!m_ActiveObjects.at(i)->IsMarkedForDestroy())
		{
			m_ActiveObjects.at(i)->FixedUpdate();
		}
	}

	m_ActiveObjects.erase
	(
		std::remove_if
		(
			std::begin(m_ActiveObjects), std::end(m_ActiveObjects), [](const std::unique_ptr<GameObject>& ptr) -> bool { return ptr->IsMarkedForDestroy(); }
		)
		, m_ActiveObjects.end()
	);

	m_InactiveObjects.erase
	(
		std::remove_if
		(
			std::begin(m_InactiveObjects), std::end(m_InactiveObjects), [](const std::unique_ptr<GameObject>& ptr) -> bool { return ptr->IsMarkedForDestroy(); }
		)
		, m_InactiveObjects.end()
	);
}

void Scene::LateUpdate()
{
	for (const auto& object : m_ActiveObjects)
	{
		object->LateUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_ActiveObjects)
	{
		object->Render();
	}
}

const std::string& Scene::GetName() const
{
	return m_Name;
}

void Scene::SetActive(bool active)
{
	SceneManager::GetInstance().SetActiveScene(this, active);
}

void Scene::SetActiveGameObject(GameObject* object, bool active)
{
	if (active) 
	{
		const auto it = std::find_if(m_InactiveObjects.begin(), m_InactiveObjects.end(), [object](const std::unique_ptr<GameObject>& ptr) { return ptr.get() == object; });
		if (it != m_InactiveObjects.end()) 
		{
			m_ActiveObjects.push_back(std::move(*it));
			m_InactiveObjects.erase(it);
		}
	}
	else 
	{
		auto it = std::find_if(m_ActiveObjects.begin(), m_ActiveObjects.end(), [object](const std::unique_ptr<GameObject>& ptr) { return ptr.get() == object; });
		if (it != m_ActiveObjects.end()) 
		{
			m_InactiveObjects.push_back(std::move(*it));
			m_ActiveObjects.erase(it);
		}
	}
}
#include <algorithm>

#include "SceneManager.h"

Scene* SceneManager::CreateScene(const std::string& name, bool active)
{
	if (active) return m_ActiveScenes.emplace_back(new Scene{ name }).get();	
	else return m_InactiveScenes.emplace_back(new Scene{ name }).get();	
}

Scene* SceneManager::GetScene(const std::string& name)
{
	auto it{ std::ranges::find_if(m_ActiveScenes, [name](const std::unique_ptr<Scene>& scene) -> bool { return scene->GetName() == name; }) };	
	if (it == m_ActiveScenes.end())
	{
		it = std::ranges::find_if(m_InactiveScenes, [name](const std::unique_ptr<Scene>& scene) -> bool { return scene->GetName() == name; });
	}

	if (it != m_InactiveScenes.end()) return it->get();	
	else return nullptr;
}

void SceneManager::DeleteScene(const std::string& name)
{
	m_ActiveScenes.erase
	(
		std::remove_if
		(
			std::begin(m_ActiveScenes), std::end(m_ActiveScenes), [&name](const std::unique_ptr<Scene>& scene) -> bool { return scene->GetName() == name; }
		)
		, m_ActiveScenes.end()
	);

	m_InactiveScenes.erase
	(
		std::remove_if
		(
			std::begin(m_InactiveScenes), std::end(m_InactiveScenes), [&name](const std::unique_ptr<Scene>& scene) -> bool { return scene->GetName() == name; }
		)
		, m_InactiveScenes.end()
	);
}

void SceneManager::Update()
{
	for(auto& scene : m_ActiveScenes)
	{
		scene->Update();
	}
}

void SceneManager::FixedUpdate()
{
	for (auto& scene : m_ActiveScenes)
	{
		scene->FixedUpdate();
	}
}

void SceneManager::LateUpdate()
{
	for (auto& scene : m_ActiveScenes)
	{
		scene->LateUpdate();	
	}
}

void SceneManager::Render()
{
	for (const auto& scene : m_ActiveScenes)
	{
		scene->Render();
	}
}

void SceneManager::SetActiveScene(Scene* scene, bool active)
{
	if (active)
	{
		const auto it = std::find_if(m_InactiveScenes.begin(), m_InactiveScenes.end(), [scene](const std::unique_ptr<Scene>& ptr) { return ptr.get() == scene; });
		if (it != m_InactiveScenes.end())
		{
			m_ActiveScenes.push_back(std::move(*it));
			m_InactiveScenes.erase(it);
		}
	}
	else
	{
		auto it = std::find_if(m_ActiveScenes.begin(), m_ActiveScenes.end(), [scene](const std::unique_ptr<Scene>& ptr) { return ptr.get() == scene; });
		if (it != m_ActiveScenes.end())
		{
			m_InactiveScenes.push_back(std::move(*it));
			m_ActiveScenes.erase(it);
		}
	}
}
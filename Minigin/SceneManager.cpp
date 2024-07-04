#include <algorithm>

#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"

Scene* SceneManager::CreateScene(const std::string& name)
{
	return m_Scenes.emplace_back(new Scene{ name }).get();
}

Scene* SceneManager::GetScene(const std::string& name)
{
	const auto it{ std::ranges::find_if(m_Scenes, [name](const std::unique_ptr<Scene>& scene) -> bool { return scene->GetName() == name; }) };	

	if (it != m_Scenes.end()) return it->get();
	else return nullptr;
}

void SceneManager::Update(std::chrono::milliseconds deltaTime)
{
	for(auto& scene : m_Scenes)
	{
		scene->Update(deltaTime);
	}
}

void SceneManager::FixedUpdate()
{
	for (auto& scene : m_Scenes)
	{
		scene->FixedUpdate();
	}
}

void SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}
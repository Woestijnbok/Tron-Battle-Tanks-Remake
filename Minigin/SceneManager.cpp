#include <algorithm>

#include "SceneManager.h"
#include "Scene.h"

void SceneManager::Update(std::chrono::milliseconds deltaTime)
{
	for(auto& scene : m_Scenes)
	{
		scene->Update(deltaTime);
	}
}

void SceneManager::FixedUpdate(std::chrono::milliseconds deltaTime)
{
	for (auto& scene : m_Scenes)
	{
		scene->FixedUpdate(deltaTime);
	}
}

void SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

std::shared_ptr<Scene> SceneManager::GetScene(const std::string& name)
{
	const auto it{ std::ranges::find_if(m_Scenes, [name](const std::shared_ptr<Scene>& scene) -> bool { return scene->GetName() == name; }) };

	if (it != m_Scenes.end()) return *it;
	else return nullptr;
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}
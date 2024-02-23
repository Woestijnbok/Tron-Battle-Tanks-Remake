#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>

void dae::SceneManager::Update(std::chrono::milliseconds deltaTime)
{
	for(auto& scene : m_scenes)
	{
		scene->Update(deltaTime);
	}
}

void dae::SceneManager::FixedUpdate(std::chrono::milliseconds deltaTime)
{
	for (auto& scene : m_scenes)
	{
		scene->FixedUpdate(deltaTime);
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

std::shared_ptr<dae::Scene> dae::SceneManager::GetScene(const std::string& name)
{
	const auto it{ std::ranges::find_if(m_scenes, [name](const std::shared_ptr<Scene>& scene) -> bool { return scene->GetName() == name; }) };

	if (it != m_scenes.end()) return *it;
	else return nullptr;
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}

#pragma once

#include <vector>
#include <string>
#include <memory>

#include "Singleton.h"
#include "Scene.h"

class SceneManager final : public Singleton<SceneManager>
{
public:

	~SceneManager() = default;

	SceneManager(const SceneManager&) = delete;
	SceneManager(SceneManager&&) = delete;
	SceneManager& operator= (const SceneManager&) = delete;
	SceneManager& operator= (const SceneManager&&) = delete;

	Scene* CreateScene(const std::string& name, bool active = true);
	Scene* GetScene(const std::string& name);
	void DeleteScene(const std::string& name);
	void Update();
	void FixedUpdate();
	void LateUpdate();
	void Render();
	void SetActiveScene(Scene* scene, bool active);

private:
	friend class Singleton<SceneManager>;
	SceneManager() = default;
	
	std::vector<std::unique_ptr<Scene>> m_ActiveScenes;
	std::vector<std::unique_ptr<Scene>> m_InactiveScenes;
};
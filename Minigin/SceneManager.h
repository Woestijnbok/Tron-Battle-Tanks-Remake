#ifndef SCENE_MANAGER
#define SCENE_MANAGER

#include <vector>
#include <string>
#include <memory>
#include <chrono>

#include "Singleton.h"
#include "Component.h"

class Scene;

class SceneManager final : public Singleton<SceneManager>
{
public:

	

	~SceneManager() = default;

	SceneManager(const SceneManager&) = delete;
	SceneManager(SceneManager&&) = delete;
	SceneManager& operator= (const SceneManager&) = delete;
	SceneManager& operator= (const SceneManager&&) = delete;

	Scene* CreateScene(const std::string& name);
	Scene* GetScene(const std::string& name);
	void Update(std::chrono::milliseconds deltaTime);
	void FixedUpdate();
	void Render();

private:
	friend class Singleton<SceneManager>;
	SceneManager() = default;
	
	std::vector<std::unique_ptr<Scene>> m_Scenes;
};

#endif
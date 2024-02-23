#ifndef SCENE_MANAGER
#define SCENE_MANAGER

#include <vector>
#include <string>
#include <memory>
#include <chrono>

#include "Singleton.h"

class Scene;

class SceneManager final : public Singleton<SceneManager>
{
public:

	~SceneManager() = default;

	SceneManager(const SceneManager&) = delete;
	SceneManager(SceneManager&&) = delete;
	SceneManager& operator= (const SceneManager&) = delete;
	SceneManager& operator= (const SceneManager&&) = delete;

	Scene& CreateScene(const std::string& name);
	void Update(std::chrono::milliseconds deltaTime);
	void FixedUpdate(std::chrono::milliseconds deltaTime);
	void Render();
	std::shared_ptr<Scene> GetScene(const std::string& name);

private:

	SceneManager() = default;

	friend class Singleton<SceneManager>;
	
	std::vector<std::shared_ptr<Scene>> m_Scenes;
};

#endif
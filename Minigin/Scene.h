#ifndef SCENE
#define SCENE

#include <chrono>

#include "SceneManager.h"
#include "Component.h"

class GameObject;

class Scene final
{
	
public:

	friend Scene* SceneManager::CreateScene(const std::string& name);

	~Scene() = default;

	GameObject* CreateGameObject();
	void RemoveGameObject(GameObject* object);
	void Clear();

	void Update(std::chrono::milliseconds deltaTime);
	void FixedUpdate();
	void Render() const;
	const std::string& GetName() const;

private:

	const std::string m_Name;
	std::vector<std::unique_ptr<GameObject>> m_Objects{};

	explicit Scene(const std::string& name);
	
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;
};

#endif
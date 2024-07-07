#pragma once

#include <string>
#include <vector>
#include <memory>

//#include "SceneManager.h"
#include "GameObject.h"

class Scene final
{
	
public:

	//friend Scene* SceneManager::CreateScene(const std::string& name, bool active);
	explicit Scene(const std::string& name);
	~Scene() = default;

	GameObject* CreateGameObject(bool active = true);
	void Clear();

	void Update();
	void FixedUpdate();
	void LateUpdate();
	void Render() const;
	const std::string& GetName() const;
	void SetActive(bool active);
	void SetActiveGameObject(GameObject* object, bool active);

private:

	const std::string m_Name;
	std::vector<std::unique_ptr<GameObject>> m_ActiveObjects;
	std::vector<std::unique_ptr<GameObject>> m_InactiveObjects;
	size_t m_InitialObjectCount;

	
	
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;
};
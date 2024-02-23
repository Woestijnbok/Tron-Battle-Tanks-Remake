#ifndef SCENE
#define SCENE

#include <chrono>

#include "SceneManager.h"

class GameObject;

class Scene final
{
	
public:

	~Scene() = default;

	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

	friend Scene& SceneManager::CreateScene(const std::string& name);

	void Add(std::shared_ptr<GameObject> object);
	void Remove(std::shared_ptr<GameObject> object);
	void RemoveAll();

	void Update(std::chrono::milliseconds deltaTime);
	void FixedUpdate(std::chrono::milliseconds deltaTime);
	void Render() const;
	const std::string& GetName() const;

private:

	static unsigned int m_IdCounter;

	std::string m_Name;
	std::vector < std::shared_ptr<GameObject>> m_Objects{};

	explicit Scene(const std::string& name);
};

#endif
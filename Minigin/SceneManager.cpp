#include "SceneManager.h"

Scene* SceneManager::CreateScene(const std::string& name, bool enabled)
{
	Scene* scene{ new Scene{name} };
	if (!enabled) scene->SetStatus(ControllableObject::Status::Disabled);
	AddControllableObject(scene);

	return scene;
}
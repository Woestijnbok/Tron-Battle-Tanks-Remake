#include "Scene.h"

Scene::Scene(const std::string& name) : 
	ControllableObject{},
	ObjectController{},
	m_Name{ name }
{

}

GameObject* Scene::CreateGameObject(bool enabled)
{
	GameObject* gameObject{ new GameObject{ this } };
	if (!enabled) gameObject->SetStatus(ControllableObject::Status::Disabled);
	AddControllableObject(gameObject);
	
	return gameObject;
}

const std::string& Scene::GetName() const
{
	return m_Name;
}
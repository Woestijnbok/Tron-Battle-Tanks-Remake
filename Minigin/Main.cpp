#include <SDL.h>
#include <iostream>
#if _DEBUG
	// ReSharper disable once CppUnusedIncludeDirective
	#if __has_include(<vld.h>)
	#include <vld.h>
	#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "Texture2D.h"
#include "TextObject.h"

void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	// Background game object
	auto background{ std::make_shared<GameObject>() };
	background->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(background));
	background->AddComponent<Texture2D>(ResourceManager::GetInstance().LoadTexture(background, "background.tga"));
	scene.Add(background);

	// Logo game object
	auto logo{ std::make_shared<GameObject>() };
	logo->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(logo));
	logo->AddComponent<Texture2D>(ResourceManager::GetInstance().LoadTexture(logo, "logo.tga"));
	logo->SetPosition(216, 180);
	scene.Add(logo);

	// Title game object
	auto title{ std::make_shared<GameObject>() };
	title->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(title));
	auto font{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };
	title->AddComponent<TextComponent>(std::make_shared<TextComponent>(title, "Programming 4 Assignment", font));
	title->SetPosition(80.0f, 20.0f);
	scene.Add(title);

	/*auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
	to->SetPosition(80.0f, 20.0f);
	scene.Add(to);*/
}

int main(int, char*[]) {
	Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}
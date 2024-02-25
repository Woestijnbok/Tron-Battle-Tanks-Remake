#include <SDL.h>
#include <iostream>
#if _DEBUG
	// ReSharper disable once CppUnusedIncludeDirective
	#if __has_include(<vld.h>)
	#include <vld.h>
	#endif
#endif

#include "Minigin.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "ImageComponent.h"
#include "TextComponent.h"

void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	// Background game object
	auto background{ std::make_shared<GameObject>() };
	background->AddComponent<RenderComponent>(
		std::make_shared<RenderComponent>(background)
	);
	background->AddComponent<ImageComponent>(
		std::make_shared<ImageComponent>(background, ResourceManager::GetInstance().LoadTexture("background.tga"))
	);
	scene.Add(background);

	// Logo game object
	auto logo{ std::make_shared<GameObject>() };
	logo->AddComponent<RenderComponent>(
		std::make_shared<RenderComponent>(logo)
	);
	background->AddComponent<ImageComponent>(
		std::make_shared<ImageComponent>(logo, ResourceManager::GetInstance().LoadTexture("logo.tga"))
	);
	logo->SetPosition(216, 180);
	scene.Add(logo);

	// Title game object
	auto title{ std::make_shared<GameObject>() };
	title->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(title));
	auto font{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };
	title->AddComponent<TextComponent>(std::make_shared<TextComponent>(title, "Programming 4 Assignment", font));
	title->SetPosition(80.0f, 20.0f);
	scene.Add(title);
}

int main(int, char*[]) {
	Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}
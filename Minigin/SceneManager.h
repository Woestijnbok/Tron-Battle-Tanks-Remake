#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
#include <chrono>

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update(std::chrono::milliseconds deltaTime);
		void FixedUpdate(std::chrono::milliseconds deltaTime);
		void Render();
		std::shared_ptr<Scene> GetScene(const std::string& name);

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;
	};
}

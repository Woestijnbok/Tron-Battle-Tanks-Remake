#pragma once

#include <string>

#include "Singleton.h"
#include "Scene.h"
#include "ObjectController.h"	

namespace Minigin
{
	class SceneManager final : public Singleton<SceneManager>, public ObjectController<Scene>
	{
	public:
		friend class Singleton<SceneManager>;

		~SceneManager() = default;

		SceneManager(const SceneManager&) = delete;
		SceneManager(SceneManager&&) noexcept = delete;
		SceneManager& operator= (const SceneManager&) = delete;
		SceneManager& operator= (const SceneManager&&) noexcept = delete;

		Scene* CreateScene(const std::string& name, bool enabled = true);

	private:
		explicit SceneManager() = default;

	};
}
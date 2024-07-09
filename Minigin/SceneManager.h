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

		~SceneManager() = default;

		Scene* CreateScene(const std::string& name, bool enabled = true);

	private:
		friend class Singleton<SceneManager>;

		SceneManager() = default;

		SceneManager(const SceneManager&) = delete;
		SceneManager(SceneManager&&) = delete;
		SceneManager& operator= (const SceneManager&) = delete;
		SceneManager& operator= (const SceneManager&&) = delete;

	};
}
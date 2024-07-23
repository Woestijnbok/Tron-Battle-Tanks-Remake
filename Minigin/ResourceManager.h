#pragma once

#include <memory>
#include <filesystem>

#include "Singleton.h"

namespace Minigin
{
	class Texture;
	class Font;

	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		friend class Singleton<ResourceManager>;

		~ResourceManager() = default;

		ResourceManager(const ResourceManager&) = delete;
		ResourceManager(ResourceManager&&) noexcept = delete;
		ResourceManager& operator= (const ResourceManager&) = delete;
		ResourceManager& operator= (const ResourceManager&&) noexcept = delete;

		std::shared_ptr<Texture> LoadTexture(const std::filesystem::path& path) const;
		std::shared_ptr<Font> LoadFont(const std::filesystem::path& path, unsigned int size) const;

	private:
		const std::filesystem::path m_TextureRootDirectory;
		const std::filesystem::path m_FontRootDirectory;

		explicit ResourceManager();

	};
}
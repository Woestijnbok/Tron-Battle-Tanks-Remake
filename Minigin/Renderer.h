#pragma once

#include <memory>
#include <filesystem>

#include "Singleton.h"

namespace Minigin
{
	class Texture;					
	class Font;
	class Transform;

	class Renderer final : public Singleton<Renderer>
	{
	public:
		friend class Singleton<Renderer>;

		~Renderer();

		Renderer(const Renderer&) = delete;
		Renderer(Renderer&&) noexcept = delete;
		Renderer& operator= (const Renderer&) = delete;
		Renderer& operator= (const Renderer&&) noexcept = delete;

		void Render() const;
		void Destroy();
		Texture* CreateTexture(const std::filesystem::path& path) const;
		Texture* CreateTexture(Font* font, const std::string& text) const;	
		void RenderTexture(const Texture& texture, const Transform& transform) const;

	private:
		class Impl;
		std::unique_ptr<Impl> m_Pimpl;	

		explicit Renderer();

	};
}
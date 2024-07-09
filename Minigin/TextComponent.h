#pragma once

#include <string>
#include <vec2.hpp>
#include <memory>

#include "Component.h"
#include "Texture.h"

namespace Minigin
{
	class Font;
	class GameObject;

	class TextComponent final : public Component
	{
	public:

		TextComponent(GameObject* owner, const std::string& text, std::shared_ptr<Font> font);
		virtual ~TextComponent() = default;

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		void SetText(const std::string& text);
		std::shared_ptr<Font> GetFont();

	private:

		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::unique_ptr<Texture> m_Texture;
	};
}
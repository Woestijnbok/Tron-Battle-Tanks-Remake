#pragma once

#include <string>
#include <memory>

namespace Minigin
{
	class Font;
	class Texture;
	class Transform;

	class Text final
	{
	public:
		explicit Text(const std::string& text, std::shared_ptr<Font> font);
		virtual ~Text();

		Text(const Text& other) = delete;
		Text(Text&& other) noexcept = delete;
		Text& operator=(const Text& other) = delete;
		Text& operator=(Text&& other) noexcept = delete;

		void Update();
		void Render(const Transform& transform) const;	
		void SetText(const std::string& text);
		std::shared_ptr<Font> GetFont() const;

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::unique_ptr<Texture> m_Texture;

	};
}
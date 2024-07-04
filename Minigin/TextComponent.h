#ifndef TEXT_OBJECT
#define TEXT_OBJECT

#include <string>
#include <memory>
#include <chrono>
#include <vec2.hpp>

#include "Component.h"

class Font;
class GameObject;
class Texture;

class TextComponent final : public Component
{
public:

	TextComponent(GameObject* owner, const std::string& text, std::shared_ptr<Font> font);
	TextComponent(GameObject* owner, const std::string& text, std::shared_ptr<Font> font, glm::vec2 position);
	virtual ~TextComponent() = default;

	TextComponent(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent& operator=(TextComponent&& other) = delete;

	virtual void Update(std::chrono::milliseconds deltaTime) override;
	virtual void Render() const override;

	void SetText(const std::string& text);
	const std::shared_ptr<Texture> GetTexture() const;

private:

	bool m_NeedsUpdate;
	std::string m_Text;
	std::shared_ptr<Font> m_Font;
	std::shared_ptr<Texture> m_Texture;
	glm::vec2 m_Position;
	bool m_SeperatePosition;
};

#endif
#ifndef TEXT_OBJECT
#define TEXT_OBJECT

#include <string>
#include <memory>
#include <chrono>

#include "GameObject.h"
#include "Transform.h"
#include "Component.h"

class Font;
class Texture2D;

class TextComponent final : public Component
{
public:

	TextComponent(const std::string& text, std::shared_ptr<Font> font);
	virtual ~TextComponent() = default;

	TextComponent(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent& operator=(TextComponent&& other) = delete;

	virtual void Update(std::chrono::milliseconds deltaTime) override;
	virtual void FixedUpdate(std::chrono::milliseconds deltaTime) override;
	virtual void Render() const override;

	void SetText(const std::string& text);
	void SetPosition(float x, float y);

private:

	bool m_NeedsUpdate;
	std::string m_Text;
	Transform m_Transform{};
	std::shared_ptr<Font> m_Font;
	std::shared_ptr<Texture2D> m_TextTexture;
};

#endif
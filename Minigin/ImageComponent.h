#ifndef IMAGE_COMPONENT
#define IMAGE_COMPONENT

#include "Component.h"

class GameObject;
class Texture;

class ImageComponent final : public Component
{
public:

	ImageComponent(std::weak_ptr<GameObject> owner, std::shared_ptr<Texture> texture);
	virtual ~ImageComponent() = default;

	ImageComponent(const ImageComponent&) = delete;
	ImageComponent(ImageComponent&&) = delete;
	ImageComponent& operator= (const ImageComponent&) = delete;
	ImageComponent& operator= (const ImageComponent&&) = delete;

	virtual void Update(std::chrono::milliseconds deltaTime) override;
	virtual void FixedUpdate(std::chrono::milliseconds deltaTime) override;
	virtual void Render() const override;

	const std::shared_ptr<Texture> GetTexture() const;

private:

	std::shared_ptr<Texture> m_Texture;
};

#endif
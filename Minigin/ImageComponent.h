#pragma once

#include <memory>

#include "Component.h"

class Texture;

class ImageComponent final : public Component
{
public:

	ImageComponent(GameObject* owner, std::shared_ptr<Texture> texture);
	virtual ~ImageComponent() = default;

	ImageComponent(const ImageComponent&) = delete;
	ImageComponent(ImageComponent&&) = delete;
	ImageComponent& operator= (const ImageComponent&) = delete;
	ImageComponent& operator= (const ImageComponent&&) = delete;

	virtual void Render() const override;
	const std::shared_ptr<Texture> GetTexture() const;

private:

	std::shared_ptr<Texture> m_Texture;
};
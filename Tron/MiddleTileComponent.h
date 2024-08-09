#pragma once

#include <memory>

#include "Component.h"
#include "Texture.h"

class TankComponent;

class MiddleTileComponent final : public Minigin::Component
{
public:
	explicit MiddleTileComponent(Minigin::GameObject* owner);
	virtual ~MiddleTileComponent() = default;

	MiddleTileComponent(const MiddleTileComponent&) = delete;
	MiddleTileComponent(MiddleTileComponent&&) noexcept = delete;
	MiddleTileComponent& operator= (const MiddleTileComponent&) = delete;
	MiddleTileComponent& operator= (const MiddleTileComponent&&) noexcept = delete;

	bool CheckCollision(TankComponent* tank);		

	virtual void Render() const;

private:
	std::unique_ptr<Minigin::Texture> m_Texture;
	const int m_Offset;
};
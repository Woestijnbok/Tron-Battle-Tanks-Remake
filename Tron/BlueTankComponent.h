#pragma once

#include <memory>
#include <chrono>

#include "TankComponent.h"
#include "Texture.h"

class PlayerTankComponent;
class TankManagerComponent;

class BlueTankComponent final : public TankComponent
{
public:
	explicit BlueTankComponent(Minigin::GameObject* owner, TankManagerComponent* manager, const std::shared_ptr<Minigin::Texture>& tankTexture);	
	virtual ~BlueTankComponent() = default;

	BlueTankComponent(const BlueTankComponent&) = delete;
	BlueTankComponent(BlueTankComponent&&) noexcept = delete;
	BlueTankComponent& operator= (const BlueTankComponent&) = delete;
	BlueTankComponent& operator= (const BlueTankComponent&&) noexcept = delete;

	virtual glm::vec2 GetFireDirection() const override;
	virtual void Update() override;
	virtual void Render() const override;

private:
	std::shared_ptr<Minigin::Texture> m_TankTexture;
	std::chrono::steady_clock::time_point m_FireTimePoint;
	bool m_CanFire;

	static const std::chrono::duration<float> m_FireRate;

};


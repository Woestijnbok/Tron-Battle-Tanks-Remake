#ifndef HEALTH_COMPONENT
#define HEALTH_COMPONENT

#include "Component.h"

class HealthComponent :public Component
{
public:
	HealthComponent(std::weak_ptr<GameObject> owner);
	virtual ~HealthComponent() = default;

	HealthComponent(const HealthComponent&) = delete;
	HealthComponent(HealthComponent&&) = delete;
	HealthComponent& operator= (const HealthComponent&) = delete;
	HealthComponent& operator= (const HealthComponent&&) = delete;

	virtual void Update(std::chrono::milliseconds deltaTime) override;
	virtual void FixedUpdate(std::chrono::milliseconds deltaTime) override;

	void Die();
	unsigned int GetLives() const;

private:
	unsigned int m_Lives;
};

#endif // !HEALTH_COMPONENT
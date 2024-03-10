#pragma once
#include "Component.h"

class TrashTheCacheComponent : public Component
{
public:

	TrashTheCacheComponent(std::weak_ptr<GameObject> owner);
	~TrashTheCacheComponent() = default;

	TrashTheCacheComponent(const TrashTheCacheComponent&) = delete;
	TrashTheCacheComponent(TrashTheCacheComponent&&) = delete;
	TrashTheCacheComponent& operator= (const TrashTheCacheComponent&) = delete;
	TrashTheCacheComponent& operator= (const TrashTheCacheComponent&&) = delete;

	virtual void Update(std::chrono::milliseconds deltaTime) override;
	virtual void FixedUpdate(std::chrono::milliseconds deltaTime) override;
	virtual void Render() const override;

private:


};


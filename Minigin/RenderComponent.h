#ifndef RENDER_COMPONENT
#define RENDER_COMPONENT

#include "Component.h"

class RenderComponent final : public Component
{
public:

	RenderComponent(std::shared_ptr<GameObject> owner);
	virtual ~RenderComponent() = default;

	RenderComponent(const RenderComponent& other) = delete;
	RenderComponent(RenderComponent&& other) = delete;
	RenderComponent& operator=(const RenderComponent& other) = delete;
	RenderComponent& operator=(RenderComponent&& other) = delete;

	virtual void Update(std::chrono::milliseconds deltaTime) override;
	virtual void FixedUpdate(std::chrono::milliseconds deltaTime) override;

	void Render() const;

private:

	
};

#endif
#ifndef FPS_COUNTER_COMPONENT
#define FPS_COUNTER_COMPONENT

#include "chrono"

#include "Component.h"
#include "Singleton.h"

class Font;
class Texture;
class GameObject;

class FPSCounterComponent final : public Component
{
public:

	FPSCounterComponent(std::weak_ptr<GameObject> owner);
	~FPSCounterComponent() = default;

	FPSCounterComponent(const FPSCounterComponent&) = delete;
	FPSCounterComponent(FPSCounterComponent&&) = delete;
	FPSCounterComponent& operator= (const FPSCounterComponent&) = delete;
	FPSCounterComponent& operator= (const FPSCounterComponent&&) = delete;

	virtual void Update(std::chrono::milliseconds deltaTime) override;
	virtual void FixedUpdate(std::chrono::milliseconds deltaTime) override;

	const std::shared_ptr<Texture> GetTexture() const;
	void SetText(const std::string& text);

private:

	std::string m_Text;
	std::shared_ptr<Font> m_Font;
	std::shared_ptr<Texture> m_Texture;
	std::chrono::steady_clock::time_point m_LastTimePoint;
	unsigned int m_FrameCounter;
};

#endif
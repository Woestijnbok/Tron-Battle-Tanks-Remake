#pragma once

#include <memory>
#include <chrono>

#include "Component.h"

namespace Minigin
{
	class Sprite;

	class SpriteComponent : public Component
	{
	public:
		explicit SpriteComponent(GameObject* owner, std::shared_ptr<Sprite> sprite, std::chrono::milliseconds frameTime);	
		~SpriteComponent();

		SpriteComponent(const SpriteComponent&) = delete;
		SpriteComponent(SpriteComponent&&) noexcept = delete;
		SpriteComponent& operator= (const SpriteComponent&) = delete;
		SpriteComponent& operator= (const SpriteComponent&&) noexcept = delete;

		virtual void Update() override;
		virtual void Render() const override;

		std::shared_ptr<Sprite> GetSprite() const;
		void Reset();

	private:
		std::shared_ptr<Sprite> m_Sprite;
		std::chrono::milliseconds m_FrameTime;
		std::chrono::steady_clock::time_point m_LastTimePoint;
		int m_Frame;
		bool m_Running;
	};
}
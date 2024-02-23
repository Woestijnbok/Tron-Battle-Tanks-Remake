#pragma once
#include <string>
#include <functional>
#include <chrono>

namespace dae
{
	class TextObject;

	class Minigin
	{
	public:
		explicit Minigin(const std::string& dataPath);
		~Minigin();
		void Run(const std::function<void()>& load);

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

	private:

		const int m_MaxFrameRate;
		const std::chrono::milliseconds m_MinFrameDuration;
		const std::chrono::milliseconds m_FixedDuration;
		std::shared_ptr<TextObject> m_FPSCounter;

		std::chrono::milliseconds CalculateMinFrameDuration(int frameRate);
	};
}
#pragma once

#include <chrono>

class TimeManager final
{
public:

	TimeManager() = delete;
	~TimeManager() = delete;

	TimeManager(const TimeManager& other) = delete;
	TimeManager(TimeManager&& other) = delete;
	TimeManager& operator=(const TimeManager& other) = delete;
	TimeManager& operator=(TimeManager&& other) = delete;

	static void SetDeltaTime(std::chrono::milliseconds delta);	
	static std::chrono::milliseconds GetDeltaTime();
	static std::chrono::milliseconds GetFixedDeltaTime();

private:

	static std::chrono::milliseconds m_DeltaTime;
	static const std::chrono::milliseconds m_FixedDeltaTime;

};
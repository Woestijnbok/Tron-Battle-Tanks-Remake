#include "TimeManager.h"

std::chrono::milliseconds TimeManager::m_DeltaTime{ 0 };
const std::chrono::milliseconds TimeManager::m_FixedDeltaTime{ 20 };

void TimeManager::SetDeltaTime(std::chrono::milliseconds delta)
{
	m_DeltaTime = delta;
}

std::chrono::milliseconds TimeManager::GetDeltaTime()
{
	return m_DeltaTime;
}

std::chrono::milliseconds TimeManager::GetFixedDeltaTime()
{
	return m_FixedDeltaTime;
}

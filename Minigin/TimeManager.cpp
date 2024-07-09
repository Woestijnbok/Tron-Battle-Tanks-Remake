#include "TimeManager.h"

using namespace Minigin;

std::chrono::milliseconds TimeManager::m_DeltaTime{ 0 };
const std::chrono::milliseconds TimeManager::m_FixedDeltaTime{ 20 };

void TimeManager::SetDeltaTime(std::chrono::milliseconds delta)
{
	m_DeltaTime = delta;
}

std::chrono::duration<float> TimeManager::GetDeltaTime()
{
	return std::chrono::duration_cast<std::chrono::duration<float>>(m_DeltaTime);
}

std::chrono::milliseconds TimeManager::GetFixedDeltaTime()
{
	return m_FixedDeltaTime;
}

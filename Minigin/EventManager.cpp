#include "EventManager.h"

Event::Event(EventType type) :
	m_Type{ type },
	m_NumberArguments{  },
	m_WordArguments{  }
{

}

void Event::AddArgument(int number)
{
	m_NumberArguments.push_back(number);
}

void Event::AddArgument(std::string word)
{
	m_WordArguments.push_back(word);
}

EventType Event::GetType() const
{
	return m_Type;
}

std::vector<int> Event::GetNumberArguments() const
{
	return m_NumberArguments;
}

std::vector<std::string> Event::GetWordArguments() const
{
	return m_WordArguments;
}

EventManager::EventManager() :
	m_EventHandlers{},
	m_Events{}
{
	m_EventHandlers[EventType::PlayerDied] = std::vector<std::function<void(const Event&)>>{};
}

void EventManager::Update()
{
	for (const Event& event : m_Events)
	{
		for (const auto& handler : m_EventHandlers[event.GetType()])
		{
			handler(event);
		}
	}

	m_Events.clear();
}

void EventManager::SendEvent(const Event& event)
{
	m_Events.push_back(event);
}

void EventManager::AddHandler(EventType type, std::function<void(const Event&)> handler)
{
	m_EventHandlers.at(type).push_back(handler);
}
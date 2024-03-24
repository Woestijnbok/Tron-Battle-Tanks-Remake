#include "EventManager.h"

Event::Event(EventType type, void* caller) :
	m_Type{ type },
	m_NumberArguments{  },
	m_WordArguments{  },
	m_Caller{ caller }
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

void* Event::GetCaller() const
{
	return m_Caller;
}

EventManager::EventManager() :
	m_EventHandlers{},
	m_Events{}
{
	for (int i{}; i < EventType::NumberOfTypes; ++i)
	{
		m_EventHandlers[static_cast<EventType>(i)] = std::vector<std::function<void(const Event&)>>{};
	}
}

void EventManager::Update()
{
	// For now we do the whole queue every time.
	while (!m_Events.empty())
	{
		for (const auto& handler : m_EventHandlers[m_Events.front().GetType()])
		{
			handler(m_Events.front());
		}

		m_Events.pop();
	}
}

void EventManager::SendEvent(const Event& event)
{
	m_Events.push(event);
}

void EventManager::AddHandler(EventType type, std::function<void(const Event&)> handler)
{
	m_EventHandlers.at(type).push_back(handler);
}

void EventManager::RemoveHandler(EventType type, std::function<void(const Event&)> handlerToRemove)
{
	auto& vector{ m_EventHandlers.at(type) };

	vector.erase(std::remove_if(vector.begin(), vector.end(), 
		[&handlerToRemove](std::function<void(const Event&)> handler) -> bool 
		{
			return handler.target_type() == handlerToRemove.target_type();
		}
	), vector.end());
}
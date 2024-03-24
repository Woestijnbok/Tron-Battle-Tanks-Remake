#ifndef EVENT_MANAGER
#define EVENT_MANAGER

#include <vector>
#include <string>
#include <map>
#include <functional>

#include "Singleton.h"

enum EventType
{
	PlayerDied
};

class Event final
{
public:
	Event(EventType type);
	~Event() = default;

	Event(const Event&) = default;
	Event(Event&&) = default;
	Event& operator= (const Event&) = delete;
	Event& operator= (const Event&&) = delete;

	void AddArgument(int number);
	void AddArgument(std::string word);
	EventType GetType() const;
	std::vector<int> GetNumberArguments() const;
	std::vector<std::string> GetWordArguments() const;

private:
	EventType m_Type;
	std::vector<int> m_NumberArguments;
	std::vector<std::string> m_WordArguments;

};

class EventManager final : public Singleton<EventManager>
{
public:
	EventManager();
	~EventManager() = default;

	EventManager(const EventManager&) = delete;
	EventManager(EventManager&&) = delete;
	EventManager& operator= (const EventManager&) = delete;
	EventManager& operator= (const EventManager&&) = delete;

	void Update();
	void SendEvent(const Event& event);
	void AddHandler(EventType type, std::function<void(const Event&)> handler);

private:
	std::map<EventType, std::vector<std::function<void(const Event&)>>> m_EventHandlers;
	std::vector<Event> m_Events;
};

#endif
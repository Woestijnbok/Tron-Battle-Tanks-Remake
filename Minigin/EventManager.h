#pragma once

#include <vector>
#include <string>
#include <map>
#include <functional>
#include <queue>

#include "Singleton.h"

enum EventType
{
	PlayerDied,
	ScoreUpdated,
	NumberOfTypes
};

class Event final
{
public:
	Event(EventType type, void* caller);
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
	void* GetCaller() const;

private:
	EventType m_Type;
	std::vector<int> m_NumberArguments;
	std::vector<std::string> m_WordArguments;
	void* m_Caller;

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
	void RemoveHandler(EventType type, std::function<void(const Event&)> handlerToRemove);

private:
	std::map<EventType, std::vector<std::function<void(const Event&)>>> m_EventHandlers;
	std::queue<Event> m_Events;
};
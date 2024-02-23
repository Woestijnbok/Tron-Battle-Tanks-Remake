#pragma once
#include <chrono>

class Component
{
public:

	Component() = default;
	virtual ~Component() = default;

	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;

	virtual void Update(std::chrono::milliseconds deltaTime) = 0;
	virtual void FixedUpdate(std::chrono::milliseconds deltaTime) = 0;

private:

	
};
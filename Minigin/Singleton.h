#pragma once

template <typename Type>
class Singleton
{
public:

	virtual ~Singleton() = default;

	Singleton(const Singleton& other) = delete;
	Singleton(Singleton&& other) = delete;
	Singleton& operator=(const Singleton& other) = delete;
	Singleton& operator=(Singleton&& other) = delete;

	static Type& GetInstance()
	{
		static Type instance{};
		return instance;
	}

protected:

	Singleton() = default;
};
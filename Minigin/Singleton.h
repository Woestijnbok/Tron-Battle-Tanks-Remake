#pragma once

namespace Minigin
{
	template <typename Type>
	class Singleton
	{
	public:
		virtual ~Singleton() = default;

		Singleton(const Singleton& other) = delete;
		Singleton(Singleton&& other)  noexcept = delete;
		Singleton& operator=(const Singleton& other) = delete;
		Singleton& operator=(Singleton&& other) noexcept = delete;

		static Type& GetInstance()
		{
			static Type instance{};
			return instance;
		}

	protected:
		explicit Singleton() = default;

	private:


	};
}
#pragma once

#include <chrono>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#include "Component.h"

class TrashTheCacheComponent : public Component
{
public:

	TrashTheCacheComponent(std::weak_ptr<GameObject> owner);
	~TrashTheCacheComponent();

	TrashTheCacheComponent(const TrashTheCacheComponent&) = delete;
	TrashTheCacheComponent(TrashTheCacheComponent&&) = delete;
	TrashTheCacheComponent& operator= (const TrashTheCacheComponent&) = delete;
	TrashTheCacheComponent& operator= (const TrashTheCacheComponent&&) = delete;

	virtual void Update(std::chrono::milliseconds deltaTime) override;
	virtual void FixedUpdate(std::chrono::milliseconds deltaTime) override;
	virtual void Render() const override;

private:

	struct transform
	{
		float matrix[16]
		{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	};

	class GameObject3D
	{
	public:
		transform local{};
		int id{};
	};

	class GameObject3DAlt
	{
	public:
		transform* local{};
		int id{};
	};

	template<typename ObjectType, typename OperationType>
	void Measure(OperationType operation, float* const data)
	{
		float measurements[11][10]{};

		for (int indexMeasurement{}; indexMeasurement < 10; ++indexMeasurement)
		{
			ObjectType* buffer{ new ObjectType[m_BufferSize]{} };

			int indexStepSize{};
			for (int stepSize = 1; stepSize <= 1024; stepSize *= 2)
			{
				auto start{ std::chrono::steady_clock::now() };

				for (size_t i = 0; i < m_BufferSize; i += stepSize)
				{
					operation(buffer[i]);
				}

				auto end{ std::chrono::steady_clock::now() };
				auto time{ std::chrono::duration_cast<std::chrono::microseconds>(end - start) };

				measurements[indexStepSize][indexMeasurement] = float(time.count());

				++indexStepSize;
			}

			delete[] buffer;
		}

		for (int i{}; i < 11; ++i)
		{
			auto [minIter, maxIter] = std::minmax_element(&measurements[i][0], &measurements[i][10]);
			float sum{ std::accumulate(&measurements[i][0], &measurements[i][10], 0.0f) };
			float average{ (sum - *minIter - *maxIter) / 8.0f };
			//std::cout << average << std::endl;
			data[i] = average;
		}
	}

	template<typename ObjectType, typename OperationType>
	void MeasureOnce(OperationType operation, float* const data)
	{
		ObjectType* buffer{ new ObjectType[m_BufferSize]{} };

		int indexStepSize{};
		for (int stepSize = 1; stepSize <= 1024; stepSize *= 2)
		{
			auto start{ std::chrono::steady_clock::now() };

			for (int i = 0; i < m_BufferSize; i += stepSize)
			{
				operation(buffer[i]);
			}

			auto end{ std::chrono::steady_clock::now() };
			auto time{ std::chrono::duration_cast<std::chrono::microseconds>(end - start) };

			data[indexStepSize] = float(time.count());
			//std::cout << data[indexStepSize] << std::endl;

			++indexStepSize;
		}

		delete[] buffer;
	}

	const size_t m_BufferSize;
	float* m_StepSizes;
	float* m_IntegerData;
	float* m_GameObjectData;
	float* m_GameObjectAltData;
	bool* m_ButtonsPressed;
};


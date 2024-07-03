#include "TrashTheCacheComponent.h"
#include "imgui.h"
#include "implot.h"

TrashTheCacheComponent::TrashTheCacheComponent(std::weak_ptr<GameObject> owner) :
	Component{ owner },
	m_BufferSize{ 1000000 },
	m_StepSizes{ new float[11] { 1.0f, 2.0f, 4.0f, 8.0f, 16.0f, 32.0f, 64.0f, 128.0f, 256.0f, 512.0f, 1024.0f } },
	m_IntegerData{ new float[11] { 1.0f, 2.0f, 4.0f, 8.0f, 16.0f, 32.0f, 64.0f, 128.0f, 256.0f, 512.0f, 1024.0f } },
	m_GameObjectData{ new float[11] { 1.0f, 2.0f, 4.0f, 8.0f, 16.0f, 32.0f, 64.0f, 128.0f, 256.0f, 512.0f, 1024.0f } },
	m_GameObjectAltData{ new float[11] { 1.0f, 2.0f, 4.0f, 8.0f, 16.0f, 32.0f, 64.0f, 128.0f, 256.0f, 512.0f, 1024.0f } },
	m_ButtonsPressed{ new bool[2] { false, false } }
{
	int sum{};
	Measure<int>([&sum](int x) -> void { sum += x; }, m_IntegerData);
	Measure<GameObject3D>([&sum](GameObject3D& x) -> void { sum += x.id; }, m_GameObjectData);
	Measure<GameObject3DAlt>([&sum](GameObject3DAlt& x) -> void { sum += x.id; }, m_GameObjectAltData);
}

TrashTheCacheComponent::~TrashTheCacheComponent()
{
	delete m_ButtonsPressed;
	delete m_StepSizes;
	delete m_IntegerData;
	delete m_GameObjectData;
	delete m_GameObjectAltData;
}

void TrashTheCacheComponent::Update(std::chrono::milliseconds deltaTime)
{
	deltaTime;

	int sum{};
	if (m_ButtonsPressed[0]) 
	{
		Measure<int>([&sum](int x) -> void { sum += x; }, m_IntegerData);
		m_ButtonsPressed[0] = false;
	}
	if (m_ButtonsPressed[1])
	{
		Measure<GameObject3D>([&sum](GameObject3D& x) -> void { sum += x.id; }, m_GameObjectData);
		Measure<GameObject3DAlt>([&sum](GameObject3DAlt& x) -> void { sum += x.id; }, m_GameObjectAltData);
		m_ButtonsPressed[1] = false;
	}
}

void TrashTheCacheComponent::FixedUpdate(std::chrono::milliseconds deltaTime)
{
	deltaTime;
}

void TrashTheCacheComponent::Render() const
{
	ImGui::Begin("Exercise 1");

	if (ImGui::Button("Resample"))
	{
		m_ButtonsPressed[0] = true;
	}

	if (ImPlot::BeginPlot("Integer buffer"))
	{
		ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
		ImPlot::PlotLine("Integer", m_StepSizes, m_IntegerData, 11);
		ImPlot::EndPlot();
	}
	
	ImGui::End();

	ImGui::Begin("Exercise 2");

	if (ImGui::Button("Resample"))
	{
		m_ButtonsPressed[1] = true;
		m_ButtonsPressed[2] = true;
	}

	if (ImPlot::BeginPlot("GameObject buffer"))
	{
		ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
		ImPlot::PlotLine("GameObject", m_StepSizes, m_GameObjectData, 11);
		ImPlot::EndPlot();
	}
	if (ImPlot::BeginPlot("GameObjectAlt buffer"))
	{
		ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
		ImPlot::PlotLine("GameObjectAlt", m_StepSizes, m_GameObjectAltData, 11);
		ImPlot::EndPlot();
	}
	if (ImPlot::BeginPlot("GameObject Versus GameObjectAlt"))
	{
		ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
		ImPlot::PlotLine("GameObject", m_StepSizes, m_GameObjectData, 11);
		ImPlot::PlotLine("GameObjectAlt", m_StepSizes, m_GameObjectAltData, 11);
		ImPlot::EndPlot();
	}

	ImGui::End();
}
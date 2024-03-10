#include "TrashTheCacheComponent.h"
#include "ImGui.h"
#include "ImPlot.h"

TrashTheCacheComponent::TrashTheCacheComponent(std::weak_ptr<GameObject> owner) :
	Component{ owner }
{

}

void TrashTheCacheComponent::Update(std::chrono::milliseconds deltaTime)
{
	deltaTime;
}

void TrashTheCacheComponent::FixedUpdate(std::chrono::milliseconds deltaTime)
{
	deltaTime;
}

void TrashTheCacheComponent::Render() const
{
	ImPlot::ShowDemoWindow();
}
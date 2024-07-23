#pragma once

#include "Component.h"
#include "Subject.h"

class TestObserverComponent : public Minigin::Component
{
public:
	TestObserverComponent(Minigin::GameObject* object);
	Minigin::Subject<int, int>& GetTestSubject();
	void TestTester();

private:

	Minigin::Subject<int, int> m_TestSubject;
};
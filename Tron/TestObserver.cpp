#include "TestObserver.h"

TestObserverComponent::TestObserverComponent(Minigin::GameObject* object) :
	Minigin::Component{ object }
{
}

Minigin::Subject<int, int>& TestObserverComponent::GetTestSubject()
{
	// TODO: insert return statement here
	return m_TestSubject;
}

void TestObserverComponent::TestTester()
{
	m_TestSubject.Notify(2, 3);
}

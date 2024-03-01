#include "Component.h"

Component::Component(std::weak_ptr<GameObject> owner) :
	m_Owner{ owner }
{
	
}
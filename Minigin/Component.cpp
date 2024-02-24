#include "Component.h"

Component::Component(std::shared_ptr<GameObject> owner) :
	m_Owner{ owner }
{
	
}
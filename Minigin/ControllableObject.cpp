#include "ControllableObject.h"

void ControllableObject::SetStatus(ControllableObject::Status status)
{
	m_Status = status;
}

ControllableObject::Status ControllableObject::GetStatus() const
{
	return m_Status;
	
}	
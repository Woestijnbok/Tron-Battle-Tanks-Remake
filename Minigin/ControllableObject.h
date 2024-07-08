#pragma once

class ControllableObject
{
public:

	enum class Status
	{
		Enabled,
		Disabled,
		Destroyed
	};

	void SetStatus(ControllableObject::Status status);
	ControllableObject::Status GetStatus() const;

protected:

	ControllableObject() = default;
	~ControllableObject() = default;

	ControllableObject(const ControllableObject&) = delete;
	ControllableObject(ControllableObject&&) = delete;
	ControllableObject& operator= (const ControllableObject&) = delete;
	ControllableObject& operator= (const ControllableObject&&) = delete;

private:

	ControllableObject::Status m_Status;

};
#ifndef COMMAND
#define COMMAND

#include <memory>

#include "GameObject.h"
#include "Component.h"

class Command
{
public:
	Command() = default;
	virtual ~Command() = default;

	Command(const Command&) = delete;
	Command(Command&&) = delete;
	Command& operator= (const Command&) = delete;
	Command& operator= (const Command&&) = delete;

	virtual void Execute(std::chrono::milliseconds deltaTime) const = 0;

protected:
	

private:


};

class GameObjectCommand : public Command
{
public:
	GameObjectCommand(GameObject* gameObject);
	virtual ~GameObjectCommand() = default;

	GameObjectCommand(const GameObjectCommand&) = delete;
	GameObjectCommand(GameObjectCommand&&) = delete;
	GameObjectCommand& operator= (const GameObjectCommand&) = delete;
	GameObjectCommand& operator= (const GameObjectCommand&&) = delete;

	virtual void Execute(std::chrono::milliseconds deltaTime) const override = 0;
	GameObject* GetGameObject();

protected:
	GameObject* m_GameObject;

private:


};

#endif
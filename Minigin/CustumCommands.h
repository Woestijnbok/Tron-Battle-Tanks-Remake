#ifndef CUSTOM_COMMANDS
#define CUSTOM_COMMANDS

#include "Command.h"

class TestCommand final : public Command
{
public:
	TestCommand() = default;
	virtual ~TestCommand() = default;

	TestCommand(const TestCommand&) = delete;
	TestCommand(TestCommand&&) = delete;
	TestCommand& operator= (const TestCommand&) = delete;
	TestCommand& operator= (const TestCommand&&) = delete;

	virtual void Execute(std::chrono::milliseconds deltaTime) const override;


private:


};

class TestGameObjectCommand final : public GameObjectCommand
{
public:
	TestGameObjectCommand(GameObject* gameObject);
	virtual ~TestGameObjectCommand() = default;

	TestGameObjectCommand(const TestGameObjectCommand&) = delete;
	TestGameObjectCommand(TestGameObjectCommand&&) = delete;
	TestGameObjectCommand& operator= (const TestGameObjectCommand&) = delete;
	TestGameObjectCommand& operator= (const TestGameObjectCommand&&) = delete;

	virtual void Execute(std::chrono::milliseconds deltaTime) const override;


private:


};

class MoveLeft final : public GameObjectCommand
{
public:
	MoveLeft(GameObject* gameObject);
	virtual ~MoveLeft() = default;

	MoveLeft(const MoveLeft&) = delete;
	MoveLeft(MoveLeft&&) = delete;
	MoveLeft& operator= (const MoveLeft&) = delete;
	MoveLeft& operator= (const MoveLeft&&) = delete;

	virtual void Execute(std::chrono::milliseconds deltaTime) const override;


private:


};

class MoveRight final : public GameObjectCommand
{
public:
	MoveRight(GameObject* gameObject);
	virtual ~MoveRight() = default;

	MoveRight(const MoveRight&) = delete;
	MoveRight(MoveRight&&) = delete;
	MoveRight& operator= (const MoveRight&) = delete;
	MoveRight& operator= (const MoveRight&&) = delete;

	virtual void Execute(std::chrono::milliseconds deltaTime) const override;


private:


};

class MoveUp final : public GameObjectCommand
{
public:
	MoveUp(GameObject* gameObject);
	virtual ~MoveUp() = default;

	MoveUp(const MoveUp&) = delete;
	MoveUp(MoveUp&&) = delete;
	MoveUp& operator= (const MoveUp&) = delete;
	MoveUp& operator= (const MoveUp&&) = delete;

	virtual void Execute(std::chrono::milliseconds deltaTime) const override;


private:


};

class MoveDown final : public GameObjectCommand
{
public:
	MoveDown(GameObject* gameObject);
	virtual ~MoveDown() = default;

	MoveDown(const MoveDown&) = delete;
	MoveDown(MoveDown&&) = delete;
	MoveDown& operator= (const MoveDown&) = delete;
	MoveDown& operator= (const MoveDown&&) = delete;

	virtual void Execute(std::chrono::milliseconds deltaTime) const override;


private:


};

#endif
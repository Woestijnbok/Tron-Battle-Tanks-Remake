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

	virtual void Execute() const override;


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

	virtual void Execute() const override;


private:


};

#endif
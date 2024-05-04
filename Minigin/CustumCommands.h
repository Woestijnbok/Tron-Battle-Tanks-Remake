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

class PlayerDie final : public GameObjectCommand
{
public:
	PlayerDie(GameObject* gameObject);
	virtual ~PlayerDie() = default;

	PlayerDie(const PlayerDie&) = delete;
	PlayerDie(PlayerDie&&) = delete;
	PlayerDie& operator= (const PlayerDie&) = delete;
	PlayerDie& operator= (const PlayerDie&&) = delete;

	virtual void Execute(std::chrono::milliseconds deltaTime) const override;


private:


};

class Add100Score final : public GameObjectCommand
{
public:
	Add100Score(GameObject* gameObject);
	virtual ~Add100Score() = default;

	Add100Score(const Add100Score&) = delete;
	Add100Score(Add100Score&&) = delete;
	Add100Score& operator= (const Add100Score&) = delete;
	Add100Score& operator= (const Add100Score&&) = delete;

	virtual void Execute(std::chrono::milliseconds deltaTime) const override;


private:


};

class TestMusic1 final : public Command
{
public:
	TestMusic1() = default;
	virtual ~TestMusic1() = default;

	TestMusic1(const TestMusic1&) = delete;
	TestMusic1(TestMusic1&&) = delete;
	TestMusic1& operator= (const TestMusic1&) = delete;
	TestMusic1& operator= (const TestMusic1&&) = delete;

	virtual void Execute(std::chrono::milliseconds deltaTime) const override;


private:


};

class TestMusic2 final : public Command
{
public:
	TestMusic2() = default;
	virtual ~TestMusic2() = default;

	TestMusic2(const TestMusic2&) = delete;
	TestMusic2(TestMusic2&&) = delete;
	TestMusic2& operator= (const TestMusic2&) = delete;
	TestMusic2& operator= (const TestMusic2&&) = delete;

	virtual void Execute(std::chrono::milliseconds deltaTime) const override;


private:


};

class TestSoundEffect1 final : public Command
{
public:
	TestSoundEffect1() = default;
	virtual ~TestSoundEffect1() = default;

	TestSoundEffect1(const TestSoundEffect1&) = delete;
	TestSoundEffect1(TestSoundEffect1&&) = delete;
	TestSoundEffect1& operator= (const TestSoundEffect1&) = delete;
	TestSoundEffect1& operator= (const TestSoundEffect1&&) = delete;

	virtual void Execute(std::chrono::milliseconds deltaTime) const override;


private:


};

class TestSoundEffect2 final : public Command
{
public:
	TestSoundEffect2() = default;
	virtual ~TestSoundEffect2() = default;

	TestSoundEffect2(const TestSoundEffect2&) = delete;
	TestSoundEffect2(TestSoundEffect2&&) = delete;
	TestSoundEffect2& operator= (const TestSoundEffect2&) = delete;
	TestSoundEffect2& operator= (const TestSoundEffect2&&) = delete;

	virtual void Execute(std::chrono::milliseconds deltaTime) const override;


private:


};

class StopMusic final : public Command
{
public:
	StopMusic() = default;
	virtual ~StopMusic() = default;

	StopMusic(const StopMusic&) = delete;
	StopMusic(StopMusic&&) = delete;
	StopMusic& operator= (const StopMusic&) = delete;
	StopMusic& operator= (const StopMusic&&) = delete;

	virtual void Execute(std::chrono::milliseconds deltaTime) const override;


private:


};

class StopAll final : public Command
{
public:
	StopAll() = default;
	virtual ~StopAll() = default;

	StopAll(const StopAll&) = delete;
	StopAll(StopAll&&) = delete;
	StopAll& operator= (const StopAll&) = delete;
	StopAll& operator= (const StopAll&&) = delete;

	virtual void Execute(std::chrono::milliseconds deltaTime) const override;


private:


};

#endif
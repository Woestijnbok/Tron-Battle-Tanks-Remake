#pragma once

#include "Command.h"

class TestMusic1 final : public Minigin::Command
{
public:
	TestMusic1() = default;
	virtual ~TestMusic1() = default;

	TestMusic1(const TestMusic1&) = delete;
	TestMusic1(TestMusic1&&) = delete;
	TestMusic1& operator= (const TestMusic1&) = delete;
	TestMusic1& operator= (const TestMusic1&&) = delete;

	virtual void Execute() const override;


private:


};

class TestMusic2 final : public Minigin::Command
{
public:
	TestMusic2() = default;
	virtual ~TestMusic2() = default;

	TestMusic2(const TestMusic2&) = delete;
	TestMusic2(TestMusic2&&) = delete;
	TestMusic2& operator= (const TestMusic2&) = delete;
	TestMusic2& operator= (const TestMusic2&&) = delete;

	virtual void Execute() const override;


private:


};

class TestSoundEffect1 final : public Minigin::Command
{
public:
	TestSoundEffect1() = default;
	virtual ~TestSoundEffect1() = default;

	TestSoundEffect1(const TestSoundEffect1&) = delete;
	TestSoundEffect1(TestSoundEffect1&&) = delete;
	TestSoundEffect1& operator= (const TestSoundEffect1&) = delete;
	TestSoundEffect1& operator= (const TestSoundEffect1&&) = delete;

	virtual void Execute() const override;


private:


};

class TestSoundEffect2 final : public Minigin::Command
{
public:
	TestSoundEffect2() = default;
	virtual ~TestSoundEffect2() = default;

	TestSoundEffect2(const TestSoundEffect2&) = delete;
	TestSoundEffect2(TestSoundEffect2&&) = delete;
	TestSoundEffect2& operator= (const TestSoundEffect2&) = delete;
	TestSoundEffect2& operator= (const TestSoundEffect2&&) = delete;

	virtual void Execute() const override;


private:


};

class StopMusic final : public Minigin::Command
{
public:
	StopMusic() = default;
	virtual ~StopMusic() = default;

	StopMusic(const StopMusic&) = delete;
	StopMusic(StopMusic&&) = delete;
	StopMusic& operator= (const StopMusic&) = delete;
	StopMusic& operator= (const StopMusic&&) = delete;

	virtual void Execute() const override;


private:


};

class StopAll final : public Minigin::Command
{
public:
	StopAll() = default;
	virtual ~StopAll() = default;

	StopAll(const StopAll&) = delete;
	StopAll(StopAll&&) = delete;
	StopAll& operator= (const StopAll&) = delete;
	StopAll& operator= (const StopAll&&) = delete;

	virtual void Execute() const override;


private:


};
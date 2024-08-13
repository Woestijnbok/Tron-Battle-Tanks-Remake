#pragma once

#include "Command.h"

class SkipCommand final : public Minigin::Command
{
public:
	explicit SkipCommand() = default;
	~SkipCommand() = default;

	SkipCommand(const SkipCommand&) = delete;
	SkipCommand(SkipCommand&&) noexcept = delete;
	SkipCommand& operator= (const SkipCommand&) = delete;
	SkipCommand& operator= (const SkipCommand&&) noexcept = delete;

	virtual void Execute() override;

};
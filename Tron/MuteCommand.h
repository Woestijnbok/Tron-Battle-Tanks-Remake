#pragma once

#include "Command.h"

class MuteCommand final : public Minigin::Command
{
public:
	explicit MuteCommand() = default;
	~MuteCommand() = default;

	MuteCommand(const MuteCommand&) = delete;
	MuteCommand(MuteCommand&&) noexcept = delete;
	MuteCommand& operator= (const MuteCommand&) = delete;
	MuteCommand& operator= (const MuteCommand&&) noexcept = delete;

	virtual void Execute() override;

private:
	bool m_IsMute;
};
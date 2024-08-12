#pragma once

#include "Command.h"

class MenuCommand final : public Minigin::Command
{
public:
	explicit MenuCommand() = default;
	virtual ~MenuCommand() = default;

	MenuCommand(const MenuCommand&) = delete;
	MenuCommand(MenuCommand&&) noexcept = delete;
	MenuCommand& operator= (const MenuCommand&) = delete;
	MenuCommand& operator= (const MenuCommand&&) noexcept = delete;

	void Execute() override;
};

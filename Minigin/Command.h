#pragma once

namespace Minigin
{
	class GameObject;

	class Command
	{
	public:
		explicit Command() = default;
		virtual ~Command() = default;

		Command(const Command&) = delete;
		Command(Command&&) noexcept = delete;
		Command& operator= (const Command&) = delete;
		Command& operator= (const Command&&) noexcept = delete;

		virtual void Execute() = 0;

	protected:


	private:


	};

	class GameObjectCommand : public Command
	{
	public:
		explicit GameObjectCommand(GameObject* gameObject);
		virtual ~GameObjectCommand() = default;

		GameObjectCommand(const GameObjectCommand&) = delete;
		GameObjectCommand(GameObjectCommand&&) noexcept = delete;
		GameObjectCommand& operator= (const GameObjectCommand&) = delete;
		GameObjectCommand& operator= (const GameObjectCommand&&) noexcept = delete;

		virtual void Execute() override = 0;

		GameObject* GetGameObject();

	protected:


	private:
		GameObject* m_GameObject;

	};
}
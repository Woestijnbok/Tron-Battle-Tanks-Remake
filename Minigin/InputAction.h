#ifndef INPUT_ACTION
#define INPUT_ACTION

#include <SDL.h>
#include <memory>

#include "Command.h"

class InputAction final
{
public:
	InputAction(SDL_KeyCode keyCode, Command* command);
	~InputAction() = default;

	InputAction(const InputAction&) = delete;
	InputAction(InputAction&&) noexcept = default;
	InputAction& operator= (const InputAction&) = delete;
	InputAction& operator= (const InputAction&&) = delete;

	std::weak_ptr<GameObject> GetGameObject();
	Command* GetCommand() const;
	SDL_KeyCode GetSDLKeyCode() const;

	bool operator==(const InputAction& rhs) const;
	bool operator<(const InputAction& rhs) const;

	friend struct std::hash<InputAction>;
		
private:
	SDL_KeyCode m_KeyCode;
	std::unique_ptr<Command> m_Command;
};

template<>
struct std::hash<InputAction>
{
	std::size_t operator()(const InputAction& inputAction) const;
};

#endif // !INPUT_ACTION
#pragma once

#include <type_traits>
#include <unordered_set>

#include "InputAction.h"
#include "Command.h"

namespace Minigin
{
    class InputMappingContext
    {
    public:
        InputMappingContext(GameObject* gameObject);
        ~InputMappingContext() = default;

        InputMappingContext(const InputMappingContext&) = delete;
        InputMappingContext(InputMappingContext&&) noexcept = default;
        InputMappingContext& operator= (const InputMappingContext&) = delete;
        InputMappingContext& operator= (const InputMappingContext&&) = delete;

        std::unordered_set<InputAction>& GetInputActions();

        bool operator==(const InputMappingContext& rhs) const;

        template<typename CommandType>
        bool AddInputAction(bool isController, unsigned int button, InputTrigger trigger)
        {
            if constexpr (std::is_base_of<GameObjectCommand, CommandType>::value)
            {
                if (m_LinkedToGameObjet)
                {
                    return m_InputActions.emplace(isController, button, trigger, new CommandType{ m_GameObject }).second;
                }
                else return false;
            }
            else
            {
                if (!m_LinkedToGameObjet)
                {
                    return m_InputActions.emplace(isController, button, trigger, new CommandType()).second;
                }
                else return false;
            }
        }

        friend struct std::hash<InputMappingContext>;

    private:
        GameObject* m_GameObject;
        const bool m_LinkedToGameObjet;
        std::unordered_set<InputAction> m_InputActions;

    };
}

template<>
struct std::hash<Minigin::InputMappingContext>
{
    std::size_t operator()(const Minigin::InputMappingContext& mapping) const;
};
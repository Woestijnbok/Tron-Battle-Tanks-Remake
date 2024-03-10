#include <SDL.h>

#include "InputManager.h"
#include "../3rdParty/imgui-1.90.4/backends/imgui_impl_sdl2.h"

bool InputManager::ProcessInput()
{
	SDL_Event event{};

	while (SDL_PollEvent(&event)) 
	{
		if (event.type == SDL_QUIT) 
		{
			return false;
		}
		ImGui_ImplSDL2_ProcessEvent(&event);
	}

	return true;
}

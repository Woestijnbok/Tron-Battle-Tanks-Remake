#ifndef RENDERER
#define RENDERER

#include <SDL.h>

#include "Singleton.h"

#include "Component.h"

class Texture;
struct ImGuiContext;
struct ImPlotContext;

class Renderer final : public Singleton<Renderer>
{
	
public:

	Renderer() = default;
	~Renderer() = default;

	Renderer(const Renderer&) = delete;
	Renderer(Renderer&&) = delete;
	Renderer& operator= (const Renderer&) = delete;
	Renderer& operator= (const Renderer&&) = delete;

	void Init(SDL_Window* window);
	void Render() const;
	void Destroy();
	void RenderTexture(const Texture& texture, float x, float y) const;
	void RenderTexture(const Texture& texture, float x, float y, float width, float height) const;
	SDL_Renderer* GetSDLRenderer() const;
	const SDL_Color& GetBackgroundColor() const;
	void SetBackgroundColor(const SDL_Color& color);

private:

	SDL_Renderer* m_Renderer;
	SDL_Window* m_Window;
	SDL_Color m_ClearColor;
	ImGuiContext* m_ImGuiContext;
	ImPlotContext* m_ImPlotContext;
};

#endif
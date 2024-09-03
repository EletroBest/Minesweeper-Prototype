#pragma once
#include "SDL.hpp"

class RendererWindow
{
    public:

        static RendererWindow& GetInstance(){static RendererWindow window(WINDOW_NAME,WINDOW_WIDTH,WINDOW_HEIGHT); return window;}
        void Clear();
        void Render();
        void Render(SDL_Rect* rect,SDL_Color* color,RectRenderMode mode);
        void Render(SDL_Surface* surface,Vector2* position, SDL_Color* color);
        void Display();

    private:

        SDL_Window* window;
        SDL_Renderer* renderer;

        RendererWindow(const char* name, int w, int h);
        RendererWindow operator=(RendererWindow&);
        RendererWindow(RendererWindow&);
        ~RendererWindow();
};
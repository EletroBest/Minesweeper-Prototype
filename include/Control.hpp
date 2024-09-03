#pragma once

#include <SDL.hpp>

class Control
{
    public:
        Control(Vector2* position, Vector2* size, SDL_Color* color = new SDL_Color{255,255,255,255},fVector2* anchorPoint = new fVector2{0.5,0.5});
        virtual void Render();

        virtual ~Control();

    protected:
        SDL_Rect* Rect;
        Vector2* Position;
        Vector2* Size;
        SDL_Color* Color;
        fVector2* AnchorPoint;
};
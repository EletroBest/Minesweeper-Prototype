#pragma once

#include "Control.hpp"

class BaseButton:public Control
{
    public:
        BaseButton(Vector2* position, Vector2* size, SDL_Color* color = new SDL_Color{255,255,255,255},fVector2* anchorPoint = new fVector2{0.5,0.5});
        virtual void Render();

        ~BaseButton();

    protected:
        SDL_Color* HandledColor;
        SDL_Color* NormalColor;
        bool Active;
};
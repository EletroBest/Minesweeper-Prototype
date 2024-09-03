#pragma once
#include "BaseButton.hpp"
#include "TextComposition.hpp"

class TextButton: public BaseButton
{
    public:
        TextButton(const char* text="-",Vector2* position = new Vector2{200,500}, Vector2* size = new Vector2{200,200}, SDL_Color* color = new SDL_Color{255,255,255,255},fVector2* anchorPoint = new fVector2{0.5,0.5});
        void Render();

        void SetText(const char* text);

        ~TextButton();

    private:
        TextComposition* Text;
};
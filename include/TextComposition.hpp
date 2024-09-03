#pragma once

#include "SDL.hpp"
#include <SDL2/SDL_ttf.h>

class TextComposition
{
    public:
        TextComposition(const char* text = "-",Vector2* position = new Vector2,int size=13,SDL_Color* color = new SDL_Color{0,0,0,0});
        void Render();

        void SetText(const char* text);

        ~TextComposition();
    private:
        SDL_Surface* Surface;
        TTF_Font* Font;
        std::string Text;
        Vector2* Position;
        int Size;
        SDL_Color* Color;
};
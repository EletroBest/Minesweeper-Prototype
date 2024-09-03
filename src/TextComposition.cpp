#include "TextComposition.hpp"
#include <SDL2/SDL_ttf.h>
#include "RendererWindow.hpp"

TextComposition::TextComposition(const char* text, Vector2* position, int size, SDL_Color* color)
:Text(text),Size(size),Color(color)
{
    TTF_Init();
    Font = TTF_OpenFont("res/fonts/Arial.ttf",size);
    if(!Font) std::cout << "Cannot create Font" << SDL_GetError() << std::endl;
    
    Surface = new SDL_Surface;
    Position = new Vector2{position->x,position->y};
}

void TextComposition::Render()
{
    std::cout << Text;
    Surface = TTF_RenderText_Solid(Font,Text.c_str(),*Color);
    if(!Surface) std::cout << "Cannot create Surface" << SDL_GetError() << std::endl;
    Vector2 position = Vector2{Position->x-(int)(Surface->w*0.5),Position->y-(int)(Surface->h*0.5)};
    if(!Surface) std::cout << "Cannot create Surface: " << SDL_GetError() << std::endl;

    RendererWindow::GetInstance().Render(Surface,&position,Color);
}

void TextComposition::SetText(const char* text)
{
    Text = text;
}

TextComposition::~TextComposition()
{
    std::cout<< "Deletando o text composition";
    delete Surface;
    SDL_FreeSurface(Surface);
    delete Position;
    TTF_CloseFont(Font);
    TTF_Quit();
    delete Color;
}
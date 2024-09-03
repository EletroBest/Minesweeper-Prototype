#include "RendererWindow.hpp"

RendererWindow::RendererWindow(const char* name, int width, int height)
{
    this->window = SDL_CreateWindow(name,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,0);
    this->renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_PRESENTVSYNC);

    if(!this->window || !this->renderer) std::cout << "An error ocurred while creating the Window or Renderer.\n";

}

void RendererWindow::Clear()
{
    SDL_RenderClear(renderer);
}

void RendererWindow::Render()
{
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
}

void RendererWindow::Render(SDL_Rect* rect,SDL_Color* color, RectRenderMode mode)
{
    SDL_SetRenderDrawColor(renderer,color->r,color->g,color->b,color->a);
    
    if(mode == FILL_RECT) SDL_RenderFillRect(renderer,rect);
    else SDL_RenderDrawRect(renderer,rect);
}

void RendererWindow::Render(SDL_Surface* surface, Vector2* position, SDL_Color* color)
{
    SDL_Rect dst{position->x,position->y,surface->w,surface->h};
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
    
    SDL_SetRenderDrawColor(renderer,color->r,color->g,color->b,color->a);
    SDL_RenderCopy(renderer,texture,NULL,&dst);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void RendererWindow::Display()
{

    SDL_RenderPresent(renderer);
}

RendererWindow::~RendererWindow()
{
    std::cout << "Destroying RendererWindow\n";
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}
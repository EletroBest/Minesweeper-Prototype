#include "Control.hpp"
#include "RendererWindow.hpp"


Control::Control(Vector2* position, Vector2* size, SDL_Color* color,fVector2* anchorPoint)
:Size(size),Color(color),AnchorPoint(anchorPoint)
{
    Position = new Vector2{position->x-(int)(Size->x*anchorPoint->x),position->y-(int)(Size->y*anchorPoint->y)};
    Rect = new SDL_Rect{Position->x,Position->y,Size->x,Size->y};
}

void Control::Render()
{
    RendererWindow::GetInstance().Render(Rect,Color,FILL_RECT);
}

Control::~Control()
{
    std::cout << "Deletando o Control";
    delete Position;
    delete Rect;
    delete Size;
    delete AnchorPoint;
}
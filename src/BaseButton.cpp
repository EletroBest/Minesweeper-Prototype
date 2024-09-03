#include "BaseButton.hpp"
#include "Control.hpp"
#include "InputManager.hpp"

BaseButton::BaseButton(Vector2* position, Vector2* size, SDL_Color* color,fVector2* anchorPoint)
:Control(position,size,color,anchorPoint),NormalColor(Color)
{
    HandledColor = new SDL_Color{static_cast<Uint8>(color->r-50),static_cast<Uint8>(color->g-50),static_cast<Uint8>(color->b-50),static_cast<Uint8>(color->a-50)};
}

void BaseButton::Render()
{
    if(InputManager::GetInstance().IsMouseInBounds(Rect)) Color = HandledColor;
    else Color = NormalColor;

    Control::Render();
}

BaseButton::~BaseButton()
{
    delete HandledColor;
}
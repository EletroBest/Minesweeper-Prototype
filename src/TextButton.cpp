#include "TextButton.hpp"

TextButton::TextButton(const char* text,Vector2* position, Vector2* size, SDL_Color* color,fVector2* anchorPoint)
:BaseButton(position,size,color,anchorPoint)
{
    Text = new TextComposition(text,new Vector2{Position->x+(int)(size->x*0.5),Position->y+(int)(size->y*0.5)},30);
}

void TextButton::Render()
{
    BaseButton::Render();
    Text->Render();
}

void TextButton::SetText(const char* text)
{
    Text->SetText(text);
}

TextButton::~TextButton()
{
    delete Text;
}
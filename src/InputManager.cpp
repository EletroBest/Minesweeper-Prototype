#include "InputManager.hpp"

InputManager::InputManager()
{
    MousePosition = new Vector2;
    MouseState = new Uint32;
    PrevMouseState = new Uint32;
}

void InputManager::Update()
{
    *MouseState = SDL_GetMouseState(&MousePosition->x,&MousePosition->y);
}

void InputManager::UpdatePrevState()
{
    *PrevMouseState = SDL_GetMouseState(nullptr,nullptr);
}

bool InputManager::IsMouseButtonPressed(MouseButton button)
{
    return *MouseState == button && *PrevMouseState != button;
}

bool InputManager::IsMouseButtonUp(MouseButton button)
{
    return *MouseState != button && *PrevMouseState == button;
}

bool InputManager::IsMouseInBounds(SDL_Rect* rect)
{
    if(MousePosition->x < rect->x || MousePosition->x > (rect->x+rect->w)) return false;
    if(MousePosition->y < rect->y || MousePosition->y > (rect->y+rect->h)) return false;

    return true;
}

InputManager::~InputManager()
{
    delete MousePosition;
    delete MouseState;
    delete PrevMouseState;
}
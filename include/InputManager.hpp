#pragma once

#include "SDL.hpp"

enum MouseButton
{
    LEFT_BUTTON = 1,
    MIDDLE_BUTTON = 2,
    RIGHT_BUTTON = 4
};

class InputManager
{
    public:
        static InputManager& GetInstance(){static InputManager instance; return instance;}
        void Update();
        void UpdatePrevState();

        bool IsMouseButtonPressed(MouseButton button);
        bool IsMouseButtonUp(MouseButton button);

        bool IsMouseInBounds(SDL_Rect* rect);

    private:

        Uint8* KeyboardState;
        Uint8* PrevKeyboardState;

        Uint32* MouseState;
        Uint32* PrevMouseState;

        Vector2* MousePosition;

        InputManager();
        InputManager(InputManager&);
        InputManager operator=(InputManager&);
        ~InputManager();
};
#pragma once
#include <SDL2/SDL.h>
#include <iostream>

#define WINDOW_NAME "Game"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define ARIAL_PATH "res/fonts/ARIAL.TTF"

typedef void(*vPointer);

enum FontType
{
    ARIAL_FONT
};

enum RectRenderMode
{
    FILL_RECT,
    EMPTY_RECT
};

struct Vector2
{
    int x;
    int y;
};

struct fVector2
{
    float x;
    float y;
};
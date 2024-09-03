#pragma once

#include <SDL.hpp>
#include <vector>
#include "TextButton.hpp"


//AROUND
#define UPPER_LEFT_TILE(X,Y) X-Y-1
#define UPPER_TILE(X,Y) X-Y
#define UPPER_RIGHT_TILE(X,Y) X-Y+1
#define LEFT_TILE(X) X-1
#define RIGHT_TILE(X) X+1
#define LOWER_LEFT_TILE(X,Y) X+Y-1
#define LOWER_TILE(X,Y) X+Y
#define LOWER_RIGHT_TILE(X,Y) X+Y+1

//DEFINITIONS
#define TILE_SIZE 32

class GameMap
{
    public:
        GameMap(int w, int h);
        void CreateBombs(int amount);
        void CreateMap();
        void SetupGame();
        
        int HasBombAround(int tile);
        void Render();

        ~GameMap();

    private:
        Vector2* MapSize;
        std::vector<TextButton*>*Map;
        std::vector<bool>*BombTiles;
        int NumberTiles;
        Vector2* Position;
        Vector2* TileSize;
};
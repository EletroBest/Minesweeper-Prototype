#include "GameMap.hpp"

#include <cstdlib>

GameMap::GameMap(int w, int h)
{

    Map = new std::vector<TextButton*>;

    MapSize = new Vector2{w,h};
    TileSize = new Vector2{TILE_SIZE,TILE_SIZE};
    NumberTiles = w*h;

    BombTiles = new std::vector<bool>;
    BombTiles->resize(NumberTiles);
    std::fill(BombTiles->begin(),BombTiles->end(),false);

    CreateBombs(50);
    CreateMap();
    SetupGame();
}

void GameMap::CreateBombs(int amount)
{

    int randomIndex;
    for(int i=0;i<amount;i++)
    {
        std::cout << randomIndex << "\n";
        do{
            randomIndex = rand()%NumberTiles-1;
        }while(BombTiles->at(randomIndex));

        BombTiles->at(randomIndex) = true;
    }

}

void GameMap::CreateMap()
{
    Vector2 startPosition{-TileSize->x,-TileSize->y};
    Vector2 tilePosition = startPosition;
    int index = 0;

    for(int i=0;i<MapSize->y;i++)
    {
        tilePosition = Vector2{startPosition.x,tilePosition.y+TileSize->y};
        for(int j=0;j<MapSize->x;j++)
        {
            tilePosition.x += TileSize->x;

            TextButton *tile = new TextButton("-",&tilePosition,TileSize);
            Map->push_back(tile);
            index++;
        }
    }
}

void GameMap::SetupGame()
{
    for(int i=0;i<BombTiles->size();i++)
    {
        const char* text;

        int bombsAround = HasBombAround(i);

        std::cout << bombsAround << "\n";

        if(BombTiles->at(i)) text = "O";
        else if(bombsAround){ std::string sText = std::to_string(bombsAround); text = sText.c_str();} // nao sei fazewr uma conversao basica
        else text = "-";

        Map->at(i)->SetText(text);

    }
}

int GameMap::HasBombAround(int tile)
{
    int bombs = 0;

    if((tile-MapSize->y)>=0)
    {
        if((tile-MapSize->y)!=0)if(BombTiles->at(UPPER_LEFT_TILE(tile,MapSize->y))) bombs+=1;
        if(BombTiles->at(UPPER_RIGHT_TILE(tile,MapSize->y))) bombs+=1;
        if(BombTiles->at(UPPER_TILE(tile,MapSize->y))) bombs+=1;
    }

    if((tile+MapSize->y)<NumberTiles)
    {
        if(BombTiles->at(LOWER_LEFT_TILE(tile,MapSize->y))) bombs+=1;
        if(BombTiles->at(LOWER_TILE(tile,MapSize->y))) bombs+=1;
        if((tile+MapSize->y)!=255) if(BombTiles->at(LOWER_RIGHT_TILE(tile,MapSize->y))) bombs+=1;
    }

    if((float)tile/MapSize->y != (int)tile/MapSize->y)
    {
        if(BombTiles->at(LEFT_TILE(tile))) 
        {
            bombs+=1;
            std::cout << "Lado";
            
        }
    }

    if((tile+1)!=(tile-15+16))
        if(BombTiles->at(RIGHT_TILE(tile))) bombs+=1;

    return bombs;
}

void GameMap::Render()
{
    for(auto i:*Map)
    {
        i->Render(); 
    }
}

GameMap::~GameMap()
{
    delete MapSize;
    Map->clear();
    delete Map;

    delete Position;
    delete TileSize;
}
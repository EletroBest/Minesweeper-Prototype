#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <vector>

#define ARIAL_FONT_PATH "res/Fonts/Arial.ttf"

#define BOMB_SPRITE_PATH "res/Sprites/Bomb.png"

struct Vector2
{
    int x=0;
    int y=0;
};

typedef void(*function);

#define TOP_LEFT_TILE(X,Y) X-Y-1
#define TOP_TILE(X,Y) X-Y
#define TOP_RIGHT_TILE(X,Y) X-Y+1

#define LEFT_TILE(X) X - 1
#define RIGHT_TILE(X) X + 1

#define BOTTOM_LEFT_TILE(X,Y) X+Y-1
#define BOTTOM_TILE(X,Y) X+Y
#define BOTTOM_RIGHT_TILE(X,Y) X+Y+1

SDL_Window* window;
SDL_Renderer* renderer;


class Control
{
    public:
        Control(Vector2 position, Vector2* size)
        :Size(size){
            SetPosition(position);
        }

        void SetPosition(Vector2 position)
        {
           // if(Position) delete Position;
            if(Size)
            Position = new Vector2{position.x+(Size->x/2),position.y+(Size->y/2)};
        }

    protected:
        Vector2* Position;
        Vector2* Size;

};


class BackGroundComposition: public Control
{
    public:
    BackGroundComposition(Vector2 position, Vector2* size,bool visible = true,SDL_Color* backgroundColor = new SDL_Color{240,240,240,255},SDL_Color* backgroundBorderColor = new SDL_Color{200,200,200,255})
    :Control(position,size),Visible(visible), BackgroundColor(backgroundColor),BackgroundBorderColor(backgroundBorderColor)
    {
        Background = new SDL_Rect{Position->x,Position->y,Size->x,Size->y};
        BackgroundBorder = Background;
    }

    void Render()
    {

        if(Visible)
        {
            SDL_SetRenderDrawColor(renderer,BackgroundColor->r,BackgroundColor->g,BackgroundColor->b,BackgroundColor->a);
            SDL_RenderFillRect(renderer,Background);
        
            SDL_SetRenderDrawColor(renderer,BackgroundBorderColor->r,BackgroundBorderColor->g,BackgroundBorderColor->b,BackgroundBorderColor->a);
            SDL_RenderDrawRect(renderer,BackgroundBorder);
        }
    }

    private:
        SDL_Rect* Background;
        SDL_Color* BackgroundColor;
        SDL_Rect* BackgroundBorder;
        SDL_Color* BackgroundBorderColor;

        bool Visible;
};

class BaseButton:public Control
{
    public:
        BaseButton(Vector2 position, Vector2* size)
        :Control(position,size){

        }
        virtual void Render()
        {
            
        }
};


class TextureComposition:public Control
{

    public:
        TextureComposition(const char* path,Vector2 position,Vector2* size,bool visible=true)
        :Control(position,size),Visible(visible){

            SDL_Surface* surface = IMG_Load(path);
            Texture = SDL_CreateTextureFromSurface(renderer,surface);
            SDL_FreeSurface(surface);
        }


        void Render()
        {
            if(Visible)
            {
                SDL_Rect rect{Position->x,Position->y,Size->x,Size->y};
                SDL_RenderCopy(renderer,Texture,NULL,&rect);
            }
        }

    private:
        SDL_Texture* Texture;
        bool Visible;
};

class TextComposition:public Control
{
    public:
    TextComposition(std::string text,Vector2 position, bool visible=true,int size =30,SDL_Color* color = new SDL_Color{0,0,0,0})
    :Control(position,NULL),Color(color),Size(size),Visible(visible)
    {
        Font = TTF_OpenFont(ARIAL_FONT_PATH,size);
        Text = new std::string(text) ;
        Surface = TTF_RenderText_Solid(Font,Text->c_str(),*Color);
        Position = new Vector2{position.x-(Surface->w/2),position.y-(Surface->h/2)};
    }

    void Render()
    {

        if(Visible)
        {
            SDL_Texture* texture;
            SDL_Rect rect{Position->x,Position->y,Surface->w,Surface->h};
            texture = SDL_CreateTextureFromSurface(renderer,Surface);
            SDL_RenderCopy(renderer,texture,NULL,&rect);
            SDL_DestroyTexture(texture);
        }
    }

    private:
        std::string* Text;
        SDL_Color* Color;
        int Size;
        TTF_Font* Font;
        SDL_Surface* Surface;
        bool Visible;
};


class TextureButton:public Control
{
    public:

        TextureButton(Vector2 position, Vector2* size)
        :Control(position,size)
        {
            Texture = new TextureComposition(BOMB_SPRITE_PATH,position,size);
        }

    private:
        TextureComposition* Texture;
};

class TextButton:public BaseButton
{
    public:
    TextButton(std::string text,Vector2 position, Vector2* size,SDL_Color* textColor = new SDL_Color{0,0,0,0})
    :BaseButton(position,size)
    {
        Backgroud = new BackGroundComposition(position,size);
        Text = new TextComposition(text,Vector2{position.x+(size->x),position.y+(size->y)},true,30,textColor);
    }

    void Render()
    {
        Backgroud->Render();
        Text->Render();
    }

    private:
        TextComposition* Text;
        BackGroundComposition* Backgroud;
};

class GameMap
{
    public:
        GameMap(int w, int h)
        {
            Buttons = new std::vector<TextButton*>;
            // CORNER DECLARATION
            TopCornerMap = new std::vector<int>;
            BottomCornerMap = new std::vector<int>;
            LeftCornerMap = new std::vector<int>;
            RightCornerMap = new std::vector<int>;

            TotalSize = w*h;
            Size = new Vector2{w,h};
            TileMap = new std::vector<char>;
            TileMap->resize(TotalSize);
            std::fill(TileMap->begin(),TileMap->end(),'-');
            SetCorners();
        
            CreateBombs(30);
            CreateNumbers();
            CreateButtons();
        }

        void SetCorners()
        {
            // SETING TOP CORNER
            for(int i=0;i<Size->x;i++)
                //std::cout << i << " ";
                TopCornerMap->push_back(i);
            
            //SETTING LEFT CORNER
            for(int i=0;i<=Size->y*(Size->y-1);i+=Size->y)
                LeftCornerMap->push_back(i);

            //SETTING RIGHT CORNER
            for(int i=Size->x-1;i<=(TotalSize-1);i+=Size->y)
                RightCornerMap->push_back(i);

            //SETTING BOTTOM CORNER
            for(int i=Size->y*(Size->y-1);i<TotalSize;i++)
                BottomCornerMap->push_back(i);
        }

        bool IsInCorner(int index, std::vector<int>* corner)
        {
            for(auto i = corner->begin(); i!= corner->end();i++)
            {
                if(index == *i) return true;
            }

            return false;
        }

        bool HasBomb(int index)
        {
            if(TileMap->at(index) == 'B') return true;
            return false;
        }

        void CreateBombs(int amount)
        {
            for(int i=0;i<amount;i++)
            {
                int randomIndex;
                do{
                    randomIndex = rand()%TotalSize;
                }while(HasBomb(randomIndex));
                TileMap->at(randomIndex) = 'B';
            }
        }

        void CreateNumbers()
        {
            int bombs;
        
            for(int i=0;i<TotalSize;i++)
            {

                if(!HasBomb(i))
                {
                    bombs=0;
                    if(!IsInCorner(i,TopCornerMap))
                    {
                        if(!IsInCorner(i,LeftCornerMap)){ if(HasBomb(TOP_LEFT_TILE(i,Size->y))) bombs++;}
                        if(HasBomb(TOP_TILE(i,Size->y))) bombs++;
                        if(!IsInCorner(i,RightCornerMap)){ if(HasBomb(TOP_RIGHT_TILE(i,Size->y))) bombs++;}
                    }

                    if(!IsInCorner(i,BottomCornerMap))
                    {
                        if(!IsInCorner(i,LeftCornerMap)) if(HasBomb(BOTTOM_LEFT_TILE(i,Size->y))) bombs++;
                        if(HasBomb(BOTTOM_TILE(i,Size->y))) bombs++;
                        if(!IsInCorner(i,RightCornerMap)){ if(HasBomb(BOTTOM_RIGHT_TILE(i,Size->y))) bombs++;}
                    }

                    if(!IsInCorner(i,LeftCornerMap))
                    {
                        if(HasBomb(LEFT_TILE(i))) bombs++;
                    }

                    if(!IsInCorner(i,RightCornerMap))
                    {
                        if(HasBomb(RIGHT_TILE(i))) bombs++;
                    }

                    if(bombs>0){std::cout << "\n" << i << "\n";TileMap->at(i) = *std::to_string(bombs).c_str();}
                }
     

            }
        }

        void CreateButtons()
        {
            int index = 0;

            std::string _char;

            SDL_Color* textColor;
            Vector2 startPosition{0,0};
            Vector2 position = startPosition;
            Vector2* size = new Vector2{32,32};
            for(int i=0;i<Size->y;i++)
            {
                for(int j=0;j<Size->x;j++)
                {
                    _char = std::string(sizeof(TileMap->at(index)),TileMap->at(index));
                    
                    switch (atoi(_char.c_str()))
                    {
                    case 1:
                        textColor = new SDL_Color{0,0,150};
                        break;
                    
                    case 2:
                        textColor = new SDL_Color{0,150,0};
                        break;
                    case 3:
                        textColor = new SDL_Color{150,0,0};
                        break;
                    default:
                        textColor = new SDL_Color{0,0,0,0};
                        break;
                    }

                    TextButton* button = new TextButton(_char,position,size,textColor);
                    position.x += size->x;
                    Buttons->push_back(button);
                    std::cout << index << " ";
                    index++;
                }
                position = Vector2{startPosition.x,position.y+size->y};
            }
        }

        void Display()
        {
            for(auto i=0;i<TotalSize;i++)
            {
                Buttons->at(i)->Render();
            }
        }


    private:
        int TotalSize;
        std::vector<char>*TileMap;
        std::vector<TextButton*>*Buttons;
        std::vector<int>*TopCornerMap;
        std::vector<int>*RightCornerMap;
        std::vector<int>*LeftCornerMap;
        std::vector<int>*BottomCornerMap;
        Vector2* Size;

};

int main(int argc, char** argv)
{

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    std::cout << std::endl;

    window = SDL_CreateWindow("Minesweeper",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1280,720,0);
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_PRESENTVSYNC);

    GameMap map(16,16);

    bool Running = true;
    SDL_Event event;

    while(Running)
    {
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                Running = false;
                break;
            
            default:
                break;
            }
        }

        SDL_RenderClear(renderer);
        map.Display();
        SDL_SetRenderDrawColor(renderer,255,0,0,0);
        SDL_RenderPresent(renderer);
    }

    TTF_Quit();
    SDL_Quit();

    return 0;
}
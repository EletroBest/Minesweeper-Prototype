#include "RendererWindow.hpp"
#include "InputManager.hpp"
#include "TextButton.hpp"
#include "GameMap.hpp"


//Texto random

void loop()
{
    int Running = true;
    SDL_Event event;

    std::cout << "Running";

    GameMap map(16,16);

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

        InputManager::GetInstance().Update();
        RendererWindow::GetInstance().Clear();
        map.Render();
        RendererWindow::GetInstance().Render();
        RendererWindow::GetInstance().Display();
        InputManager::GetInstance().UpdatePrevState();
    }

}

int main(int argc, char** argv)
{

    SDL_Init(SDL_INIT_VIDEO);
    RendererWindow::GetInstance();
    InputManager::GetInstance();
    loop();
    SDL_Quit();

    return 0;
}
#include <SDL3/SDL.h>
#include <cstdint>
#include <vector>

constexpr Uint32 DELAY = 16;

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Pixel Renderer", WIDTH, HEIGHT, 0);
    
    bool running = true; 
    SDL_Event event; 

    while(running) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_EVENT_QUIT)
                running = false;
        }

        SDL_Delay(DELAY);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;   
}
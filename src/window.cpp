#include "window.hpp"

Window::Window(const char *title, int width, int height) : width(width), height(height)
{
    if(!SDL_Init(SDL_INIT_VIDEO)){
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        running = false;
        return; 
    }

    window = SDL_CreateWindow(title, width, height, 0);
    if(!window){
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        running = false;
        return;
    }
    
    renderer = SDL_CreateRenderer(window, nullptr);
    if(!renderer)
    {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
        running = false;
        return; 
    }

    running = true;
}

Window::~Window()
{
    if(renderer) SDL_DestroyRenderer(renderer);
    if(window) SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::handleEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            running = false;
        }
    }
}

void Window::clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
    SDL_RenderClear(renderer);
}

void Window::drawLine(float x1, float y1, float x2, float y2)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderLine(renderer, x1, y1, x2, y2);
}

void Window::drawTriangle(vec3d vertex1, vec3d vertex2, vec3d vertex3)
{
    drawLine(vertex1.x, vertex1.y, vertex2.x, vertex2.y);
    drawLine(vertex1.x, vertex1.y, vertex3.x, vertex3.y);
    drawLine(vertex2.x, vertex2.y, vertex3.x, vertex3.y);
}

void Window::present()
{
    SDL_RenderPresent(renderer);
}

bool Window::isRunning()
{
    return running;
}
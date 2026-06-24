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

void Window::drawPixel(int x, int y, float brightness)
{
    int shade = brightness * 255;
    SDL_SetRenderDrawColor(renderer, shade, shade, shade, 255);
    SDL_RenderPoint(renderer, x, y);
}

void Window::fillTriangle(vec3d v1, vec3d v2, vec3d v3, float brightness)
{
    auto edge = [](vec3d a, vec3d b, vec3d c)
    {
        return (c.x - a.x) * (b.y - a.y) - 
            (c.y - a.y) * (b.x - a.x);
    };

    int minX = (int)std::min({v1.x, v2.x, v3.x});
    int maxX = (int)std::max({v1.x, v2.x, v3.x});
    int minY = (int)std::min({v1.y, v2.y, v3.y});
    int maxY = (int)std::max({v1.y, v2.y, v3.y});

    for (int y = minY; y <= maxY; y++)
    {
        for (int x = minX; x <= maxX; x++)
        {
            vec3d p = {(float)x, (float)y, 0.0f};

            float w1 = edge(v2, v3, p);
            float w2 = edge(v3, v1, p);
            float w3 = edge(v1, v2, p);

            if ((w1 >= 0 && w2 >= 0 && w3 >= 0) ||
                (w1 <= 0 && w2 <= 0 && w3 <= 0))
            {
                drawPixel(x, y, brightness);
            }
        }
    }
}

void Window::present()
{
    SDL_RenderPresent(renderer);
}

bool Window::isRunning()
{
    return running;
}
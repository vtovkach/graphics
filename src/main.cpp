#include <SDL3/SDL.h>
#include <cstdint>
#include <vector>
#include <iostream>
#include <cmath>

constexpr Uint32 DELAY = 16;

constexpr float WIDTH = 800;
constexpr float HEIGHT = 600;

struct vec3d
{
    float x,y,z;
};

struct triangle
{
    vec3d vertices[3];
};

struct mesh
{
    std::vector<triangle> tris; 
};

struct mat4x4
{
    float m[4][4] = { 0 };
};

class Window
{
private:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    int width; 
    int height;
    bool running = true; 
public:
    Window(const char *title, int width, int height) : width(width), height(height)
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
    }

    ~Window()
    {
        if(renderer) SDL_DestroyRenderer(renderer);
        if(window) SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void handleEvents() {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }
    }

    void clear()
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
        SDL_RenderClear(renderer);
    }

    void drawLine(float x1, float y1, float x2, float y2)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderLine(renderer, x1, y1, x2, y2);
    }

    void drawTriangle(vec3d vertex1, vec3d vertex2, vec3d vertex3)
    {
        drawLine(vertex1.x, vertex1.y, vertex2.x, vertex2.y);
        drawLine(vertex1.x, vertex1.y, vertex3.x, vertex3.y);
        drawLine(vertex2.x, vertex2.y, vertex3.x, vertex3.y);
    }

    void present()
    {
        SDL_RenderPresent(renderer);
    }

    bool isRunning()
    {
        return running;
    }
};

void MultiplyMatrixVector(vec3d &i, vec3d &o, mat4x4 &m)
{
    o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
    o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
    o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
    float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

    if (w != 0.0f)
    {
        o.x /= w; o.y /= w; o.z /= w;
    }
}

int main() {
    Window win("Renderer", WIDTH, HEIGHT);
    mat4x4 matProj, matRotZ, matRotX; 
    mesh meshCube;

    float fTheta = 0; 

    while(win.isRunning()){
        win.handleEvents();
        win.clear();

        // 3D CUBE 
        meshCube.tris = 
        {
            // SOUTH
            { 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
		    { 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

            // EAST                                                      
            { 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
            { 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

            // NORTH                                                     
            { 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
            { 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

            // WEST                                                      
            { 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
            { 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

            // TOP                                                       
            { 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
            { 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

            // BOTTOM                                                    
            { 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
            { 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },
        };

        // Projection Matrix 
        float fNear = 0.1f;
        float fFar = 1000.0f;
        float fFov = 90.0f;
        float fAspectRation = (float)HEIGHT / (float)WIDTH;
        float fFovRad = 1.0f / tanf(fFov * 0.5 / 180.0f * 3.14159f);

        matProj.m[0][0] = fAspectRation * fFovRad;
        matProj.m[1][1] = fFovRad;
        matProj.m[2][2] = fFar / (fFar - fNear);
        matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
        matProj.m[2][3] = 1.0f;
        matProj.m[3][3] = 0.0f;

        fTheta += 1.0f * 0.016; 

        // Rotation Z
		matRotZ.m[0][0] = cosf(fTheta);
		matRotZ.m[0][1] = sinf(fTheta);
		matRotZ.m[1][0] = -sinf(fTheta);
		matRotZ.m[1][1] = cosf(fTheta);
		matRotZ.m[2][2] = 1;
		matRotZ.m[3][3] = 1;

		// Rotation X
		matRotX.m[0][0] = 1;
		matRotX.m[1][1] = cosf(fTheta * 0.5f);
		matRotX.m[1][2] = sinf(fTheta * 0.5f);
		matRotX.m[2][1] = -sinf(fTheta * 0.5f);
		matRotX.m[2][2] = cosf(fTheta * 0.5f);
		matRotX.m[3][3] = 1;

        // Draw Triangles
        for(auto tri : meshCube.tris)
        {
            triangle triProjected, triTranslated, triRotatedZ, triRotatedZX;

            MultiplyMatrixVector(tri.vertices[0], triRotatedZ.vertices[0], matRotZ);
            MultiplyMatrixVector(tri.vertices[1], triRotatedZ.vertices[1], matRotZ);
            MultiplyMatrixVector(tri.vertices[2], triRotatedZ.vertices[2], matRotZ);

            MultiplyMatrixVector(triRotatedZ.vertices[0], triRotatedZX.vertices[0], matRotX);
            MultiplyMatrixVector(triRotatedZ.vertices[1], triRotatedZX.vertices[1], matRotX);
            MultiplyMatrixVector(triRotatedZ.vertices[2], triRotatedZX.vertices[2], matRotX);

            triTranslated = triRotatedZX;
            triTranslated.vertices[0].z = triRotatedZX.vertices[0].z + 3.0f;
            triTranslated.vertices[1].z = triRotatedZX.vertices[1].z + 3.0f;
            triTranslated.vertices[2].z = triRotatedZX.vertices[2].z + 3.0f;

            MultiplyMatrixVector(triTranslated.vertices[0], triProjected.vertices[0], matProj);
            MultiplyMatrixVector(triTranslated.vertices[1], triProjected.vertices[1], matProj);
            MultiplyMatrixVector(triTranslated.vertices[2], triProjected.vertices[2], matProj);

            // Scale into view
            triProjected.vertices[0].x += 1.0f; triProjected.vertices[0].y += 1.0f; 
            triProjected.vertices[1].x += 1.0f; triProjected.vertices[1].y += 1.0f; 
            triProjected.vertices[2].x += 1.0f; triProjected.vertices[2].y += 1.0f; 

            triProjected.vertices[0].x *= 0.5f * (float)WIDTH;
            triProjected.vertices[0].y *= 0.5f * (float)HEIGHT;
            triProjected.vertices[1].x *= 0.5f * (float)WIDTH;
            triProjected.vertices[1].y *= 0.5f * (float)HEIGHT;
            triProjected.vertices[2].x *= 0.5f * (float)WIDTH;
            triProjected.vertices[2].y *= 0.5f * (float)HEIGHT;

            win.drawTriangle(triProjected.vertices[0], triProjected.vertices[1], triProjected.vertices[2]);
        }
 
        win.present();
        SDL_Delay(16);
    }

    return 0;   
}
#include <cstdint>
#include <iostream>
#include <cmath>

#include "math3d.hpp"
#include "window.hpp"

constexpr Uint32 DELAY = 16;
constexpr float WIDTH = 800;
constexpr float HEIGHT = 600;

int main() {
    Window win("Renderer", WIDTH, HEIGHT);
    mat4x4 matProj, matRotZ, matRotX; 
    mesh meshCube;

    vec3d vCamera = {0, 0, 0}; 

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

            // Rotate in Z axis 
            MultiplyMatrixVector(tri.vertices[0], triRotatedZ.vertices[0], matRotZ);
            MultiplyMatrixVector(tri.vertices[1], triRotatedZ.vertices[1], matRotZ);
            MultiplyMatrixVector(tri.vertices[2], triRotatedZ.vertices[2], matRotZ);

            // Rotate in X axis 
            MultiplyMatrixVector(triRotatedZ.vertices[0], triRotatedZX.vertices[0], matRotX);
            MultiplyMatrixVector(triRotatedZ.vertices[1], triRotatedZX.vertices[1], matRotX);
            MultiplyMatrixVector(triRotatedZ.vertices[2], triRotatedZX.vertices[2], matRotX);

            // Offset into the screen
            triTranslated = triRotatedZX;
            triTranslated.vertices[0].z = triRotatedZX.vertices[0].z + 3.0f;
            triTranslated.vertices[1].z = triRotatedZX.vertices[1].z + 3.0f;
            triTranslated.vertices[2].z = triRotatedZX.vertices[2].z + 3.0f;

            vec3d normal, line1, line2;

            line1.x = triTranslated.vertices[1].x - triTranslated.vertices[0].x;
            line1.y = triTranslated.vertices[1].y - triTranslated.vertices[0].y;
            line1.z = triTranslated.vertices[1].z - triTranslated.vertices[0].z;

            line2.x = triTranslated.vertices[2].x - triTranslated.vertices[0].x;
            line2.y = triTranslated.vertices[2].y - triTranslated.vertices[0].y;
            line2.z = triTranslated.vertices[2].z - triTranslated.vertices[0].z;

            CrossProduct(line1, line2, normal);

            float normal_len = sqrtf(
                normal.x * normal.x +
                normal.y * normal.y +
                normal.z * normal.z
            );

            normal.x /= normal_len;
            normal.y /= normal_len;
            normal.z /= normal_len;

            //if(normal.z < 0)
            if(normal.x * (triTranslated.vertices[0].x - vCamera.x) + 
               normal.y * (triTranslated.vertices[0].y - vCamera.y) +
               normal.z * (triTranslated.vertices[0].z - vCamera.z) < 0.0)
            {
                // Project triangles 3D -> 2D
                MultiplyMatrixVector(triTranslated.vertices[0], triProjected.vertices[0], matProj);
                MultiplyMatrixVector(triTranslated.vertices[1], triProjected.vertices[1], matProj);
                MultiplyMatrixVector(triTranslated.vertices[2], triProjected.vertices[2], matProj);

                // Normalize coordinates [-1, 1] -> [WIDTH, HEIGHT]
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
        }
 
        win.present();
        SDL_Delay(16);
    }

    return 0;   
}
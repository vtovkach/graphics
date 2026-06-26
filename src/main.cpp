#include <cstdint>
#include <iostream>
#include <cmath>
#include <algorithm>

#include "math3d.hpp"
#include "window.hpp"
#include "mesh.hpp"

constexpr Uint32 DELAY = 16;
constexpr float WIDTH = 800;
constexpr float HEIGHT = 600;

struct trianglesToDraw
{
    triangle tri;
    float brightness; 
};

int main() {
    Window win("Renderer", WIDTH, HEIGHT);

    mat4x4 matProj = {0};
    mat4x4 matRotZ = {0}; 
    mat4x4 matRotX = {0}; 

    mesh meshCube;

    vec3d vCamera = {0, 0, 0}; 

    float fTheta = 0;

    meshCube.LoadFromObjFile("res/VideoShip.obj");

    while(win.isRunning()){
        win.handleEvents();
        win.clear();

        /*
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
        */
        
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

        std::vector<trianglesToDraw> vecTriangleToRaster; 

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
            triTranslated.vertices[0].z = triRotatedZX.vertices[0].z + 8.0f;
            triTranslated.vertices[1].z = triRotatedZX.vertices[1].z + 8.0f;
            triTranslated.vertices[2].z = triRotatedZX.vertices[2].z + 8.0f;

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
                vec3d light_direction = {0.0f, 0.0f, -1.0f}; 
                float light_mag = sqrtf((light_direction.x * light_direction.x) + 
                                        (light_direction.y * light_direction.y) + 
                                        (light_direction.z * light_direction.z));
                light_direction.x /= light_mag;
                light_direction.y /= light_mag;
                light_direction.z /= light_mag;

                float brightness =  (light_direction.x * normal.x) + 
                                    (light_direction.y * normal.y) + 
                                    (light_direction.z * normal.z);
                if(brightness > 1.0f) brightness = 1.0f;
                if(brightness < 0.0f) brightness = 0.0f; 

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

                trianglesToDraw triToDraw; 
                triToDraw.tri = triProjected;
                triToDraw.brightness = brightness;

                vecTriangleToRaster.push_back(triToDraw);
            }
        }

        // Sort triangles from back to front
        sort(vecTriangleToRaster.begin(), vecTriangleToRaster.end(), [](trianglesToDraw &t1, trianglesToDraw &t2)
        {
            triangle tri1 = t1.tri;
            triangle tri2 = t2.tri;

            float z1 = (tri1.vertices[0].z + tri1.vertices[1].z + tri1.vertices[2].z) / 3.0f; 
            float z2 = (tri2.vertices[0].z + tri2.vertices[1].z + tri2.vertices[2].z) / 3.0f;
            
            return z1 > z2;
        });

        for(auto &triProjected : vecTriangleToRaster)
        {
            // Rasterize triangle 
            win.fillTriangle(triProjected.tri.vertices[0], triProjected.tri.vertices[1], triProjected.tri.vertices[2], triProjected.brightness);
        }


        win.present();
        SDL_Delay(16);
    }

    return 0;   
}
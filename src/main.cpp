#include <iostream>
#include "raylib.h"

int main(int argc, char *argv[])
{
    const int WIDTH = 1280;
    const int HEIGHT = 720;


    InitWindow(WIDTH, HEIGHT, "prj deserted");

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText("PRJ DESERTED", WIDTH/2, HEIGHT/2, 20,RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
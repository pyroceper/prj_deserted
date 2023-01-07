#include "game.h"

Game::Game()
{
    InitWindow(WIDTH, HEIGHT, TITLE.c_str());
    SetTargetFPS(FPS);
}

void Game::run()
{
    while(!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText(TITLE.c_str(), WIDTH/2, HEIGHT/2, 20, RAYWHITE);
        EndDrawing();
    }
}


Game::~Game()
{
    CloseWindow();
}


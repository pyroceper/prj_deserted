#include "game.h"

Game::Game()
{
    InitWindow(WIDTH, HEIGHT, TITLE.c_str());
    SetTargetFPS(FPS);
    player.x = WIDTH/2;
    player.y = HEIGHT/2;
}

void Game::run()
{
    while(!WindowShouldClose())
    {
        //input
        if(IsKeyDown(KEY_RIGHT)) player.x++;
        if(IsKeyDown(KEY_LEFT)) player.x--;
        if(IsKeyDown(KEY_UP)) player.y--;
        if(IsKeyDown(KEY_DOWN)) player.y++;

        //render
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText(TITLE.c_str(), WIDTH/2, HEIGHT/2, 20, RAYWHITE);
            DrawRectangle(player.x, player.y, 32, 16, RED);
        EndDrawing();
    }
}


Game::~Game()
{
    CloseWindow();
}


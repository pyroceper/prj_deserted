#include "game.h"

Game::Game()
{
    InitWindow(WIDTH, HEIGHT, TITLE.c_str());
    SetTargetFPS(FPS);
    Player::rec.x = (WIDTH/2) - 20;
    Player::rec.y = HEIGHT/2;

    testGround.x = 0;
    testGround.y = 500;
    testGround.width = 630;
    testGround.height = 20;
}

void Game::run()
{
    while(!WindowShouldClose())
    {
        //input
        if(IsKeyDown(KEY_RIGHT)) Player::rec.x++;
        if(IsKeyDown(KEY_LEFT)) Player::rec.x--;
        if(IsKeyDown(KEY_UP) && Player::on_floor) Player::is_jump = true;

        //logic
        if(Player::is_jump)
        {
            Player::rec.y -= 1.0f * Player::jump_height * GetFrameTime();
            Player::jump_height -= 10.0f;
        }

        if(!Player::on_floor && Player::is_jump)
        {
            Player::rec.y += Player::GRAVITY * GetFrameTime();
        }

        if(!Player::on_floor && !Player::is_jump)
        {
            Player::rec.y += Player::fall_speed * Player::GRAVITY * GetFrameTime();
            Player::fall_speed += 0.2f;
        }

        if(Collision::AABB(Player::rec, testGround))
        {
            Player::on_floor = true;
            Player::jump_height = Player::JUMP_HEIGHT;
            Player::is_jump = false;
            Player::fall_speed = 0.0f;
        }
        else 
            Player::on_floor = false;        

        //render
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText(TITLE.c_str(), WIDTH/2, HEIGHT/2, 20, RAYWHITE);
            DrawRectangle(Player::rec.x, Player::rec.y, 32, 16, RED);
            DrawRectangle(testGround.x, testGround.y, testGround.width, testGround.height, GREEN);
        EndDrawing();
    }
}


Game::~Game()
{
    CloseWindow();
}


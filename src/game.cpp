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

    bgLayer1 = LoadTexture("../assets/gfx/background_layer_1.png");
    bgLayer2 = LoadTexture("../assets/gfx/background_layer_2.png");
    bgLayer3 = LoadTexture("../assets/gfx/background_layer_3.png");

    block = LoadTexture("../assets/gfx/block.png");

    loadLevel();
}

void Game::loadLevel()
{
    FILE *level = fopen("../assets/levels/level0.txt", "r");

    for(int i=0;i<30;i++)
    {
        for(int j=0;j<30;j++)
        {
            fscanf(level, "%d", &map[i][j]);
        }
    }
}


void Game::run()
{
    while(!WindowShouldClose())
    {
        //input
        if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) Player::rec.x += 1.0f * Player::speed * GetFrameTime();
        if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))  Player::rec.x -= 1.0f * Player::speed * GetFrameTime();
        if((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && Player::on_floor) Player::is_jump = true;

        //logic
        Cam::followTarget((int)Player::rec.x, (int)Player::rec.y, 740, 740);
        offsetX = static_cast<int>(Cam::offset.x);
        offsetY = static_cast<int>(Cam::offset.y);

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
            DrawTextureEx(bgLayer1, {0, 0}, 0.0f, SCALE, WHITE);
            DrawTextureEx(bgLayer2, {0, 0}, 0.0f, SCALE, WHITE);
            DrawTextureEx(bgLayer3, {0, 0}, 0.0f, SCALE, WHITE);
            for(int i=0;i<30;i++)
            {
                for(int j=0;j<30;j++)
                {
                    if(map[i][j])
                        DrawTexture(block, (j * 32) - offsetX, (i * 32) - offsetY, WHITE);
                }
            }


            DrawRectangle(Player::rec.x - offsetX, Player::rec.y - offsetY, 32, 32, RED);
            DrawRectangle(testGround.x - offsetX, testGround.y - offsetY, testGround.width, testGround.height, GREEN);
        EndDrawing();
    }
}


Game::~Game()
{
    UnloadTexture(bgLayer1);
    UnloadTexture(bgLayer2);
    UnloadTexture(bgLayer3);
    UnloadTexture(block);
    CloseWindow();
}


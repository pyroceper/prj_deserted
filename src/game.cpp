#include "game.h"

Game::Game()
{
    InitWindow(WIDTH, HEIGHT, TITLE.c_str());
    SetTargetFPS(FPS);

    testGround.x = 0;
    testGround.y = 500;
    testGround.width = 630;
    testGround.height = 20;

    bgLayer1 = LoadTexture("../assets/gfx/background_layer_1.png");
    bgLayer2 = LoadTexture("../assets/gfx/background_layer_2.png");
    bgLayer3 = LoadTexture("../assets/gfx/background_layer_3.png");

    block = LoadTexture("../assets/gfx/block.png");

    Player::left = Player::right = Player::top = Player::bottom = false;

    loadLevel("../assets/levels/level0.txt");
}

void Game::loadLevel(const std::string fileName)
{
    FILE *level = fopen(fileName.c_str(), "r");
    float x, y, w, h;
    int numOfCollisionBoxes;


    for(int i=0;i<30;i++)
    {
        for(int j=0;j<30;j++)
        {
            fscanf(level, "%d", &map[i][j]);
        }
    }
    fscanf(level, "%f %f", &Player::rec.x, &Player::rec.y);
    fscanf(level, "%d", &numOfCollisionBoxes);
    for(int i=0;i<numOfCollisionBoxes;i++)
    {
        fscanf(level, "%f %f %f %f", &x, &y, &w, &h);
        collisionBoxes.push_back({x, y, w, h});
    }
}

void Game::inputHandler()
{
    if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) Player::rec.x += 1.0f * Player::speed * GetFrameTime();
    if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))  Player::rec.x -= 1.0f * Player::speed * GetFrameTime();
    if((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && Player::on_floor) Player::is_jump = true;
}

void Game::collisionHandler()
{
    for(int i=0;i<collisionBoxes.size();i++)
    {
        if(Collision::AABB(Player::rec, collisionBoxes[i]))
        {
            Player::collision_side = Collision::getCollisionSide(Player::rec, collisionBoxes[i]);
            if(Player::collision_side == Collision::Side::BOTTOM)
            {
                Player::bottom = true;
                Player::collision_array[0] = Collision::getBottom(Player::rec) - Collision::getTop(collisionBoxes[i]);
            }
            if(Player::collision_side == Collision::Side::RIGHT)
            {
                Player::right = true;
                Player::collision_array[1] = Collision::getRight(Player::rec) - Collision::getLeft(collisionBoxes[i]);
            }
            if(Player::collision_side == Collision::Side::LEFT)
            {
                Player::left = true;
                Player::collision_array[2] = Collision::getRight(collisionBoxes[i]) - Collision::getLeft(Player::rec);
            }
            if(Player::collision_side == Collision::Side::TOP)
            {
                Player::top = true;
                Player::collision_array[3] = Collision::getBottom(collisionBoxes[i]) - Collision::getTop(Player::rec);
            }
        }                          
    }
        
    if(!Player::bottom)
    {
        Player::on_floor = false;
    }
    if(Player::bottom)
    {
        Player::rec.y -= Player::collision_array[0];
        Player::on_floor = true;
        Player::jump_height = Player::JUMP_HEIGHT;
        Player::is_jump = false;
        Player::fall_speed = 0.0f;
        Player::bottom = false;
    }
    if(Player::left)
    {
        Player::rec.x += Player::collision_array[2];
        Player::left = false;
    }
}

void Game::camera()
{
    Cam::followTarget(Player::rec.x, Player::rec.y, 740, 740);
    offsetX = static_cast<int>(Cam::offset.x);
    offsetY = static_cast<int>(Cam::offset.y);
}

void Game::playerMovement()
{
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
}

void Game::render()
{
    BeginDrawing();
        ClearBackground(BLACK);
        DrawTextureEx(bgLayer1, bgLayer1Pos, 0.0f, SCALE, WHITE);
        DrawTextureEx(bgLayer2, bgLayer2Pos, 0.0f, SCALE, WHITE);
        DrawTextureEx(bgLayer3, bgLayer3Pos, 0.0f, SCALE, WHITE);
        for(int i=0;i<30;i++)
        {
            for(int j=0;j<30;j++)
            {
                if(map[i][j])
                    DrawTexture(block, (j * 32) - offsetX, (i * 32) - offsetY, WHITE);
            }
        }
        //debug
        // for(int i=0;i<collisionBoxes.size();i++)
        // {
        //     DrawRectangle(collisionBoxes[i].x - offsetX, collisionBoxes[i].y - offsetY, collisionBoxes[i].width, collisionBoxes[i].height, GREEN);
        // }
        DrawRectangle(Player::rec.x - offsetX, Player::rec.y - offsetY, 32, 32, RED);

        DrawText(debug, WIDTH/2, HEIGHT/2, 20, RAYWHITE);
    EndDrawing();
}

void Game::run()
{
    while(!WindowShouldClose())
    {
        //input
        inputHandler();

        //logic
        camera();
        playerMovement();
        collisionHandler();
  
        //debug
        sprintf(debug, "diff = %f", Player::collision_array[0]);
  
        //render
        render();
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


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

    block[0] = LoadTexture("../assets/gfx/block.png");
    block[1] = LoadTexture("../assets/gfx/block_plain.png");
    block[2] = LoadTexture("../assets/gfx/block_grass.png");

    Player::left = Player::right = Player::top = Player::bottom = false;

    loadLevel("../assets/levels/level0.txt");
}

void Game::loadLevel(const std::string fileName)
{
    FILE *level = fopen(fileName.c_str(), "r");
    float x, y, w, h;
    int numOfCollisionBoxes;


    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<COLS;j++)
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
    if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) 
    {
        Player::rec.x += 1.0f * Player::speed * GetFrameTime();
        if(!Player::right && offsetX != 0 && offsetX < 640)
        {
            bgLayer1Pos.x -= 2.0f * GetFrameTime();
            bgLayer2Pos.x -= 5.0f * GetFrameTime();
            bgLayer3Pos.x -= 15.0f * GetFrameTime();
        }
    }
    if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) 
    {
         Player::rec.x -= 1.0f * Player::speed * GetFrameTime();
         if(!Player::left && offsetX != 0 && offsetX < 640)
         {
            bgLayer1Pos.x += 2.0f * GetFrameTime();
            bgLayer2Pos.x += 5.0f * GetFrameTime();
            bgLayer3Pos.x += 15.0f * GetFrameTime();
         }
    }
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
    if(Player::right)
    {
        Player::rec.x -= Player::collision_array[1];
        Player::right = false;
    }
}

void Game::camera()
{
    Cam::followTarget(Player::rec.x, Player::rec.y, 740, 740);
    offsetX = static_cast<int>(Cam::offset.x);
    offsetY = static_cast<int>(Cam::offset.y);
    offsetY -= 250;
    if(offsetX > 640)
        offsetX = 640;
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
        for(int i=0;i<ROWS;i++)
        {
            for(int j=0;j<COLS;j++)
            {
                switch(map[i][j])
                {
                    case 0: break;
                    case 2:
                        DrawTexture(block[2], (j * 32) - offsetX, (i * 32) - offsetY, WHITE);
                        break;
                    case 6:
                        DrawTexture(block[0], (j * 32) - offsetX, (i * 32) - offsetY, WHITE);
                        break;
                    
                    case 17:
                        DrawTexture(block[1], (j * 32) - offsetX, (i * 32) - offsetY, WHITE);
                        break;

                    default:
                        DrawRectangle((j * 32) - offsetX, (i * 32) - offsetY, 32, 32, ORANGE);
                }
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
        sprintf(debug, "x = %f, y = %f; x = %f, y = %f", Player::rec.x, Player::rec.y, Cam::offset.x, Cam::offset.y);
  
        //render
        render();
    }
}


Game::~Game()
{
    UnloadTexture(bgLayer1);
    UnloadTexture(bgLayer2);
    UnloadTexture(bgLayer3);
    UnloadTexture(block[0]);
    UnloadTexture(block[1]);
    UnloadTexture(block[2]);
    CloseWindow();
}


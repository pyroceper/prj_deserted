#include "game.h"

Game::Game()
{
    InitWindow(WIDTH, HEIGHT, TITLE.c_str());
    InitAudioDevice();
    #if defined(PLATFORM_DESKTOP)
        SetTargetFPS(FPS);
    #endif

    for(int i=0;i<50;i++)
    {
        Enemy::is_active[i] = false;
        Enemy::rect[i].width = Enemy::rect[i].height = 32;
        FlipBox::rect[i].width = FlipBox::rect[i].height = 32;
        Enemy::is_dead[i] = false;
    }

    title = LoadTexture("assets/gfx/title.png");
    tx_menu = LoadTexture("assets/gfx/menu.png");

    bgLayer1 = LoadTexture("assets/gfx/background_layer_1.png");
    bgLayer2 = LoadTexture("assets/gfx/background_layer_2.png");
    bgLayer3 = LoadTexture("assets/gfx/background_layer_3.png");

    block[0] = LoadTexture("assets/gfx/block.png");
    block[1] = LoadTexture("assets/gfx/block_plain.png");
    block[2] = LoadTexture("assets/gfx/block_grass.png");

    lamp = LoadTexture("assets/gfx/lamp.png");

    kitty[0] = LoadTexture("assets/gfx/kitty/idle_1/kitty_idle1.png");
    kitty[1] = LoadTexture("assets/gfx/kitty/idle_1/kitty_idle2.png");
    kitty[2] = LoadTexture("assets/gfx/kitty/idle_1/kitty_idle3.png");
    kitty[3] = LoadTexture("assets/gfx/kitty/idle_1/kitty_idle4.png");

    kitty_walk[0] = LoadTexture("assets/gfx/kitty/walk/kitty_walk1.png");
    kitty_walk[1] = LoadTexture("assets/gfx/kitty/walk/kitty_walk2.png");
    kitty_walk[2] = LoadTexture("assets/gfx/kitty/walk/kitty_walk3.png");
    kitty_walk[3] = LoadTexture("assets/gfx/kitty/walk/kitty_walk4.png");
    kitty_walk[4] = LoadTexture("assets/gfx/kitty/walk/kitty_walk5.png");
    kitty_walk[5] = LoadTexture("assets/gfx/kitty/walk/kitty_walk6.png");
    kitty_walk[6] = LoadTexture("assets/gfx/kitty/walk/kitty_walk7.png");
    kitty_walk[7] = LoadTexture("assets/gfx/kitty/walk/kitty_walk8.png");

    kitty_attack[0] = LoadTexture("assets/gfx/kitty/attack/kitty_attack1.png");
    kitty_attack[1] = LoadTexture("assets/gfx/kitty/attack/kitty_attack2.png");
    kitty_attack[2] = LoadTexture("assets/gfx/kitty/attack/kitty_attack3.png");
    kitty_attack[3] = LoadTexture("assets/gfx/kitty/attack/kitty_attack4.png");
    kitty_attack[4] = LoadTexture("assets/gfx/kitty/attack/kitty_attack5.png");
    kitty_attack[5] = LoadTexture("assets/gfx/kitty/attack/kitty_attack6.png");

    kitty_ui = LoadTexture("assets/gfx/kitty/kitty_face.png");

    enemy_orange[0] = LoadTexture("assets/gfx/enemies/orange/orange1.png");
    enemy_orange[1] = LoadTexture("assets/gfx/enemies/orange/orange2.png");
    enemy_orange[2] = LoadTexture("assets/gfx/enemies/orange/orange3.png");
    enemy_orange[3] = LoadTexture("assets/gfx/enemies/orange/orange4.png");
    enemy_orange[4] = LoadTexture("assets/gfx/enemies/orange/orange5.png");
    enemy_orange[5] = LoadTexture("assets/gfx/enemies/orange/orange6.png");

    enemy_orange_hurt = LoadTexture("assets/gfx/enemies/orange/hurt.png");

    fx_hurt = LoadSound("assets/sfx/hurt.wav");
    fx_pickup = LoadSound("assets/sfx/pickup.wav");
    fx_jump = LoadSound("assets/sfx/jump.wav");

    bg_music = LoadMusicStream("assets/sfx/Forest.mp3");

    PlayMusicStream(bg_music);

    current_kitty = &kitty[0];
    current_kitty_walk = &kitty_walk[0];
    current_kitty_attack = &kitty_attack[0];

    current_enemy_orange = &enemy_orange[0];

    fish_pickup = LoadTexture("assets/gfx/fish.png");
    

    Player::left = Player::right = Player::top = Player::bottom = false;

}

#if defined(PLATFORM_WEB)
void webRun(Game &game)
{
    switch(game.state)
    {
        case 0:
                game.menu();
                break;
        case 1:
                game.level0();
                break;
    }
}
#endif

void Game::loadLevel(const std::string fileName)
{
    FILE *level = fopen(fileName.c_str(), "r");
    float x, y, w, h;
    int numOfCollisionBoxes;
    int numOfEnemies;
    int n;
    int r, c;

    fscanf(level, "%d %d", &c, &r);
    rows = r;
    cols = c;
    printf("[debug] rows = %d, cols = %d\n", rows, cols);

    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            fscanf(level, "%d", &map[i][j]);
        }
    }
    printf("[debug] loading level done!\n");
    fscanf(level, "%f %f", &Player::rec.x, &Player::rec.y);
    player_spawn_point.x = Player::rec.x;
    player_spawn_point.y = Player::rec.y;
    //for debug player 
    player_debug.x = player_spawn_point.x;
    player_debug.y = player_spawn_point.y;
    fscanf(level, "%d", &numOfCollisionBoxes);
    for(int i=0;i<numOfCollisionBoxes;i++)
    {
        fscanf(level, "%f %f %f %f", &x, &y, &w, &h);
        collisionBoxes.push_back({x, y, w, h});
    }
    // fscanf(level, "%d", &numOfEnemies);
    // for(int i=0;i<numOfEnemies;i++)
    // {
    //     fscanf(level, "%f %f %d", &x, &y, &n);
    //     Enemy::rect[i].x = x;
    //     Enemy::rect[i].y = y;
    //     Enemy::is_active[i] = true;
    //     Enemy::is_left[i] = -1;
    //     if(n == 1)
    //         Enemy::type[i] = Enemy::Type::PATROL;
    //     num_of_active_enemies++;
    // }
    // fscanf(level, "%d", &n);
    // for(int i=0;i<n;i++)
    // {
    //     fscanf(level, "%f %f", &x, &y);
    //     FlipBox::rect[i].x = x;
    //     FlipBox::rect[i].y = y;
    //     num_of_flip_boxes++;
    // }
    // fscanf(level, "%d", &n);
    // for(int i=0;i<n;i++)
    // {
    //     fscanf(level, "%f %f", &x, &y);
    //     Pickup::rect[i].x = x;
    //     Pickup::rect[i].y = y;
    //     Pickup::rect[i].width = Pickup::rect[i].height = 32;
    //     Pickup::is_active[i] = true;
    //     num_of_pickups++;
    // }

    fclose(level);
}

void Game::levelPrintDebug()
{
    FILE *level = fopen("assets/levels/debug.txt", "w");
    fprintf(level, "%d %d\n", rows, cols);
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            fprintf(level, "%d ", map[i][j]);
        }
        fprintf(level, "\n");
    }    
    fclose(level);
}

void Game::inputHandler()
{
    Player::is_running = false;
    if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) 
    {
        Player::rec.x += 1.0f * Player::speed * GetFrameTime();
        // if(!Player::right && offsetX != 0 && offsetX < 640)
        // {
        //     bgLayer1Pos.x -= 2.0f * GetFrameTime();
        //     bgLayer2Pos.x -= 5.0f * GetFrameTime();
        //     bgLayer3Pos.x -= 15.0f * GetFrameTime();
        // }
        Player::is_running = true;
        Player::is_left = 1;
    }
    if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) 
    {
         Player::rec.x -= 1.0f * Player::speed * GetFrameTime();
        //  if(!Player::left && offsetX != 0 && offsetX < 640)
        //  {
        //     bgLayer1Pos.x += 2.0f * GetFrameTime();
        //     bgLayer2Pos.x += 5.0f * GetFrameTime();
        //     bgLayer3Pos.x += 15.0f * GetFrameTime();
        //  }
        Player::is_running = true;
        Player::is_left = -1;
    }
    if((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && Player::on_floor) 
    {
        Player::is_jump = true;
        PlaySound(fx_jump);
    }
    if(IsKeyDown(KEY_SPACE))
        Player::is_attack = true;
}

void Game::inputDebug()
{
    if(IsKeyDown(KEY_LEFT))
        player_debug.x -= 1.0f * Player::speed * GetFrameTime();
    if(IsKeyDown(KEY_RIGHT))
        player_debug.x += 1.0f * Player::speed * GetFrameTime();
    if(IsKeyDown(KEY_DOWN))
        player_debug.y += 1.0f * Player::speed * GetFrameTime();
    if(IsKeyDown(KEY_UP))
        player_debug.y -= 1.0f * Player::speed * GetFrameTime();
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

    //ono almost out of time ;-;

    for(int i=0;i<num_of_pickups;i++)
    {
        if(Collision::AABB(Player::rec, Pickup::rect[i]) && Pickup::is_active[i] && i == 3)
        {
            state = 0; // hack  ;-; 
        }
        if(Collision::AABB(Player::rec, Pickup::rect[i]) && Pickup::is_active[i])
        {
            PlaySound(fx_pickup);
            lives++;
        }
        if(Collision::AABB(Player::rec, Pickup::rect[i]))
        {
            Pickup::is_active[i] = false;
        }

    }

}

void Game::camera()
{
    Cam::followTarget(Player::rec.x, Player::rec.y, 740, 740);
    offsetX = static_cast<int>(Cam::offset.x);
    offsetY = static_cast<int>(Cam::offset.y);
    offsetY -= 270;
    // if(offsetX > 640)
    //     offsetX = 640;
}

void Game::cameraDebug()
{
    Cam::followTarget(player_debug.x, player_debug.y, 740, 740);
    offsetX = static_cast<int>(Cam::offset.x);
    offsetY = static_cast<int>(Cam::offset.y);
    offsetY -= 270;
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

    if(Player::rec.x < 0)
        Player::rec.x = 0;
    // if(Player::rec.x > 1880.f)
    //     Player::rec.x = 1880.f;

    if(lives < 0)
        state = 0;
}

void Game::playerAnimation()
{
    Player::animation_idle_tick += 1.0f * GetFrameTime();
    Player::animation_walk_tick += 1.0f * GetFrameTime();
    Player::animation_attack_tick += 1.0f * GetFrameTime();
    if(Player::animation_idle_tick > 0.2f)
    {
        Player::animation_idle_tick = 0.f;
        if(current_kitty == &kitty[0])
        {
            current_kitty = &kitty[1];
            return;
        }
        if(current_kitty == &kitty[1])
        {
            current_kitty = &kitty[2];
            return;
        }
        if(current_kitty == &kitty[2])
        {
            current_kitty = &kitty[3];
            return;
        }
        if(current_kitty == &kitty[3])
        {
            current_kitty = &kitty[0];
            return;
        }
    }
    if(Player::animation_walk_tick > 0.1f)
    {
        Player::animation_walk_tick = 0.f;
        if(current_kitty_walk == &kitty_walk[0])
        {
            current_kitty_walk = &kitty_walk[1];
            return;
        }
        if(current_kitty_walk == &kitty_walk[1])
        {
            current_kitty_walk = &kitty_walk[2];
            return;
        }
        if(current_kitty_walk == &kitty_walk[2])
        {
            current_kitty_walk = &kitty_walk[3];
            return;
        }
        if(current_kitty_walk == &kitty_walk[3])
        {
            current_kitty_walk = &kitty_walk[4];
            return;
        }
        if(current_kitty_walk == &kitty_walk[4])
        {
            current_kitty_walk = &kitty_walk[5];
            return;
        }
        if(current_kitty_walk == &kitty_walk[5])
        {
            current_kitty_walk = &kitty_walk[6];
            return;
        }
        if(current_kitty_walk == &kitty_walk[6])
        {
            current_kitty_walk = &kitty_walk[7];
            return;
        }
        if(current_kitty_walk == &kitty_walk[7])
        {
            current_kitty_walk = &kitty_walk[0];
            return;
        }
    }

    if(Player::animation_attack_tick > 0.15f)
    {
        Player::animation_attack_tick = 0.f;
        if(current_kitty_attack == &kitty_attack[0])
        {
            current_kitty_attack = &kitty_attack[1];
            return;
        }
        if(current_kitty_attack == &kitty_attack[1])
        {
            current_kitty_attack = &kitty_attack[2];
            return;
        }
        if(current_kitty_attack == &kitty_attack[2])
        {
            current_kitty_attack = &kitty_attack[3];
            return;
        }
        if(current_kitty_attack == &kitty_attack[3])
        {
            current_kitty_attack = &kitty_attack[4];
            return;
        }
        if(current_kitty_attack == &kitty_attack[4])
        {
            current_kitty_attack = &kitty_attack[5];
            return;
        }
        if(current_kitty_attack == &kitty_attack[5])
        {
            Player::is_attack = false;
            current_kitty_attack = &kitty_attack[0];
            return;
        }   
    }

}

void Game::enemyThink(int index)
{
    if(Enemy::type[index] == Enemy::Type::PATROL)
    {
        if(Enemy::is_left[index] == -1)
            Enemy::rect[index].x -= 30.0f * GetFrameTime();
        else 
            Enemy::rect[index].x += 30.0f * GetFrameTime();
    }
}

void Game::enemyCollisionHandler(int index)
{
    for(int i=0;i<num_of_flip_boxes;i++)
    {
        if(Collision::AABB(Enemy::rect[index], FlipBox::rect[i]))
        {
            if(Enemy::is_left[index] == 1)
                Enemy::is_left[index] = -1;
            else 
                Enemy::is_left[index] = 1;
        }
    }
    if(Enemy::is_active[index] && Collision::AABB(Player::rec, Enemy::rect[index]) && Player::is_attack)
    {
        Player::collision_side = Collision::getCollisionSide(Player::rec, Enemy::rect[index]);
        if(Player::collision_side == Collision::Side::RIGHT || Player::collision_side == Collision::Side::LEFT)
        {
            Enemy::is_active[index] = false;
            Enemy::is_dead[index] = true;
            PlaySound(fx_hurt);
        }
    }
    else if(Enemy::is_active[index] && Collision::AABB(Player::rec, Enemy::rect[index]) && !Player::is_attack)
    {
        Player::rec.x = player_spawn_point.x;
        Player::rec.y = player_spawn_point.y;
        PlaySound(fx_hurt);
        lives--;
    }
    
}

void Game::enemyHandler()
{
    for(int i=0;i<num_of_active_enemies;i++)
    {
        if(Enemy::is_active[i])
        {
            enemyThink(i);
            enemyCollisionHandler(i);
            enemyAnimation(i);
        }
        else if(!Enemy::is_active[i] && Enemy::is_dead)
        {
            Enemy::death_timer[i] += 1.0f * GetFrameTime();
            if(Enemy::death_timer[i] > 0.1f)
            { 
                Enemy::death_timer[i] = 1.0f;
            }
        }
    }
}

void Game::enemyAnimation(int index)
{
    Enemy::animation_tick[index] += 1.0f * GetFrameTime();
    if(Enemy::animation_tick[index] > 0.2f)
    {
        Enemy::animation_tick[index] = 0.f;
        if(current_enemy_orange == &enemy_orange[0])
        {
            current_enemy_orange = &enemy_orange[1];
            return;
        }
        if(current_enemy_orange == &enemy_orange[1])
        {
            current_enemy_orange = &enemy_orange[2];
            return;
        }
        if(current_enemy_orange == &enemy_orange[2])
        {
            current_enemy_orange = &enemy_orange[3];
            return;
        }
        if(current_enemy_orange == &enemy_orange[3])
        {
            current_enemy_orange = &enemy_orange[4];
            return;
        }
        if(current_enemy_orange == &enemy_orange[4])
        {
            current_enemy_orange = &enemy_orange[5];
            return;
        }
        if(current_enemy_orange == &enemy_orange[5])
        {
            current_enemy_orange = &enemy_orange[0];
            return;
        }
        if(current_enemy_orange == &enemy_orange[6])
        {
            current_enemy_orange = &enemy_orange[0];
            return;
        }    
    }

}

void Game::render()
{
    BeginDrawing();
        ClearBackground(BLACK);
        DrawTextureEx(bgLayer1, bgLayer1Pos, 0.0f, SCALE, WHITE);
        DrawTextureEx(bgLayer2, bgLayer2Pos, 0.0f, SCALE, WHITE);
        DrawTextureEx(bgLayer3, bgLayer3Pos, 0.0f, SCALE, WHITE);
        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<cols;j++)
            {
                switch(map[i][j])
                {
                    case 0: break;
                    case 2:
                        DrawTexture(block[2], (j * 32) - offsetX, (i * 32) - offsetY, WHITE);
                        break;
                    case 1:
                    case 166:
                    case 167:
                    case 168:
                    case 6:
                        DrawTexture(block[0], (j * 32) - offsetX, (i * 32) - offsetY, WHITE);
                        break;
                    
                    case 17:
                        DrawTexture(block[1], (j * 32) - offsetX, (i * 32) - offsetY, WHITE);
                        break;

                    default:
                        DrawRectangle((j * 32) - offsetX, (i * 32) - offsetY, 32, 32, GREEN);
                }
            }
        }
        DrawTextureEx(lamp, {128.0f - offsetX, 1682.0f - offsetY}, 0.0f, 2.5f, WHITE);
        //debug
        // for(int i=0;i<collisionBoxes.size();i++)
        // {
        //     DrawRectangle(collisionBoxes[i].x - offsetX, collisionBoxes[i].y - offsetY, collisionBoxes[i].width, collisionBoxes[i].height, GREEN);
        // }
        //DrawRectangle(Player::rec.x - offsetX, Player::rec.y - offsetY, 32, 32, RED);
        for(int i=0;i<num_of_pickups;i++)
        {
            if(Pickup::is_active[i])
                DrawTextureEx(fish_pickup, {Pickup::rect[i].x - offsetX, Pickup::rect[i].y - offsetY}, 0.0f, 1.45f, WHITE);
        }
        if(!Player::is_running && !Player::is_jump && !Player::is_attack)
            DrawTexturePro(*current_kitty, (Rectangle){0, 0, static_cast<float>(16 * Player::is_left), 16}, (Rectangle){Player::rec.x - offsetX - 10, Player::rec.y - offsetY - 32, 16 * 3, 16 * 3}, {0,0}, 0.f, WHITE);
        else if(Player::is_jump || Player::fall_speed)
            DrawTexturePro(kitty_walk[5], (Rectangle){0, 0, static_cast<float>(16 * Player::is_left), 16}, (Rectangle){Player::rec.x - offsetX - 10, Player::rec.y - offsetY - 32, 16 * 3, 16 * 3}, {0,0}, 0.f, WHITE);
        else if(!Player::is_running && !Player::is_jump && Player::is_attack)
            DrawTexturePro(*current_kitty_attack, (Rectangle){0, 0, static_cast<float>(16 * Player::is_left), 16}, (Rectangle){Player::rec.x - offsetX - 10, Player::rec.y - offsetY - 32, 16 * 3, 16 * 3}, {0,0}, 0.f, WHITE);
        else 
            DrawTexturePro(*current_kitty_walk, (Rectangle){0, 0, static_cast<float>(16 * Player::is_left), 16}, (Rectangle){Player::rec.x - offsetX - 10, Player::rec.y - offsetY - 32, 16 * 3, 16 * 3}, {0,0}, 0.f, WHITE);

        for(int i=0;i<num_of_active_enemies;i++)
        {
            //DrawRectangle(Enemy::rect[i].x - offsetX, Enemy::rect[i].y - offsetY, 32, 32, RED);
            // DrawTexture(enemy_orange[0], Enemy::rect[i].x - offsetX, Enemy::rect[i].y - offsetY, WHITE);
            if(Enemy::is_active[i])
                DrawTexturePro(*current_enemy_orange, (Rectangle){0, 0, static_cast<float>(32 * Enemy::is_left[i]), 32}, (Rectangle){Enemy::rect[i].x - offsetX, Enemy::rect[i].y - offsetY - 32, 64, 64}, {0,0}, 0.f, WHITE);
            else if(Enemy::is_dead[i] && Enemy::death_timer[i] < 1.0f)
                DrawTexturePro(enemy_orange_hurt, (Rectangle){0, 0, static_cast<float>(32 * Enemy::is_left[i]), 32}, (Rectangle){Enemy::rect[i].x - offsetX, Enemy::rect[i].y - offsetY - 32, 64, 64}, {0,0}, 0.f, WHITE);
 
        }
        DrawTextureEx(kitty_ui, {0.f, 0.f}, 0.0f, 5.0f, WHITE);

        //debug
        // DrawRectangle(FlipBox::rect[0].x - offsetX, FlipBox::rect[0].y - offsetY, 32, 32, ORANGE);
        // DrawRectangle(FlipBox::rect[1].x - offsetX, FlipBox::rect[1].y - offsetY, 32, 32, ORANGE);
        // DrawRectangle(FlipBox::rect[2].x - offsetX, FlipBox::rect[2].y - offsetY, 32, 32, ORANGE);
        DrawText(debug, 72, 25, 40, GRAY);
    EndDrawing();
}

void Game::menu()
{
    //input
    if(IsKeyDown(KEY_DOWN) && menu_cursor_pos.y == 420)
    {
        menu_cursor_pos.y = 530;
        PlaySound(fx_pickup);
    }
    if(IsKeyDown(KEY_UP) && menu_cursor_pos.y == 530)
    {
        menu_cursor_pos.y = 420;
        PlaySound(fx_pickup);
    }
    if(IsKeyDown(KEY_SPACE) && menu_cursor_pos.y == 420)
    {
        lives = 1;
        loadLevel("assets/levels/level1.txt");
        levelPrintDebug();
        state = 1;
    }
    if(IsKeyDown(KEY_SPACE) && menu_cursor_pos.y == 530)
    {
        #if defined(PLATFORM_DESKTOP)
            clean();
            exit(0);
        #endif
    }

    
    //render
    BeginDrawing();
        ClearBackground(BLACK);
        DrawTextureEx(bgLayer1, bgLayer1Pos, 0.0f, SCALE, WHITE);
        DrawTextureEx(bgLayer2, bgLayer2Pos, 0.0f, SCALE, WHITE);
        DrawTextureEx(bgLayer3, bgLayer3Pos, 0.0f, SCALE, WHITE);
        DrawTextureEx(title, {(1280/2) - 50, 20}, 0.0f, SCALE, WHITE);
        DrawTextureEx(kitty_ui, {(1280/2) - 130, 200}, 10.0f, 10.0f, WHITE);
        DrawTextureEx(tx_menu, {500, 220}, 0.0f, SCALE, WHITE);
        DrawTextureEx(fish_pickup, menu_cursor_pos, 0.0f, 3.0f, WHITE);
    EndDrawing();
}

void Game::renderTest()
{
        BeginDrawing();
            ClearBackground(RAYWHITE);
            for(int y=0;y<rows;y++)
            {
                for(int x=0;x<cols;x++)
                {
                    if(map[y][x] == 2)
                        //DrawRectangle(x * 32, y * 32, 32, 32, YELLOW);
                        DrawTexture(block[2], (x * 32) - offsetX, (y * 32) - offsetY, WHITE);
                    if(map[y][x] == 17)
                        DrawTexture(block[1], (x * 32) - offsetX, (y * 32) - offsetY, WHITE);
                }
            }
            DrawRectangle(player_debug.x - offsetX, player_debug.y - offsetY, 32, 32, RED);
            //DrawText("working", 0, 0, 20, YELLOW);
            for(int i=0;i<collisionBoxes.size();i++)
            {
                DrawRectangle(collisionBoxes[i].x - offsetX, collisionBoxes[i].y - offsetY, collisionBoxes[i].width, collisionBoxes[i].height, GREEN);
            }
        EndDrawing();
}

void Game::level0()
{
    //input
    inputHandler();
    //inputDebug();

    //music
    UpdateMusicStream(bg_music);

    //logic
    camera();
    //cameraDebug();
    playerMovement();
    collisionHandler();
    playerAnimation();
    //enemyHandler();
  
    //debug
    //sprintf(debug, "x %d", lives);
  
    //render
    render();
    //renderTest();
}

void Game::run()
{
    while(!WindowShouldClose())
    {
        switch(state)
        {
            case 0:
                    menu();
                    break;
            case 1:
                    level0();
                    break;
        }

    }
}

void Game::clean()
{
    current_kitty = current_kitty_walk = current_kitty_attack = nullptr;
    current_enemy_orange = nullptr;
    UnloadTexture(title);
    UnloadTexture(tx_menu);
    UnloadTexture(bgLayer1);
    UnloadTexture(bgLayer2);
    UnloadTexture(bgLayer3);
    UnloadTexture(block[0]);
    UnloadTexture(block[1]);
    UnloadTexture(block[2]);
    UnloadTexture(lamp);
    UnloadTexture(kitty_ui);
    for(int i=0;i<4;i++)
    {
        UnloadTexture(kitty[i]);
    }
    for(int i=0;i<8;i++)
    {
        UnloadTexture(kitty_walk[i]);
    }
    for(int i=0;i<6;i++)
    {
        UnloadTexture(enemy_orange[i]);
    }
    UnloadTexture(enemy_orange_hurt);
    UnloadTexture(fish_pickup);
    UnloadSound(fx_hurt);
    UnloadSound(fx_pickup);
    UnloadSound(fx_jump);
    UnloadMusicStream(bg_music);
    CloseAudioDevice();
    CloseWindow();
}


Game::~Game()
{
    clean();
}


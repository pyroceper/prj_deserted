#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>
#include <cstdio>
#include <vector>
#include "raylib.h"
#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif
#include "collision.h"
#include "player.h"
#include "enemy.h"
#include "flip_box.h"
#include "camera.h"
#include "pickup.h"

const int ROWS = 120;
const int COLS = 120;

class Game
{
    public:
        Game();
        void run();
        #if defined(PLATFORM_WEB)
            friend void webRun(Game &game);
        #endif
        ~Game();
    private:
        const int WIDTH = 1280;
        const int HEIGHT = 720;
        const std::string TITLE = "Abandoned";
        const int FPS = 60;
        const float SCALE = 4.1f;
        int offsetX = 0;
        int offsetY = 0;

        int map[ROWS][COLS] = {0};
        int rows = 0;
        int cols = 0;

        std::vector<Rectangle> collisionBoxes;
        int num_of_active_enemies = 0;
        int num_of_flip_boxes = 0;
        int num_of_pickups = 0;

        char debug[250] = {0};

        int lives = 1;
        int state = 0;

        Texture2D title;
        Texture2D tx_menu;

        Texture2D block[3];
        Texture2D lamp;
        Texture2D bgLayer1;
        Texture2D bgLayer2;
        Texture2D bgLayer3;

        Texture2D kitty_ui;

        Texture2D kitty_idle;
        int kitty_idle_index = 0;

        Texture2D kitty_attack;
        int kitty_attack_index = 0;

        Texture2D kitty_walk;
        int kitty_walk_index = 0;

        Texture2D enemy_orange_walk;
        int enemy_orange_walk_index = 0;
        Texture2D enemy_orange_hurt;

        Texture2D enemy_rat_walk;
        int enemy_rat_walk_index = 0;

        Texture2D enemy_rat_attack;
        int enemy_rat_attack_index = 0;

        Texture2D fish_pickup;

        Vector2 bgLayer1Pos {0, 0};
        Vector2 bgLayer2Pos {0, 0};
        Vector2 bgLayer3Pos {0, 0};

        Vector2 player_spawn_point {0,0};
        Vector2 menu_cursor_pos {620, 420};

        Sound fx_hurt;
        Sound fx_pickup;
        Sound fx_jump;

        Music bg_music;

        void loadLevel(const std::string fileName);
        void inputHandler();
        void collisionHandler();
        void camera();
        void playerMovement();
        void playerAnimation();
        void enemyHandler();
        void enemyThink(int index);
        void enemyCollisionHandler(int index);
        void enemyAnimation(int index);
        void render();

        //debug
        Vector2 player_debug {0.f, 0.f};
        void inputDebug();
        void renderTest();
        void cameraDebug();
        void levelPrintDebug();

        void menu();
        void level0();
        void clean();

};

#if defined(PLATFORM_WEB)
    void webRun(Game &game);
#endif


#endif
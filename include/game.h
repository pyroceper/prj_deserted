#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>
#include <cstdio>
#include <vector>
#include "raylib.h"
#include "collision.h"
#include "player.h"
#include "enemy.h"
#include "flip_box.h"
#include "camera.h"

const int ROWS = 60;
const int COLS = 60;

class Game
{
    public:
        Game();
        void run();
        ~Game();
    private:
        const int WIDTH = 1280;
        const int HEIGHT = 720;
        const std::string TITLE = "PRJ DESERTED";
        const int FPS = 60;
        const float SCALE = 4.1f;
        int offsetX = 0;
        int offsetY = 0;

        int map[ROWS][COLS] = {0};

        std::vector<Rectangle> collisionBoxes;
        int num_of_active_enemies = 0;
        int num_of_flip_boxes = 0;

        char debug[250] = {0};

        Texture2D block[3];
        Texture2D lamp;
        Texture2D bgLayer1;
        Texture2D bgLayer2;
        Texture2D bgLayer3;

        Texture2D kitty[5];
        Texture2D kitty_walk[8];

        Texture2D *current_kitty = nullptr;
        Texture2D *current_kitty_walk = nullptr;

        Vector2 bgLayer1Pos {0, 0};
        Vector2 bgLayer2Pos {0, 0};
        Vector2 bgLayer3Pos {0, 0};

        void loadLevel(const std::string fileName);
        void inputHandler();
        void collisionHandler();
        void camera();
        void playerMovement();
        void playerAnimation();
        void enemyHandler();
        void enemyThink(int index);
        void enemyCollisionHandler(int index);
        void render();

};


#endif
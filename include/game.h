#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>
#include <vector>
#include "raylib.h"
#include "collision.h"
#include "player.h"
#include "camera.h"

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
        const float SCALE = 4.0f;
        int offsetX = 0;
        int offsetY = 0;

        int map[30][30] = {0};

        std::vector<Rectangle> collisionBoxes;
        int numOfCollisionBoxes = 0;

        Rectangle testGround;

        Texture2D block;

        Texture2D bgLayer1;
        Texture2D bgLayer2;
        Texture2D bgLayer3;

        Vector2 bgLayer1Pos {0, 0};
        Vector2 bgLayer2Pos {0, 0};
        Vector2 bgLayer3Pos {0, 0};

        void loadLevel(const std::string fileName);

};


#endif
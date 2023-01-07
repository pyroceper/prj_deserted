#ifndef GAME_H
#define GAME_H

#include <string>
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

        Rectangle testGround;

        Texture2D bgLayer1;
        Texture2D bgLayer2;
        Texture2D bgLayer3;

};


#endif
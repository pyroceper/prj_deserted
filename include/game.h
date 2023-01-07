#ifndef GAME_H
#define GAME_H

#include <string>
#include "raylib.h"
#include "collision.h"
#include "player.h"

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

        Rectangle testGround;

};


#endif
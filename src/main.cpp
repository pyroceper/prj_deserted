#include <iostream>
#include "game.h"
#include "web.h"

int main(int argc, char *argv[])
{
    #if defined(PLATFORM_DESKTOP)
        Game game;
        game.run();
    #elif defined(PLATFORM_WEB)
        emscripten_set_main_loop(bootstrap, 0, 1);
    #endif
    return 0;
}
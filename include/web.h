#ifndef WEB_H
#define WEB_H

#if defined(PLATFORM_WEB)
    #include "game.h"
    Game game;
    void bootstrap(void)
    {
        webRun(game);
    }
#endif


#endif
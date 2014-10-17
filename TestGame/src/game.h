#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <Engine.h>
#include "Entities/player.h"

class Game {
public:
   Engine e;
   void run();
private:
   void init();
   void gameLoop();
   void quit();

   void update();
   void render();
};

#endif // GAME_H_INCLUDED

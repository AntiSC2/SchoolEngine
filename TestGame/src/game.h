#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <Engine.h>
#include "Entities/player.h"

class Game {
public:
   Game();
   ~Game();
   Engine e;
   void run();
private:
   void init();
   void gameLoop();
   void quit();

   void update();
   void render();
   Player *player;
};

#endif // GAME_H_INCLUDED

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <Engine.h>
#include "Entities/player.h"
#include "Entities/bullet.h"
#include <vector>

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
      std::vector<Bullet> bullets;
      unsigned int countBullets;
};

#endif // GAME_H_INCLUDED

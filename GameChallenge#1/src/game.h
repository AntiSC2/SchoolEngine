#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#ifndef GLEW_BUILD
#define GLEW_BUILD
#endif // GLEW_BUILD
#include <GL/glew.h>
#include <Engine.h>
#include <fstream>
#include <string>
#include "Entities/entity.h"
#include "Level/level.h"
#include "Entities/player.h"

class Player;

class Game {
public:
   Game();
   ~Game();

   void run();

   static Engine e;

private:
   void init();
   void loadLevel(const char* filePath, Level& a);
   void gameLoop();
   void update();
   void drawGame();

   Player* player;
   Level level;
};

#endif // GAME_H_INCLUDED

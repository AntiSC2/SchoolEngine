#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#ifndef GLEW_BUILD
#define GLEW_BUILD
#endif // GLEW_BUILD
#include <GL/glew.h>
#include <Engine.h>
#include <fstream>
#include <string>
#include "Level/level.h"

class SpriteFont;

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
   SpriteFont* _spriteFont;
   Level level;
};

#endif // GAME_H_INCLUDED

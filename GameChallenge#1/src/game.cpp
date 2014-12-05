#include "game.h"
#include <Graphics/vertex.h>
#include <Graphics/spritefont.h>
#include <glm/glm.hpp>
#include <exception>

Game::Game() {
   ;
}

Game::~Game() {
   ;
}

Engine Game::e;

void Game::run() {
   init();
   gameLoop();
}

void Game::init() {
   e.initSubSystems();
   e.initScreen(1280, 720 , "GameChallenge#1");
   e.initShaders("resources/shaders/Vertex.vert", "resources/shaders/Fragment.frag");
   e.initResources("resources/data/Game.data");
   loadLevel("resources/data/Level.data", level);

}

void Game::loadLevel(const char* filePath, Level& a) {
   std::ifstream fin(filePath);
   a.clearLevel();
   if(fin.is_open()) {
      std::string fileLine = "";
      unsigned int c = 0;
      unsigned int x = 0, y = 0;
      unsigned int temp;
      fin >> fileLine >> temp;
      a.setHumans(temp);

      while(std::getline(fin, fileLine)) {
         if(c == 0) {
            a.setWidth(fileLine.size());
            x = fileLine.size();
         }

         if(fileLine.size() == x)
            a.addBlocks(fileLine);
         y++;
      }
      a.setHeight(y);
      a.finishLevel(e.camera);
   }
}

void Game::gameLoop() {
   const double dt = 16.66666666666;
   double currentTime = SDL_GetTicks();
   double newTime;
   double frameTime;
   double accumelator = 0.0;

   unsigned int updates = 0;
   unsigned int frames = 0;
   unsigned int seconds = 0;
   try {
      _spriteFont = new SpriteFont("resources/fonts/chintzy.ttf", 64, 32, 126);
   }
   catch(std::exception &e) {
      printf("%s", e.what());
   }

   while(!e.input->windowClosed()) {
      newTime = SDL_GetTicks();
      frameTime = newTime - currentTime;
      currentTime = newTime;
      accumelator += frameTime;

      while(accumelator >= dt) {
         update();
         updates++;
         accumelator -= dt;
      }

      drawGame();
      frames++;
      if(SDL_GetTicks() - seconds > 1000) {
         printf("Updates: %d\nFrames: %d\nMouse X: %d\nMouse Y: %d\n", updates, frames, Input::getMouseX(e.camera), Input::getMouseY(e.camera));
         updates = 0;
         frames = 0;
         seconds = SDL_GetTicks();
      }
   }
   _spriteFont->dispose();
   delete _spriteFont;
}

void Game::update() {
   e.input->update();
   if(Input::keyPressed(SDL_SCANCODE_R))
      loadLevel("resources/data/Level.data", level);
   level.update();
   e.camera->update();
}

void Game::drawGame() {
   glActiveTexture(GL_TEXTURE0);
   e.screen->render();
   e.shaders[0]->setCameraMatrix(e.camera->getCameraMatrix());
   e.TheBatch->begin();
   _spriteFont->draw(e.TheBatch, "What is love\nWhat are you doing mate", glm::vec2(3500, -1000), glm::vec2(2, 2), 0.0f, Color(255, 255, 255, 255));
   level.render(e.TheBatch);
   e.TheBatch->end();
   e.TheBatch->renderDraw();
   e.screen->update();
}



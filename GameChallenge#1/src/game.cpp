#include "game.h"

Game::Game() {
   ;
}

Game::~Game() {
   delete player;
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
   player = new Player(level);
}

void Game::loadLevel(const char* filePath, Level& a) {
   std::ifstream fin(filePath);
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
}

void Game::update() {
   e.input->update();
   player->update();
   level.update();
   e.camera->update();
}

void Game::drawGame() {
   glActiveTexture(GL_TEXTURE0);
   e.screen->render();
   e.shaders[0]->setCameraMatrix(e.camera->getCameraMatrix());
   e.TheBatch->begin();
   player->render(e.TheBatch);
   level.render(e.TheBatch);
   e.TheBatch->end();
   e.TheBatch->renderDraw();
   e.screen->update();
}



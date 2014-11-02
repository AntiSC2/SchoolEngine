#include "game.h"

Game::Game() : player(nullptr), countBullets(0) {
   ;
}

Game::~Game() {
   delete player;
   /*for(int i = 0; i < bullets.size(); i++) {
      delete bullets[i];
   }*/
}

void Game::run() {
   init();
   gameLoop();
   //quit();
}

void Game::init() {
   e.initSubSystems();
   e.initScreen(1280, 720, "Test Game");
   e.initResources("resources/data/Game.data");
   e.initShaders("resources/shaders/Vertex.vert", "resources/shaders/Fragment.frag");
   e.initLevels("resources/data/Level.data");

   player = new Player;
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

      render();
      frames++;
      if(SDL_GetTicks() - seconds > 1000) {
         printf("Updates: %d\nFrames: %d\n", updates, frames);
         updates = 0;
         frames = 0;
         seconds = SDL_GetTicks();
      }
   }
}

void Game::update() {
   e.input->update();
   const float scale_speed = 0.01f;
   const float speed = 7.5f;

   if(e.input->keyPressed(SDL_SCANCODE_Q)) {
      e.camera->setScale(e.camera->getScale() + scale_speed);
   }

   if(e.input->keyPressed(SDL_SCANCODE_E)) {
      e.camera->setScale(e.camera->getScale() - scale_speed);
   }

   if(e.input->keyPressed(SDL_SCANCODE_A)) {
      e.camera->setPosition(e.camera->getPosition() + glm::vec2(-speed, 0.0f));
   }

   if(e.input->keyPressed(SDL_SCANCODE_D)) {
      e.camera->setPosition(e.camera->getPosition() + glm::vec2(speed, 0.0f));
   }

   if(e.input->keyPressed(SDL_SCANCODE_W)) {
      e.camera->setPosition(e.camera->getPosition() + glm::vec2(0.0f, speed));
   }

   if(e.input->keyPressed(SDL_SCANCODE_S)) {
      e.camera->setPosition(e.camera->getPosition() + glm::vec2(0.0f, -speed));
   }
   if(e.input->keyTyped(SDL_SCANCODE_R)) {
      e.initShaders("resources/shaders/Vertex.vert", "resources/shaders/Fragment.frag");
   }
   e.camera->update();
   for(int i = 0; i < bullets.size();) {
      bullets[i].update();
      if(bullets[i].lifeTime == 0) {
         bullets[i] = bullets.back();
         bullets.pop_back();
         countBullets--;
      } else {
         i++;
      }
   }
   player->update();
   if(player->createBullet) {
      player->createBullet = false;
      countBullets++;
      bullets.emplace_back(player->getPosition().x, player->getPosition().y, Input::getMouseX(e.camera), Input::getMouseY(e.camera), 240);
   }
}

void Game::render() {
   e.screen->render();
   e.shaders[0]->setCameraMatrix(e.camera->getCameraMatrix());
   e.TheBatch->begin();

   for(int i = 0; i < bullets.size(); i++) {
      bullets[i].render(e.TheBatch);
   }
   player->render(e.TheBatch);

   e.TheBatch->end();

   e.TheBatch->renderDraw();
   e.screen->update();
}










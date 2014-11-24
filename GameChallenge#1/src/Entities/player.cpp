#include "player.h"
#include "game.h"

Player::Player(int x, int y, Level& a) : speed(4.0f) {
   destRect.x = x;
   destRect.y = y;
   destRect.z = 48;
   destRect.w = 48;
   targetE = nullptr;
   createBullet = false;
   frames = 0;

   sprite.initSprite(destRect.x, destRect.y, destRect.z, destRect.w, 0, 0, 255, 255, "resources/textures/circle.png");
   this->a = &a;
}


Player::~Player() {
   ;
}

void Player::init(int x, int y) {
   destRect.x = x;
   destRect.y = y;
   sprite.updatePosition(destRect.x, destRect.y);
}

void Player::update() {
   targetE = a->getEntity(destRect);
   if(Input::keyPressed(SDL_SCANCODE_W)) {
      destRect.y += speed;
   }
   if(Input::keyPressed(SDL_SCANCODE_S)) {
      destRect.y -= speed;
   }
   if(Input::keyPressed(SDL_SCANCODE_A)) {
      destRect.x -= speed;
   }
   if(Input::keyPressed(SDL_SCANCODE_D)) {
      destRect.x += speed;
   }
   if(Input::getMouseButton() == 1) {
      if(createBullet == false) {
         createBullet = true;
         a->addBullet(destRect);
      }
   }
   a->checkWalls(destRect);
   if(createBullet == true) {
      if(frames == 15) {
         frames = 0;
         createBullet = false;
      }
      frames++;
   }
   sprite.updatePosition(destRect.x, destRect.y + 16);
   glm::vec2 temp;
   temp.x = destRect.x + 24;
   temp.y = destRect.y + 40;
   Game::e.camera->setPosition(temp);
}

void Player::render(SpriteBatch* batch) {
   sprite.render(batch);
}

int Player::getID() {
   return 1;
}

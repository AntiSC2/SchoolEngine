#include "zombie.h"

Zombie::Zombie(int x, int y, Level& a) {
   destRect.x = x;
   destRect.y = y;
   destRect.z = 48;
   destRect.w = 48;

   target.x = 0.0f;
   target.y = 0.0f;

   speed = 3.0f;
   targetP = nullptr;

   sprite.initSprite(destRect.x, destRect.y, destRect.z, destRect.w, 50, 255, 50, 255, "resources/textures/circle.png");
   this->a = &a;
}

Zombie::~Zombie() {
   ;
}

void Zombie::update() {
   targetP = a->getClosestHuman(destRect);
   if(targetP != nullptr) {
      target = glm::vec2(targetP->getPosition().x, targetP->getPosition().y);
      //printf("ZOMBIE TARGET X: %f\nZOMBIE TARGET Y: %f\n", target.x, target.y);
      target -= glm::vec2(destRect.x, destRect.y);
      target = glm::normalize(target);
   }

   destRect += glm::vec4(target.x, target.y, 0, 0) * speed;
   a->checkWalls(destRect);
   sprite.updatePosition(destRect.x, destRect.y + 16);
}

void Zombie::render(SpriteBatch *batch) {
   sprite.render(batch);
}

int Zombie::getID() {
   return 3;
}

#include "human.h"
#include <glm/gtx/rotate_vector.hpp>

Human::Human(int x, int y, Level& a) {
   destRect.x = x;
   destRect.y = y;
   destRect.z = 48;
   destRect.w = 48;
   frames = 0;
   targetE = nullptr;
   speed = 4.0f;
   this->a = &a;
   direction.x = rand() % this->a->getWidth() * 64;
   direction.y = rand() % this->a->getHeight() * 64;
   direction.y = -direction.y;
   direction = glm::normalize(direction);
   sprite.initSprite(destRect.x, destRect.y, destRect.z, destRect.w, 200, 200, 200, 255, "resources/textures/circle.png");

}

Human::~Human() {
   ;
}

void Human::update() {
   targetE = a->getEntity(destRect);
   if(frames == 320) {
      frames = 0;
      float degrees = rand() % 30;
      if(rand() % 100 < 50) {
         degrees = -(degrees);
      }
      direction = glm::rotate(direction, degrees);
   }

   destRect += glm::vec4(direction.x, direction.y, 0, 0) * speed;
   checkEntityCollision(targetE);
   if(a->checkWalls(destRect)) {
      float degrees = rand() % 40;
      if(rand() % 100 < 50) {
         degrees = -(degrees);
      }
      direction = glm::rotate(direction, degrees);
   }
   sprite.updatePosition(destRect.x, destRect.y + 16);
   frames++;
}

void Human::render(SpriteBatch *batch) {
   sprite.render(batch);
}

int Human::getID() {
   return 2;
}

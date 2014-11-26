#include "bullet.h"

Bullet::Bullet(int x, int y, glm::vec2 direction) {
   destRect.z = 16;
   destRect.w = 16;

   destRect.x = x;
   destRect.y = y - 48;

   sprite.initSprite(destRect.x, destRect.y, destRect.z, destRect.w, 100, 100, 100, 255, "resources/textures/circle.png");
   speed = 8.0f;
   this->direction = direction - glm::vec2(destRect.x, destRect.y + 48);
   this->direction = glm::normalize(this->direction);
}

void Bullet::update() {
   destRect += glm::vec4(direction.x, direction.y, 0, 0) * speed;
   sprite.updatePosition(destRect.x, destRect.y + 48);
}

void Bullet::render(SpriteBatch *batch) {
   sprite.render(batch);
}

glm::vec4& Bullet::getPosition() {
   return destRect;
}

bool Bullet::checkEntityCollision(Entity* a) {
      if(a == nullptr)
         return false;
      float RADIUS1 = a->getPosition().w / 2;
      float RADIUS2 = destRect.w;
      float depth = std::sqrt(std::pow(destRect.x - a->getPosition().x, 2) + std::pow(destRect.y + 16 - a->getPosition().y, 2));
      if(depth < (RADIUS1 + RADIUS2)) {
         return true;
      }
      return false;
}

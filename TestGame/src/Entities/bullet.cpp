#include "bullet.h"

Bullet::Bullet(int x, int y, int dirX, int dirY, int lifeTime) {
   position.x = x;
   position.y = y;

   direction.x = dirX - position.x;
   direction.y = dirY - position.y;

   this->lifeTime = lifeTime;

   sprite = new Sprite;
   sprite->initSprite(position.x, position.y, 32, 32, 255, 255, 255, 255, "resources/textures/bullet.png");

   direction = glm::normalize(direction);
   speed = 1.0f;
}

Bullet::~Bullet() {
   delete sprite;
}

void Bullet::render(SpriteBatch *batch) {
   sprite->render(batch);
}

void Bullet::update() {
   if(lifeTime > 0) {
      lifeTime--;
      position += direction * speed;
      sprite->updatePosition(position.x, position.y);
   }
}

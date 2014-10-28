#include "bullet.h"

Bullet::Bullet(int x, int y, int dirX, int dirY, int lifeTime) {
   position.x = x;
   position.y = y;
   bounding_box.x = x - 16;
   bounding_box.y = y - 16;
   bounding_box.z = 32;
   bounding_box.w = 32;

   direction.x = dirX - position.x;
   direction.y = dirY - position.y;

   this->lifeTime = lifeTime;

   sprite = new Sprite;
   sprite->initSprite(position.x - 16, position.y - 16, 32, 32, 255, 255, 255, 255, "resources/textures/bullet.png");

   direction = glm::normalize(direction);
   speed = 6.0f;
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
      bounding_box.x = position.x - 16;
      bounding_box.y = position.y - 16;
      sprite->updatePosition(bounding_box.x, bounding_box.y);
   }
}

#include "player.h"

Player::Player() {
   position.x = 0;
   position.y = 0;
   bounding_box.x = position.x - 64;
   bounding_box.y = position.y - 64;
   bounding_box.z = 128;
   bounding_box.w = 128;
   sprite = new Sprite;
   sprite->initSprite(bounding_box.x, bounding_box.y, bounding_box.z, bounding_box.w , 255, 255, 255, 255, "resources/textures/player.png");
   createBullet = false;
}

Player::~Player() {
   delete sprite;
}

void Player::render(SpriteBatch *batch) {
   sprite->render(batch);
}

void Player::update() {
   if(Input::getMouseButton() == 1) {
      createBullet = true;
   }
}

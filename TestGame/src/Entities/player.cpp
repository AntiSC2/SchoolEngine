#include "player.h"

Player::Player() {
   sprite = new Sprite;
   sprite->initSprite(position.x, position.y, 255, 255, 255, 255, 255, 255, "resources/textures/player.png");
}

Player::~Player() {
   delete sprite;
}

void Player::render(SpriteBatch *batch) {
   sprite->render(batch);
}

void Player::update() {
   ;
}

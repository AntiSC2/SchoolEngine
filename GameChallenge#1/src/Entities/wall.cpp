#include "wall.h"

Wall::Wall(int x, int y, WALL_ID id) : ID(id) {
   destRect.x = x;
   destRect.y = y;
   destRect.z = 64;
   destRect.w = 64;
   broken = false;
   if(ID == WALL_ID::LIGHT_BRICK) {
      sprite.initSprite(x, y, 64, 64, 255, 255, 255, 255, "resources/textures/light_bricks.png");
   }
   if(ID == WALL_ID::RED_BRICK) {
      sprite.initSprite(x, y, 64, 64, 255, 255, 255, 255, "resources/textures/red_bricks.png");
   }
   if(ID == WALL_ID::GLASS) {
      sprite.initSprite(x, y, 64, 64, 255, 255, 255, 255, "resources/textures/glass.png");
   }
}

Wall::~Wall() {
   ;
}

void Wall::init() {
   broken = false;
}

void Wall::update() {
   ;
}

void Wall::render(SpriteBatch* batch) {
   if(broken == false)
      sprite.render(batch);
}

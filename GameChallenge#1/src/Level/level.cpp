#include "level.h"

Level::Level() : width(0), height(0), humans(0), TILE_SIZE(64) {
   ;
}

Level::~Level() {
   for(int i = 0; i < entities.size(); i++) {
      delete entities[i];
   }
   entities.clear();
   walls.clear();
}

void Level::setWidth(unsigned int x) {
   width = x;
}

void Level::setHeight(unsigned int y) {
   height = y;
}

void Level::setHumans(unsigned int humans) {
   this->humans = humans;
}

bool Level::checkWalls(glm::vec4& position) {
   position.y = -position.y;
   int x[4];
   int y[4];
   glm::vec4 collisionRects[4];
   for(int i = 0; i < 4; i++) {
      switch(i) {
         case 0:
            x[i] = std::floor(position.x / 64);
            y[i] = std::floor(position.y / 64);
            break;
         case 1:
            x[i] = std::floor((position.x + position.z) / 64);
            y[i] = std::floor(position.y / 64);
            break;
         case 2:
            x[i] = std::floor((position.x + position.z) / 64);
            y[i] = std::floor((position.y + position.w) / 64);
            break;
         case 3:
            x[i] = std::floor(position.x / 64);
            y[i] = std::floor((position.y + position.w) / 64);
            break;
      }
   }
   for(int i = 0; i < 4; i++) {
      collisionRects[i].w = 100;
      if(walls[y[i]][x[i]] != '.' && walls[y[i]][x[i]] != '@' && walls[y[i]][x[i]] != 'Z') {
         collisionRects[i].x = x[i] * 64;
         collisionRects[i].y = y[i] * 64;
         collisionRects[i].z = TILE_SIZE;
         collisionRects[i].w = TILE_SIZE;
      }
   }
   for(int i = 0; i < 4; i++) {
      if(collisionRects[i].w != 100) {
         const float TILE_RADIUS = TILE_SIZE / 2;
         const float ENTITY_RADIUS = position.z / 2;
         const float MIN_DISTANCE = ENTITY_RADIUS + TILE_RADIUS;

         glm::vec2 distVec = glm::vec2(position.x + ENTITY_RADIUS, position.y + ENTITY_RADIUS) - glm::vec2(collisionRects[i].x + TILE_RADIUS, collisionRects[i].y + TILE_RADIUS);
         float xDepth = MIN_DISTANCE - abs(distVec.x);
         float yDepth = MIN_DISTANCE - abs(distVec.y);

         if(xDepth > 0 || yDepth > 0) {
            if(std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f)) {
               if(distVec.x < 0) {
                  position.x -= xDepth;
               } else {
                  position.x += xDepth;
               }
            } else {
               if(distVec.y < 0) {
                  position.y -= yDepth;
               } else {
                  position.y += yDepth;
               }
            }
         }
      }
   }
   position.y = -position.y;
   return true;
}

void Level::addBlocks(std::string& fileLine) {
   walls.push_back(fileLine);
}

void Level::finishLevel() {
   Color white;
   white.r = 255;
   white.g = 255;
   white.b = 255;
   white.a = 255;
   glm::vec4 tileRect;
   tileRect.z = TILE_SIZE;
   tileRect.w = TILE_SIZE;
   glm::vec4 uvRect;
   uvRect.x = 0;
   uvRect.y = 0;
   uvRect.z = 1;
   uvRect.w = -1;
   levelBatch.init();
   levelBatch.begin();
   for(int y = 0; y < height; y++) {
      tileRect.y = y * TILE_SIZE;
      tileRect.y = -tileRect.y;
      for(int x = 0; x < width; x++) {
         tileRect.x = x * TILE_SIZE;
         switch(walls[y][x]) {
            case 'R':
               levelBatch.draw(tileRect, uvRect, RM::TextureCache->createTexture("resources/textures/red_bricks.png")->getID(), 0.0f, white);
               break;
            case 'L':
               levelBatch.draw(tileRect, uvRect, RM::TextureCache->createTexture("resources/textures/light_bricks.png")->getID(), 0.0f, white);
               break;
            case 'G':
               levelBatch.draw(tileRect, uvRect, RM::TextureCache->createTexture("resources/textures/glass.png")->getID(), 0.0f, white);
               break;
            default:
               break;
         }
      }
   }
   levelBatch.end();
}

void Level::update() {
   for(int i = 0; i < entities.size(); i++) {
      entities[i]->update();
   }
}

void Level::render() {
   for(int i = 0; i < entities.size(); i++) {
      //entities[i]->render(batch);
   }
   levelBatch.renderDraw();
}


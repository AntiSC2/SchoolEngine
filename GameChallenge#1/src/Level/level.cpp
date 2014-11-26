#include "level.h"

Level::Level() : width(0), height(0), humans(0), TILE_SIZE(64), win_state(0) {
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

void Level::clearLevel() {
   for(int i = 0; i < entities.size(); i++) {
      delete entities[i];
   }
   entities.clear();
   walls.clear();
   bullets.clear();
   win_state = 0;
}

unsigned int Level::getWidth() {
   return width;
}

unsigned int Level::getHeight() {
   return height;
}

bool Level::checkWalls(glm::vec4& position) {
   bool hitWall = false;
   try {
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
         if(walls.at(y[i]).at(x[i]) != '.' && walls.at(y[i]).at(x[i]) != '@' && walls.at(y[i]).at(x[i]) != 'Z') {
            collisionRects[i].x = x[i] * 64;
            collisionRects[i].y = y[i] * 64;
            collisionRects[i].z = TILE_SIZE;
            collisionRects[i].w = TILE_SIZE;
         }
      }
      for(int i = 0; i < 4; i++) {
         if(collisionRects[i].w != 100) {
            const float TILE_RADIUS = TILE_SIZE / 2;
            const float ENTITY_RADIUS = position.w / 2;
            const float MIN_DISTANCE = ENTITY_RADIUS + TILE_RADIUS;

            glm::vec2 distVec = glm::vec2(position.x + ENTITY_RADIUS, position.y + ENTITY_RADIUS) - glm::vec2(collisionRects[i].x + TILE_RADIUS, collisionRects[i].y + TILE_RADIUS);
            float xDepth = MIN_DISTANCE - abs(distVec.x);
            float yDepth = MIN_DISTANCE - abs(distVec.y);

            if(xDepth > 0 || yDepth > 0) {
               if(std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f)) {
                  if(distVec.x < 0) {
                     position.x -= xDepth;
                     hitWall = true;
                  } else {
                     position.x += xDepth;
                     hitWall = true;
                  }
               } else {
                  if(distVec.y < 0) {
                     position.y -= yDepth;
                     hitWall = true;
                  } else {
                     position.y += yDepth;
                     hitWall = true;
                  }
               }
            }
         }
      }
      position.y = -position.y;
   }
   catch(const std::out_of_range& error) {
      //printf("Not inside the level! %s\n", error.what());

   }
   return hitWall;
}

void Level::addBlocks(std::string& fileLine) {
   walls.push_back(fileLine);
}

void Level::finishLevel(Camera2D* camera) {
   levelCamera = camera;
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
         case 'Z': {
            Entity* newZombie = new Zombie(tileRect.x, tileRect.y, *this);
            entities.push_back(newZombie);
            newZombie = nullptr;
            break;
         }
         case '@': {
            Entity* newPlayer = new Player(tileRect.x, tileRect.y, *this);
            entities.push_back(newPlayer);
            newPlayer = nullptr;
            break;
         }
         default:
            break;
         }
      }
   }
   levelBatch.end();
   if(humans > 0) {
      int zombies = entities.size();

      for(int i = 0; i < humans; i++) {
         Entity* newHuman = new Human((rand() % (width - 2) + 1) * 64, -(rand() % (height - 2) + 2) * 64, *this);
         entities.push_back(newHuman);
         newHuman = nullptr;
      }
   }
}

Entity* Level::getClosestHuman(glm::vec4& destRect) {
   Entity* MIN = nullptr;
   glm::vec2 objPos(destRect.x, abs(destRect.y));

   float MIN_DISTANCE = 99999.0f;
   for(int i = 0; i < entities.size(); i++) {
      if(entities[i]->getID() < 3) {
         glm::vec2 entPos(entities[i]->getPosition().x, abs(entities[i]->getPosition().y));
         float distance = glm::length(entPos - objPos);
         if(distance < MIN_DISTANCE && entities[i]->getID() < 3) {
            MIN = entities[i];
            MIN_DISTANCE = distance;
         }
      }
   }
   return MIN;
}

Entity* Level::getEntity(const glm::vec4& destRect) {
   Entity* MIN = nullptr;
   glm::vec2 objPos(destRect.x, abs(destRect.y));

   float MIN_DISTANCE = 99999.0f;
   for(int i = 0; i < entities.size(); i++) {
      glm::vec2 entPos(entities[i]->getPosition().x, abs(entities[i]->getPosition().y));
      float distance = glm::length(entPos - objPos);
      if(distance < MIN_DISTANCE && objPos != entPos) {
         MIN = entities[i];
         MIN_DISTANCE = distance;
      }
   }
   return MIN;
}

Entity* Level::getZombie(const glm::vec4& destRect) {
   Entity* MIN = nullptr;
   glm::vec2 objPos(destRect.x, abs(destRect.y));

   float MIN_DISTANCE = 99999.0f;
   for(int i = 0; i < entities.size(); i++) {
      glm::vec2 entPos(entities[i]->getPosition().x, abs(entities[i]->getPosition().y));
      float distance = glm::length(entPos - objPos);
      if(distance < MIN_DISTANCE && entities[i]->getID() == 3) {
         MIN = entities[i];
         MIN_DISTANCE = distance;
      }
   }
   return MIN;
}

void Level::update() {
   bool win = true;
   for(unsigned int i = 0; i < entities.size(); i++) {
      if(entities[i]->getID() == 3)
         win = false;
      if(entities[i]->getPosition().x < 32 || entities[i]->getPosition().y > -32 ||
            entities[i]->getPosition().x > width * 64 - 32 || entities[i]->getPosition().y > -(height * 64 - 64)) {
         delete entities[i];
         entities[i] = entities.back();
         entities.pop_back();
         i--;
      } else {
         entities[i]->update();

         if(entities[i]->getID() == 3) {
            if(entities[i]->checkEntityCollision(entities[i]->targetP)) {
               for(unsigned int a = 0; a < entities.size(); a++) {
                  if(entities[i]->targetP == entities[a]) {
                     Entity* newZombie = new Zombie(entities[a]->getPosition().x, entities[a]->getPosition().y, *this);
                     delete entities[a];
                     entities[a] = entities.back();
                     entities.pop_back();
                     entities.push_back(newZombie);
                     newZombie = nullptr;
                     break;
                  }
               }
            }
         }
      }
   }
   for(unsigned int i = 0; i < bullets.size(); i++) {
      bullets[i].update();
      bullets[i].targetE = getZombie(bullets[i].getPosition());
      if(checkWalls(bullets[i].getPosition()) == true) {
         bullets[i] = bullets.back();
         bullets.pop_back();
         i--;
      } else if(bullets[i].checkEntityCollision(bullets[i].targetE)) {
         for(unsigned int z = 0; z < entities.size(); z++) {
            if(entities[z] == bullets[i].targetE) {
               delete entities[z];
               entities[z] = entities.back();
               entities.pop_back();
               break;
            }
         }
         bullets[i] = bullets.back();
         bullets.pop_back();
         i--;
      }
   }
   if(win == true && win_state == false) {
      win_state = true;
      printf("YOU WIN! Score: %d\n", entities.size() - 1);
   }
}

void Level::render(SpriteBatch *batch) {
   for(unsigned int i = 0; i < entities.size(); i++) {
      entities[i]->render(batch);
   }
   for(unsigned int i = 0; i < bullets.size(); i++) {
      bullets[i].render(batch);
   }
   levelBatch.renderDraw();
}

void Level::addBullet(const glm::vec4& destRect) {
   Bullet* newBullet = new Bullet(destRect.x + (destRect.z / 2 - 4), destRect.y + (destRect.w / 2 + 4), glm::vec2(Input::getMouseX(levelCamera), Input::getMouseY(levelCamera)));
   bullets.push_back(*newBullet);
   newBullet = nullptr;
}


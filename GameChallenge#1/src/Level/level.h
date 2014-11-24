#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED
#include "Entities/entity.h"
#include "Entities/zombie.h"
#include "Entities/player.h"
#include "Entities/human.h"
#include "Entities/bullet.h"
#include <stdexcept>
#include <input.h>
#include <Camera/camera2D.h>
#include <Graphics/spritebatch.h>
#include <Graphics/vertex.h>
#include <Managers/rm.h>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>

class Level {
public:
   Level();
   ~Level();

   void setWidth(unsigned int x);
   void setHeight(unsigned int y);
   void setHumans(unsigned int humans);

   unsigned int getWidth();
   unsigned int getHeight();

   bool checkWalls(glm::vec4& position);
   Entity* getClosestHuman(glm::vec4& destRect);
   Entity* getEntity(const glm::vec4& destRect);
   Entity* getZombie(const glm::vec4& destRect);
   void addBullet(const glm::vec4& destRect);

   void addBlocks(std::string& fileLine);
   void finishLevel(Camera2D *camera);
   void update();
   void render(SpriteBatch *batch);

private:
   unsigned int width, height, humans, TILE_SIZE;
   SpriteBatch levelBatch;
   Camera2D *levelCamera;
   std::vector<std::string> walls;
   std::vector<Entity*> entities;
   std::vector<Bullet> bullets;
};

#endif // LEVEL_H_INCLUDED

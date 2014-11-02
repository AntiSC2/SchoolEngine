#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED
#include "Entities/entity.h"
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

      bool checkWalls(glm::vec4& position);

      void addBlocks(std::string& fileLine);
      void finishLevel();
      void update();
      void render();

   private:
      unsigned int width, height, humans, TILE_SIZE;
      SpriteBatch levelBatch;
      std::vector<std::string> walls;
      std::vector<Entity*> entities;
};

#endif // LEVEL_H_INCLUDED

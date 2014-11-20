#ifndef HUMAN_H_INCLUDED
#define HUMAN_H_INCLUDED
#include "Entities/entity.h"
#include "Level/level.h"
#include <Graphics/sprite.h>
#include <Graphics/spritebatch.h>


class Level;

class Human : public Entity {
   public:
      Human(int x, int y, Level& a);
      ~Human();

      void update();
      void render(SpriteBatch *batch);
      int getID();
   private:
      unsigned int frames;
      Sprite sprite;
      Level *a;
      glm::vec2 direction;
      float speed;
};

#endif // HUMAN_H_INCLUDED

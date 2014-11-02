#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED
#include <Graphics/sprite.h>
#include <Graphics/spritebatch.h>
#include "Entities/entity.h"

enum class WALL_ID {
   LIGHT_BRICK = 1,
   RED_BRICK = 2,
   GLASS = 3
};

class Wall : public Entity {
   public:
      Wall(int x, int y, WALL_ID id);
      ~Wall();

      void init();

      void update();
      void render(SpriteBatch* batch);

   private:
      Sprite sprite;
      WALL_ID ID;
      bool broken;
};

#endif // WALL_H_INCLUDED

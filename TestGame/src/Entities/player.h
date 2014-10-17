#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "entity.h"
#include <Graphics/sprite.h>
#include <Graphics/spritebatch.h>

class Player : public Entity {
   public:
      Player();
      ~Player();

      void render(SpriteBatch *batch);
      void update();

   private:
      Sprite *sprite;
};

#endif // PLAYER_H_INCLUDED

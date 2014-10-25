#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <SDL2/SDL.h>
#include "entity.h"
#include <Graphics/sprite.h>
#include <Graphics/spritebatch.h>
#include <input.h>

class Player : public Entity {
   public:
      Player();
      ~Player();

      void render(SpriteBatch *batch);
      void update();

      bool createBullet;

   private:
      Sprite *sprite;
};

#endif // PLAYER_H_INCLUDED

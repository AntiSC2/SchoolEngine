#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "entity.h"
#include <Graphics/sprite.h>
#include <Graphics/spritebatch.h>

class Bullet : public Entity {
   public:
      Bullet(int x = 0, int y = 0, int dirX = 0, int dirY = 0, int lifeTime = 240);
      ~Bullet();

      void render(SpriteBatch *batch);
      void update();

      unsigned int lifeTime;

   private:
      Sprite *sprite;
      glm::vec2 direction;
      float speed;
};

#endif // BULLET_H_INCLUDED

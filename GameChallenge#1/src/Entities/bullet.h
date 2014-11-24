#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED
#include <glm/glm.hpp>
#include "Entities/entity.h"
#include <Graphics/sprite.h>
#include <Graphics/spritebatch.h>

class Bullet {
   public:
      Bullet(int x, int y, glm::vec2 direction);
      void update();
      void render(SpriteBatch* batch);
      Entity* targetE;
      glm::vec4& getPosition();

      bool checkEntityCollision(Entity* a);
   private:
      Sprite sprite;
      glm::vec2 direction;
      glm::vec4 destRect;
      float speed;
};

#endif // BULLET_H_INCLUDED

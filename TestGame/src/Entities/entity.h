#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED
#include <glm/glm.hpp>
#include <Graphics/spritebatch.h>

class Entity {
   public:
      Entity();
      virtual ~Entity();

      virtual void render(SpriteBatch *batch) = 0;
      virtual void update() = 0;

      glm::vec2 getPosition() {
         return position;
      }
   protected:
      glm::vec2 position;
};

#endif // ENTITY_H_INCLUDED

#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED
#include <glm/glm.hpp>
#include <Graphics/spritebatch.h>

class Entity {
   public:
      Entity() {
         ;
      }
      virtual ~Entity() {
         ;
      }

      virtual void render(SpriteBatch *batch) = 0;
      virtual void update() = 0;

      glm::vec2 getPosition() {
         return position;
      }

      bool checkCollision(const glm::vec4& a, const glm::vec4& b) {
         if(a.x + a.z < b.x) return false;
         if(a.y + a.w < b.y) return false;
         if(a.x > b.x + b.z) return false;
         if(a.y > b.y + b.w) return false;
         return true;
      }

   protected:
      glm::vec2 position;
      glm::vec4 bounding_box;
};

#endif // ENTITY_H_INCLUDED

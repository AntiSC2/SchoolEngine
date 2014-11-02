#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED
#include <Graphics/spritebatch.h>
#include <vector>
#include <glm/glm.hpp>

class Entity {
   public:
      Entity() {
         ;
      }
      ~Entity() {
         ;
      }
      virtual void update() = 0;
      virtual void render(SpriteBatch* batch) = 0;

      glm::vec4& getPosition() {
         return destRect;
      }

      bool checkCollision(glm::vec4& a, glm::vec4& b) {
         if(a.x + a.z < b.x) return false;
         if(a.x > b.x + b.z) return false;
         if(a.y + a.w < b.y) return false;
         if(a.y > b.y + b.w) return false;
         return true;
      }
   protected:
      glm::vec4 destRect;
};

#endif // ENTITY_H_INCLUDED

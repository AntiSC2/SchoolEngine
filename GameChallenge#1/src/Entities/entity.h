#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED
#include <Graphics/spritebatch.h>
#include <vector>
#include <cmath>
#include <glm/glm.hpp>

class Entity {
public:
   Entity() {
      ;
   }
   virtual ~Entity() {
      ;
   }
   virtual void update() = 0;
   virtual void render(SpriteBatch* batch) = 0;
   virtual int getID() = 0;

   const glm::vec4& getPosition() const {
      return destRect;
   }

   bool checkEntityCollision(Entity* a) {
      float RADIUS1 = a->getPosition().w / 2;
      float RADIUS2 = destRect.w / 2;
      if(std::sqrt((a->destRect.x - destRect.x) * (a->destRect.x - destRect.x) + (a->destRect.y - destRect.y) * (a->destRect.y - destRect.y)) < (RADIUS1 - RADIUS2))
         return true;
      return false;
   }

   bool checkCollision(glm::vec4& a, glm::vec4& b) {
      if(a.x + a.z < b.x) return false;
      if(a.x > b.x + b.z) return false;
      if(a.y + a.w < b.y) return false;
      if(a.y > b.y + b.w) return false;
      return true;
   }
   Entity* targetP;
protected:
   glm::vec4 destRect;
};

#endif // ENTITY_H_INCLUDED

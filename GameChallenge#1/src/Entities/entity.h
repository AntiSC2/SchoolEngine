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
      if(a == nullptr)
         return false;
      float RADIUS1 = a->destRect.w / 2;
      float RADIUS2 = destRect.w / 2;
      float depth = std::sqrt(std::pow(destRect.x - a->destRect.x, 2) + std::pow(destRect.y - a->destRect.y, 2));
      if(depth < (RADIUS1 + RADIUS2)) {
         float MIN_DISTANCE = RADIUS1 + RADIUS2;
         glm::vec2 distVec = glm::vec2(destRect.x + RADIUS2, destRect.y + RADIUS2) - glm::vec2(a->destRect.x + RADIUS1, a->destRect.y + RADIUS1);
         float xDepth = MIN_DISTANCE - std::abs(distVec.x);
         float yDepth = MIN_DISTANCE - std::abs(distVec.y);

         if(xDepth > 0 || yDepth > 0) {
            if(std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f)) {
               if(distVec.x < 0) {
                  destRect.x -= xDepth;
               } else {
                  destRect.x += xDepth;
               }
            } else {
               if(distVec.y < 0) {
                  destRect.y -= yDepth;
               } else {
                  destRect.y += yDepth;
               }
            }
         }
         return true;
      }
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
   Entity* targetE;
protected:
   glm::vec4 destRect;
};

#endif // ENTITY_H_INCLUDED

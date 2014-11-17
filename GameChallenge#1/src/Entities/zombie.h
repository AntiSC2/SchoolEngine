#ifndef ZOMBIE_H_INCLUDED
#define ZOMBIE_H_INCLUDED
#include "Entities/entity.h"
#include "Level/level.h"
#include <Graphics/spritebatch.h>
#include <Graphics/sprite.h>
#include <glm/glm.hpp>

class Level;

class Zombie : public Entity {
public:
   Zombie(int x, int y, Level& a);
   ~Zombie();
   void update();
   void render(SpriteBatch* batch);
   int getID();
private:
   Sprite sprite;
   Level *a;

   glm::vec2 target;
   float speed;
};

#endif // ZOMBIE_H_INCLUDED


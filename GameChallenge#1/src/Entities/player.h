#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "Entities/entity.h"
#include "Level/level.h"
#include <input.h>
#include <Graphics/sprite.h>

class Level;

class Player : public Entity {
public:
   Player(int x, int y, Level& a);
   ~Player();

   void init(int x, int y);

   void update();
   void render(SpriteBatch* batch);
   int getID();
private:
   const float speed;
   int frames;
   bool createBullet;
   Sprite sprite;
   Level *a;
};

#endif // PLAYER_H_INCLUDED

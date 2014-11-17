#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "game.h"
#include "entity.h"

class Level;

class Player : public Entity {
public:
   Player(Level& a);
   ~Player();

   void init(int x, int y);

   void update();
   void render(SpriteBatch* batch);
   int getID();
private:
   const float speed;
   Sprite sprite;
   Level *a;
};

#endif // PLAYER_H_INCLUDED
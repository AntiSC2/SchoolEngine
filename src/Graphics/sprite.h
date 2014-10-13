#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED
#ifndef GLEW_BUILD
#define GLEW_BUILD
#endif // GLEW_BUILD
#include <GL/glew.h>
#include <stdio.h>
#include "vertex.h"

class Sprite{
   public:
      Sprite();
      ~Sprite();
      void initSprite(int x, int y, int width, int height, GLubyte r, GLubyte g, GLubyte b, GLubyte a);
      void render();
   private:
      GLint x;
      GLint y;
      GLint width;
      GLint height;
      GLubyte r,g,b,a;
      GLuint vboID;
};

#endif // SPRITE_H_INCLUDED

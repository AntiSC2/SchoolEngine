#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED
#ifndef GLEW_BUILD
#define GLEW_BUILD
#endif // GLEW_BUILD
#include <GL/glew.h>
#include <stdio.h>
#include "vertex.h"
#include "texture.h"
#include "Managers/rm.h"

class Sprite {
   public:
      Sprite();
      ~Sprite();
      void initSprite(int x, int y, int width, int height, GLubyte r, GLubyte g, GLubyte b, GLubyte a, const char* filePath);
      void render();
   private:
      GLint x;
      GLint y;
      GLint width;
      GLint height;
      GLubyte r,g,b,a;
      GLuint vboID;
      Texture *tex;
};

#endif // SPRITE_H_INCLUDED

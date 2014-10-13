#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED
#ifndef GLEW_BUILD
#define GLEW_BUILD
#endif // GLEW_BUILD
#include <GL/glew.h>
#include <glm/common.hpp>

struct Vertex{
   GLint position[3];

   GLubyte color[4];

   void setPosition(GLint x, GLint y, GLint z){
      position[0] = x;
      position[1] = y;
      position[2] = z;
   }
   void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a){
      color[0] = r;
      color[1] = g;
      color[2] = b;
      color[3] = a;
   }
};

#endif // VERTEX_H_INCLUDED

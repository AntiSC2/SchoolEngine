#include "sprite.h"

Sprite::Sprite() : x(0), y(0), width(0), height(0), r(0), g(0), b(0), a(0), vboID(0){
   ;
}

Sprite::~Sprite(){
   if(vboID != 0){
      glDeleteBuffers(1, &vboID);
   }
}

void Sprite::initSprite(int x, int y, int width, int height, GLubyte r, GLubyte b, GLubyte g, GLubyte a){



   if(vboID != 0){
      glDeleteBuffers(1, &vboID);
   } else {
      glGenBuffers(1, &vboID);
   }

   Vertex vertices[6];

   vertices[0].setPosition(x + width, y + height, 0);
   vertices[1].setPosition(x, y + height, 0);
   vertices[2].setPosition(x, y, 0);

   vertices[3].setPosition(x, y, 0);
   vertices[4].setPosition(x + width, y, 0);
   vertices[5].setPosition(x + width, y + height, 0);

   for(int i = 0; i < 6; i++){
      if(i != 3 && i != 5)
         vertices[i].setColor(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255);
      else if(i == 3) {
         vertices[i].color[0] = vertices[2].color[0];
         vertices[i].color[1] = vertices[2].color[1];
         vertices[i].color[2] = vertices[2].color[2];
         vertices[i].color[3] = vertices[2].color[3];
      }
      else {
         vertices[i].color[0] = vertices[0].color[0];
         vertices[i].color[1] = vertices[0].color[1];
         vertices[i].color[2] = vertices[0].color[2];
         vertices[i].color[3] = vertices[0].color[3];
      }
   }

   glBindBuffer(GL_ARRAY_BUFFER, vboID);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::render() {
   glBindBuffer(GL_ARRAY_BUFFER, vboID);

   glEnableVertexAttribArray(0);
   glEnableVertexAttribArray(1);

   glVertexAttribPointer(0, 3, GL_INT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
   glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
   //glEnableVertexArrayAttrib(2);

   glDrawArrays(GL_TRIANGLES, 0, 6);

   glDisableVertexAttribArray(0);
   glDisableVertexAttribArray(1);

   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

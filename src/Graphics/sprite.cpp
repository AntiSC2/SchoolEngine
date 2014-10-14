#include "sprite.h"

Sprite::Sprite() : x(0), y(0), width(0), height(0), r(0), g(0), b(0), a(0), vboID(0), tex(nullptr) {
   ;
}

Sprite::~Sprite() {
   tex = nullptr;
   if(vboID != 0) {
      glDeleteBuffers(1, &vboID);
   }
}

void Sprite::initSprite(int x, int y, int width, int height, GLubyte r, GLubyte b, GLubyte g, GLubyte a, const char* filePath) {

   if(vboID != 0) {
      glDeleteBuffers(1, &vboID);
   } else {
      glGenBuffers(1, &vboID);
   }

   tex = RM::TextureCache->createTexture(filePath);

   Vertex vertices[6];

   vertices[0].setPosition(x + width, y + height);
   vertices[0].setUV(1, 0);
   vertices[1].setPosition(x, y + height);
   vertices[1].setUV(0, 0);
   vertices[2].setPosition(x, y);
   vertices[2].setUV(0, 1);

   vertices[3].setPosition(x, y);
   vertices[3].setUV(0, 1);
   vertices[4].setPosition(x + width, y);
   vertices[4].setUV(1, 1);
   vertices[5].setPosition(x + width, y + height);
   vertices[5].setUV(1, 0);

   for(int i = 0; i < 6; i++) {
      vertices[i].setColor(r, g, b, a);
   }

   glBindBuffer(GL_ARRAY_BUFFER, vboID);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::render() {
   glBindBuffer(GL_ARRAY_BUFFER, vboID);
   tex->use();

   glEnableVertexAttribArray(0);
   glEnableVertexAttribArray(1);
   glEnableVertexAttribArray(2);

   glVertexAttribPointer(0, 3, GL_INT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
   glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
   glVertexAttribPointer(2, 2, GL_INT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));


   glDrawArrays(GL_TRIANGLES, 0, 6);

   glDisableVertexAttribArray(0);
   glDisableVertexAttribArray(1);
   glDisableVertexAttribArray(2);

   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

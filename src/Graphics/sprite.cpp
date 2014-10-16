#include "sprite.h"

Sprite::Sprite() : tex(nullptr) {
   ;
}

Sprite::~Sprite() {
   tex = nullptr;
}

void Sprite::initSprite(GLint xv, GLint yv, GLint width, GLint height, GLubyte r, GLubyte b, GLubyte g, GLubyte a, const char* filePath) {

   tex = RM::TextureCache->createTexture(filePath);

   destRect.x = xv;
   destRect.y = yv;
   destRect.z = width;
   destRect.w = height;

   uvRect.x = 0;
   uvRect.y = 0;
   uvRect.z = 1;
   uvRect.w = -1;

   color.r = r;
   color.g = g;
   color.b = b;
   color.a = a;
}

void Sprite::render(SpriteBatch* batch) {
   tex->use();
   batch->draw(destRect, uvRect, Texture::currentlyBound, 0, color);
}

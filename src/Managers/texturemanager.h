#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED
#include <map>
#include <utility>
#include <stdio.h>
#include "Graphics/texture.h"

class TextureManager {
   public:
      TextureManager();
      ~TextureManager();

      Texture* createTexture(const char* filePath);
   private:
      std::map<const char*, Texture*> textures;
};

#endif // TEXTUREMANAGER_H_INCLUDED

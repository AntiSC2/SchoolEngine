#include "texturemanager.h"

TextureManager::TextureManager() {
   ;
}

TextureManager::~TextureManager() {
   for(const auto& elem : textures) {
      printf("Removing texture: %s\n", elem.first);
      delete elem.second;
   }
}

Texture* TextureManager::createTexture(const char* filePath) {
   auto it = textures.find(filePath);
   if(it == textures.end()) {
      Texture* temp = new Texture;
      temp->loadTexture(filePath);
      printf("Creating new texture: %s\n", filePath);
      textures.insert(std::pair<const char*, Texture*>(filePath, temp));
      printf("Loading texture: %s\n", filePath);
      it = textures.find(filePath);
      return it->second;
   } else {
      printf("Loading cached texture: %s\n", filePath);
      return it->second;
   }
   return nullptr;
}

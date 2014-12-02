#ifndef RM_H_INCLUDED
#define RM_H_INCLUDED
#include "texturemanager.h"
#include <fstream>
#include <string>

class RM {
public:
   static void init(const char* filePath);
   static TextureManager* TextureCache;

private:
};

#endif // RM_H_INCLUDED

#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "input.h"
#include "Graphics/screen.h"


class Engine {
   public:

      void initSubSystems();
      void initScreen(int width, int height, const char* title);
      void initResources(const char* filePath);
      void initShaders(const char* fileVert, const char* fileFrag);
      void initLevels(const char* filePath);
      void initCamera(int x, int y, int scale);


      Screen *screen;
      //Camera2D *camera;
      //Level *level;
      //Shader *shaders;
      //Resource Manager
      Input *input;
      Engine();
      ~Engine();

   private:
};

#endif // ENGINE_H_INCLUDED

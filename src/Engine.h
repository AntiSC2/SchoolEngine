#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <time.h>
#include <stdio.h>
#include "input.h"
#include "Graphics/screen.h"
#include "Graphics/shader.h"
#include "Graphics/sprite.h"
#include "Graphics/spritebatch.h"
#include "Managers/rm.h"
#include "Camera/camera2D.h"


class Engine {
   public:

      void initSubSystems();
      void initScreen(int width, int height, const char* title);
      void initResources(const char* filePath);
      void initShaders(const char* fileVert, const char* fileFrag);
      void initLevels(const char* filePath);
      void initCamera(int x, int y, int scale);


      Screen *screen;
      Camera2D *camera;
      SpriteBatch *TheBatch;
      //Level *level;
      Shader **shaders;
      //Resource Manager
      Input *input;
      /*TEMP*/
      Sprite *sprite;
      /*TEMP*/
      Engine();
      ~Engine();

   private:
};

#endif // ENGINE_H_INCLUDED

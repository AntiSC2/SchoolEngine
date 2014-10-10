#include "Engine.h"

Engine::Engine(){
   ;
}

Engine::~Engine(){
   delete input;
   delete screen;
   IMG_Quit();
   SDL_Quit();
}

void Engine::initSubSystems() {
   if(SDL_Init(SDL_INIT_VIDEO) != 0){
      printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
   } else if(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG != IMG_INIT_PNG){
      printf("SDL_Image could not initialize! IMG Error: %s\n", IMG_GetError());
   } else {
      input = new Input;
   }
}

void Engine::initScreen(int width, int height, const char* title) {
   screen = new Screen(width, height, title);
}

void Engine::initResources(const char* filePath){
   ;
}

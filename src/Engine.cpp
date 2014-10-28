#include "Engine.h"

Engine::Engine() : screen(nullptr), camera(nullptr), shaders(nullptr), TheBatch(nullptr), input(nullptr) {
   ;
}

Engine::~Engine() {
   delete input;
   delete screen;
   delete RM::TextureCache;
   delete camera;
   delete TheBatch;
   delete[] shaders;
   IMG_Quit();
   SDL_Quit();
}

void Engine::initSubSystems() {
   if(SDL_Init(SDL_INIT_VIDEO) != 0) {
      printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
   } else if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
      printf("SDL_Image could not initialize! IMG Error: %s\n", IMG_GetError());
   } else {
      input = new Input;
   }
}

void Engine::initScreen(int width, int height, const char* title) {
   screen = new Screen(width, height, title);
   camera = new Camera2D(width, height);
   camera->init(width, height);
}

void Engine::initResources(const char* filePath) {
   srand(time(nullptr));
   TheBatch = new SpriteBatch;
   TheBatch->init();
   RM::init(filePath);
}

void Engine::initShaders(const char* fileVert, const char* fileFrag) {
   if(shaders != nullptr) {
      delete[] shaders;
      shaders = nullptr;
   }
   shaders = new Shader*[1];
   shaders[0] = &Shader::RENDERER;
   for(int i = 0; i < 1; i++) {
      shaders[i]->initProgram(fileVert, fileFrag);
      shaders[i]->addAttribute("position");
      shaders[i]->addAttribute("color");
      shaders[i]->addAttribute("uv");
      shaders[i]->linkProgram();
   }
   shaders[0]->use();
}

void Engine::initLevels(const char* filePath) {
   ;
}

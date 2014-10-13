#include "Engine.h"

Engine::Engine() {
   ;
}

Engine::~Engine() {
   delete input;
   delete screen;
   delete RM::TextureCache;
   delete camera;
   delete[] shaders;
   delete[] sprite;
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
   camera = new Camera2D(1280, 720);
   camera->init(1280, 720);
}

void Engine::initResources(const char* filePath) {
   srand(time(nullptr));
   RM::TextureCache->createTexture("resources/textures/tex.png");
   sprite = new Sprite[4];
   sprite[0].initSprite(0, 0, 128, 128, 255, 255, 255, 255, "resources/textures/tex.png");
   sprite[1].initSprite(-128, 0, 128, 128, 255, 255, 255, 255, "resources/textures/tex.png");
   sprite[2].initSprite(128, 0, 128, 128, 255, 255, 255, 255, "resources/textures/tex.png");
   sprite[3].initSprite(-64, -64, 128, 128, 255, 255, 255, 255, "resources/textures/tex.png");
}

void Engine::initShaders(const char* fileVert, const char* fileFrag) {
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

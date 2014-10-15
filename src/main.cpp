#include "Engine.h"
#include "Graphics/texture.h"
#include "Graphics/vertex.h"
#include "Managers/rm.h"
#include <cstring>

int main(int argc, char**argv) {
   Engine g;
   g.initSubSystems();
   g.initScreen(1280, 720, "SchoolEngine");
   g.initResources("APAPAP");
   g.initShaders("resources/shaders/Vertex.vert", "resources/shaders/Fragment.frag");
   const char* texFileklJlksjfklsj = "resources/textures/tex.png\0";
   Texture *TEX = RM::TextureCache->createTexture(texFileklJlksjfklsj);
   while(!g.input->window_closed()) {
      const float speed = 1.0f;
      const float scale_speed = 0.001f;
      g.screen->render();
      g.input->update();
      if(g.input->key_pressed(SDL_SCANCODE_Q)) {
         g.camera->setScale(g.camera->getScale() + scale_speed);
      }

      if(g.input->key_pressed(SDL_SCANCODE_E)) {
         g.camera->setScale(g.camera->getScale() - scale_speed);
      }

      if(g.input->key_pressed(SDL_SCANCODE_A)) {
         g.camera->setPosition(g.camera->getPosition() + glm::vec2(-speed, 0.0f));
      }

      if(g.input->key_pressed(SDL_SCANCODE_D)) {
         g.camera->setPosition(g.camera->getPosition() + glm::vec2(speed, 0.0f));
      }

      if(g.input->key_pressed(SDL_SCANCODE_W)) {
         g.camera->setPosition(g.camera->getPosition() + glm::vec2(0.0f, speed));
      }

      if(g.input->key_pressed(SDL_SCANCODE_S)) {
         g.camera->setPosition(g.camera->getPosition() + glm::vec2(0.0f, -speed));
      }
      g.camera->update();
      g.TheBatch->begin();
      Color color;
      color.r = 255;
      color.g = 255;
      color.b = 255;
      color.a = 255;
      TEX->use();
      g.TheBatch->draw(glm::vec4(0, 0, 128, 128), glm::vec4(0, 0, 1, 1), Texture::currentlyBound, 0, color);
      g.TheBatch->end();
      g.TheBatch->renderDraw();
      g.shaders[0]->setCameraMatrix(g.camera->getCameraMatrix());
      for(int i = 0; i < 1000; i++) {
        // g.sprite[i].render();
      }
      g.screen->update();
   }
   return 0;
}

#include "Engine.h"

int main(int argc, char**argv) {
   Engine g;
   g.initSubSystems();
   g.initScreen(1280, 720, "SchoolEngine");
   g.initResources("APAPAP");
   g.initShaders("resources/shaders/Vertex.vert", "resources/shaders/Fragment.frag");
   while(!g.input->window_closed()){
      g.screen->render();
      g.input->update();
      g.sprite[0].render();
      g.sprite[1].render();
      g.sprite[2].render();
      g.sprite[3].render();
      g.screen->update();
   }
   return 0;
}

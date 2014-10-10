#include "Engine.h"

int main(int argc, char**argv) {
   Engine g;
   g.initSubSystems();
   g.initScreen(1280, 720, "SchoolEngine");
   while(!g.input->window_closed()){
      g.screen->render();
      g.input->update();
      g.screen->update();
   }
   return 0;
}

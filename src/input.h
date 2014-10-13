#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
#include <iostream>

class Input {
private:
   SDL_Event event;
   static bool keys[65536];
   static std::vector<SDL_Scancode> pressed_keys;
   static std::vector<unsigned int> clicked_buttons;
   bool quit = false;
   static int mx, my, mb;
   static bool mg;
public:
   Input();
   void update();
   std::vector<SDL_Keycode> get_pressed_keys();
   static bool key_pressed(SDL_Scancode key);
   static bool key_typed(SDL_Scancode key);
   static bool mouse_clicked(unsigned int button);
   static int get_DX();
   static int get_DY();
   static int get_mouse_button();
   static bool mouse_grabbed();
   bool window_closed();
};

#endif // INPUT_H_INCLUDED

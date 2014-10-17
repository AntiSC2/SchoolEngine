/*#include "game.h"
#include <cstring>

int main(int argc, char**argv) {
   Game g;
   g.run();
   return 0;
}*/

#include <iostream>

int main() {
   double x, y;
   char operation;
   while(true) {
      std::cout << "Skriv in två tal: \n";
      std::cin >> x;
      std::cin >> y;
      std::cout << "Skriv in operation(+, -, *, /)\n";
      std::cin >> operation;
      switch(operation) {
         case '+' :
            std::cout << x + y << std::endl;
            break;
         case '-' :
            std::cout << x - y << std::endl;
            break;
         case '*' :
            std::cout << x * y << std::endl;
            break;
         case '/' :
            std::cout << x / y << std::endl;
            break;
      }
      std::cout << "Vill du fortsätta?" << std::endl;
      std::cin >> operation;
      if(operation == 'n') {
         break;
      }
   }
}

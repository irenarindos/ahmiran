// Brian Malloy        Game Construction

#include "manager.h"
#include <time.h>

int main(int, char*[]) {
	srand(time(NULL));
   try {
      Manager game_manager;
      game_manager.play();
   }
   catch (const string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
   return 0;
}

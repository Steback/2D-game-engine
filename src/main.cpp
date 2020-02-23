#include <iostream>
#include "Game.h"
#include "Constants.h"

int main(int argc, char *args[]) {
    Game* game = new Game();

    game -> initialize( WINDOW_WIDTH, WINDOW_HEIGHT );

    while ( game -> gameISRunning() ) {
        game -> processInput();
        game -> update();
        game -> render();
    }

    game -> destroy();

    return 0;
}

#include "game/game.h"

int main() {
    Game game;
    if (game.init()) {
        game.run();
        game.quit();
    } else {
        return 1;
    }
    return 0;
}

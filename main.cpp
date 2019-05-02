#include "Game/Game.h"
#include "Common/StaticInitializer.hpp"

void informMe(Game::Event *event);

int main(int argc, char** argv) {
    Game::StaticInitializer::initialize();

    new Game::Game();
    return 0;
}

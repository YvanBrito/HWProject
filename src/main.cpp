#include <iostream>
#include "Game/Game.hpp"

int main(int argc, char* argv[]) {
    Game& game = Game::getInstance();
    int exitCode{ 0 };

    if (game.init() == false) {
        std::cerr << "Failed to initialize the game." << std::endl;
        exitCode = -1;
    }
    else
    {
        game.run();
    }
    
    game.cleanup();
    
    return exitCode;
}
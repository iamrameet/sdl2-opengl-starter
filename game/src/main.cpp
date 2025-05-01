#include <iostream>
#include "TopDownShooterGame.hpp"
#include <glm/glm.hpp>
#include <memory>

// Define SDL_main to avoid linker errors
#define SDL_MAIN_HANDLED

// Screen dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char* WINDOW_TITLE = "Top-Down Shooter Game";

int main(int argc, char* argv[]) {
    // Create game instance
    Game::TopDownShooterGame game(WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Initialize the game
    if (!game.initialize()) {
        std::cerr << "Failed to initialize game!" << std::endl;
        return 1;
    }

    // Run the game loop
    game.run();

    // Game will automatically clean up when it goes out of scope

    return 0;
}

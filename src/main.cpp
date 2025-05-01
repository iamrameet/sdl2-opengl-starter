#include <iostream>
#include "Core/Game.hpp"
#include "GameObjects/Triangle.hpp"
#include <glm/glm.hpp>
#include <memory>

// Define SDL_main to avoid linker errors
#define SDL_MAIN_HANDLED

// Screen dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char* WINDOW_TITLE = "2D Game with SDL2 and OpenGL";

int main(int argc, char* argv[]) {
    // Create game instance
    Game game(WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Initialize the game
    if (!game.Initialize()) {
        std::cerr << "Failed to initialize game!" << std::endl;
        return 1;
    }

    // Game objects are initialized in Game::InitializeGameObjects

    // Run the game loop
    game.Run();

    // Game will automatically clean up when it goes out of scope

    return 0;
}

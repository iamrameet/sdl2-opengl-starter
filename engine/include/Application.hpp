#pragma once

#include <SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <memory>

namespace Engine {

// Forward declarations
class GameObject;
class Shader;
class Renderer;
class UISystem;

/**
 * @brief Base Application class that handles the core game loop and engine functionality.
 *
 * This class provides the foundation for creating games with the engine.
 * It handles window creation, OpenGL setup, and the main game loop.
 */
class Application {
public:
    // Constructor and destructor
    Application(const std::string& title, int width, int height);
    virtual ~Application();

    // Application lifecycle methods
    virtual bool initialize();
    void run();
    virtual void shutdown();

    // Application state
    bool isRunning() const { return m_running; }
    void quit() { m_running = false; }

    // Window dimensions
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

    // Game object management
    void addGameObject(std::shared_ptr<GameObject> gameObject);
    void removeGameObject(const std::string& name);

    // Renderer access
    std::shared_ptr<Renderer> getRenderer() { return m_renderer; }

    // UI system access
    std::shared_ptr<UISystem> getUISystem() { return m_uiSystem; }

protected:
    // Game loop methods - can be overridden by derived classes
    virtual void processInput();
    virtual void update(float deltaTime);
    virtual void render();

    // Initialize game objects - must be implemented by derived classes
    virtual void initializeGameObjects() = 0;

    // SDL and OpenGL objects
    SDL_Window* m_window;
    SDL_GLContext m_glContext;

    // Application state
    bool m_running;
    std::string m_title;
    int m_width;
    int m_height;

    // Game objects
    std::vector<std::shared_ptr<GameObject>> m_gameObjects;

    // Renderer
    std::shared_ptr<Renderer> m_renderer;

    // UI system
    std::shared_ptr<UISystem> m_uiSystem;

    // Shaders
    std::shared_ptr<Shader> m_shader;

    // Timing
    Uint32 m_lastFrameTime;
};

} // namespace Engine

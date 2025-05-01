#pragma once

#include <SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <memory>

#include "../Graphics/Renderer.hpp"

// Forward declarations
class GameObject;
class Shader;
class UISystem;
class Triangle;

class Game {
public:
    // Constructor and destructor
    Game(const std::string& title, int width, int height);
    ~Game();

    // Game lifecycle methods
    bool Initialize();
    void Run();
    void Shutdown();

    // Game state
    bool IsRunning() const { return m_running; }
    void Quit() { m_running = false; }

    // Window dimensions
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }

    // Game object management
    void AddGameObject(std::shared_ptr<GameObject> gameObject);
    void RemoveGameObject(const std::string& name);

    // Renderer access
    std::shared_ptr<Renderer> GetRenderer() { return m_renderer; }

    // UI system access
    std::shared_ptr<UISystem> GetUISystem() { return m_uiSystem; }

private:
    // Game loop methods
    void ProcessInput();
    void Update(float deltaTime);
    void Render();

    // Initialize game objects
    void InitializeGameObjects();

    // SDL and OpenGL objects
    SDL_Window* m_window;
    SDL_GLContext m_glContext;

    // Game state
    bool m_running;
    std::string m_title;
    int m_width;
    int m_height;

    // Game objects
    std::vector<std::shared_ptr<GameObject>> m_gameObjects;
    std::shared_ptr<Triangle> m_triangle;

    // Renderer
    std::shared_ptr<Renderer> m_renderer;

    // UI system
    std::shared_ptr<UISystem> m_uiSystem;

    // Shaders
    std::shared_ptr<Shader> m_shader;

    // Timing
    Uint32 m_lastFrameTime;
};

#include "Application.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

#include "GameObject.hpp"
#include "Shader.hpp"
#include "Renderer.hpp"
#include "UISystem.hpp"

namespace Engine {

Application::Application(const std::string& title, int width, int height)
    : m_window(nullptr)
    , m_glContext(nullptr)
    , m_running(false)
    , m_title(title)
    , m_width(width)
    , m_height(height)
    , m_lastFrameTime(0)
{
}

Application::~Application()
{
    shutdown();
}

bool Application::initialize()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Set OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Create window with OpenGL context
    m_window = SDL_CreateWindow(
        m_title.c_str(),
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        m_width, m_height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    if (!m_window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create OpenGL context
    m_glContext = SDL_GL_CreateContext(m_window);
    if (!m_glContext) {
        std::cerr << "OpenGL context could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    // Print OpenGL version
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    // Use VSync
    if (SDL_GL_SetSwapInterval(1) < 0) {
        std::cerr << "Warning: Unable to set VSync! SDL Error: " << SDL_GetError() << std::endl;
    }

    // Enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Initialize shader
    try {
        m_shader = std::make_shared<Shader>("assets/shaders/basic.vert", "assets/shaders/basic.frag");
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to load shaders: " << e.what() << std::endl;
        return false;
    }

    // Initialize renderer
    m_renderer = std::make_shared<Renderer>();
    if (!m_renderer->initialize(m_width, m_height)) {
        std::cerr << "Failed to initialize renderer" << std::endl;
        return false;
    }
    m_renderer->setShader(m_shader);

    // Initialize UI system
    m_uiSystem = std::make_shared<UISystem>();
    if (!m_uiSystem->initialize(m_renderer)) {
        std::cerr << "Failed to initialize UI system" << std::endl;
        return false;
    }

    // Initialize game objects
    initializeGameObjects();

    // Set initial frame time
    m_lastFrameTime = SDL_GetTicks();

    // Application is now running
    m_running = true;

    return true;
}

void Application::run()
{
    // Target frame rate (60 FPS)
    const Uint32 targetFrameTime = 1000 / 60;

    while (m_running) {
        // Record frame start time
        Uint32 frameStartTime = SDL_GetTicks();

        // Calculate delta time
        float deltaTime = (frameStartTime - m_lastFrameTime) / 1000.0f;
        m_lastFrameTime = frameStartTime;

        // Process input, update game state, and render
        processInput();
        update(deltaTime);
        render();

        // Swap the window buffers
        SDL_GL_SwapWindow(m_window);

        // Calculate frame time and delay if needed
        Uint32 frameTime = SDL_GetTicks() - frameStartTime;
        if (frameTime < targetFrameTime) {
            SDL_Delay(targetFrameTime - frameTime);
        }
    }
}

void Application::shutdown()
{
    // Clear game objects
    m_gameObjects.clear();

    // Release UI system
    m_uiSystem.reset();

    // Release renderer
    m_renderer.reset();

    // Release shader
    m_shader.reset();

    // Destroy OpenGL context and window
    if (m_glContext) {
        SDL_GL_DeleteContext(m_glContext);
        m_glContext = nullptr;
    }

    if (m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }

    // Quit SDL
    SDL_Quit();
}

void Application::processInput()
{
    // Check for quit events
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        // User requests quit
        if (e.type == SDL_QUIT) {
            m_running = false;
        }
        // User presses a key
        else if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_ESCAPE) {
                m_running = false;
            }
        }
    }
}

void Application::update(float deltaTime)
{
    // Update all game objects
    for (auto& gameObject : m_gameObjects) {
        gameObject->update(deltaTime);
    }
}

void Application::render()
{
    // Begin frame
    m_renderer->beginFrame();

    // Set up the shader
    m_shader->use();

    // Set up projection matrix (orthographic)
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_width),
                                      static_cast<float>(m_height), 0.0f,
                                      -1.0f, 1.0f);
    m_shader->setMat4("projection", projection);

    // Render all game objects
    for (auto& gameObject : m_gameObjects) {
        gameObject->render(*m_shader);
    }

    // End frame
    m_renderer->endFrame();

    // Note: We don't swap buffers here, it's done in Application::Run
}

void Application::addGameObject(std::shared_ptr<GameObject> gameObject)
{
    m_gameObjects.push_back(gameObject);
}

void Application::removeGameObject(const std::string& name)
{
    // Find and remove the game object with the given name
    m_gameObjects.erase(
        std::remove_if(m_gameObjects.begin(), m_gameObjects.end(),
            [&name](const std::shared_ptr<GameObject>& obj) { return obj->getName() == name; }),
        m_gameObjects.end());
}

} // namespace Engine

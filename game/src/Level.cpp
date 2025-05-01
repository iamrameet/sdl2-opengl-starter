#include "Level.hpp"
#include "Shader.hpp"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

namespace Game {

Level::Level(const std::string& name, const glm::vec2& position)
    : Engine::GameObject(name, position)
    , m_backgroundColor(0.1f, 0.1f, 0.2f)
    , m_gridColor(0.2f, 0.2f, 0.3f)
    , m_gridSize(50.0f)
{
    // Initialize the level's appearance
    initializeGeometry();
}

Level::~Level()
{
    // Clean up OpenGL resources
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
}

void Level::update(float deltaTime)
{
    // Level doesn't need to update
}

void Level::render(const Engine::Shader& shader)
{
    // Skip rendering if not active
    if (!m_active) return;

    // Use the shader
    shader.use();

    // Create model matrix
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(m_position, 0.0f));
    model = glm::scale(model, glm::vec3(m_scale, 1.0f));

    // Set model matrix in shader
    shader.setMat4("model", model);

    // Set color in shader (background color)
    shader.setVec3("color", m_backgroundColor);

    // Bind VAO and draw
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void Level::initializeGeometry()
{
    // Create a quad that covers the entire screen
    float vertices[] = {
        // positions
        0.0f, 0.0f, -0.1f,  // bottom left
        1.0f, 0.0f, -0.1f,  // bottom right
        0.0f, 1.0f, -0.1f,  // top left
        1.0f, 1.0f, -0.1f   // top right
    };

    // Create VAO and VBO
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    // Bind VAO
    glBindVertexArray(m_vao);

    // Bind VBO and copy vertices
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

} // namespace Game

#include "Enemy.hpp"
#include "Shader.hpp"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

namespace Game {

Enemy::Enemy(const std::string& name, const glm::vec2& position)
    : Engine::GameObject(name, position)
    , m_target(nullptr)
    , m_speed(100.0f)
    , m_color(1.0f, 0.2f, 0.2f) // Red color for enemies
{
    // Initialize the enemy's appearance
    initializeGeometry();
}

Enemy::~Enemy()
{
    // Clean up OpenGL resources
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
}

void Enemy::update(float deltaTime)
{
    // Move towards target if one exists
    if (m_target && m_target->isActive()) {
        // Calculate direction to target
        glm::vec2 direction = m_target->getPosition() - m_position;

        // Normalize direction
        if (glm::length(direction) > 0.0f) {
            direction = glm::normalize(direction);
        }

        // Move towards target
        m_position += direction * m_speed * deltaTime;

        // Update rotation to face target
        m_rotation = atan2(direction.y, direction.x) + glm::radians(90.0f);
    }
}

void Enemy::render(const Engine::Shader& shader)
{
    // Skip rendering if not active
    if (!m_active) return;

    // Use the shader
    shader.use();

    // Create model matrix
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(m_position, 0.0f));
    model = glm::rotate(model, m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(m_scale, 1.0f));

    // Set model matrix in shader
    shader.setMat4("model", model);

    // Set color in shader
    shader.setVec3("color", m_color);

    // Bind VAO and draw
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void Enemy::initializeGeometry()
{
    // Create a triangle pointing downward (towards the player)
    float vertices[] = {
        // positions
         0.0f,   0.5f, 0.0f,  // top
        -0.5f,  -0.5f, 0.0f,  // bottom left
         0.5f,  -0.5f, 0.0f   // bottom right
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

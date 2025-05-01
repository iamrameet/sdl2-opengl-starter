#include "Player.hpp"
#include "TopDownShooterGame.hpp"
#include "Shader.hpp"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

namespace Game {

Player::Player(const std::string& name, const glm::vec2& position)
    : Engine::GameObject(name, position)
    , m_moveDirection(0.0f, 0.0f)
    , m_speed(200.0f)
    , m_shooting(false)
    , m_fireRate(0.2f)
    , m_fireTimer(0.0f)
    , m_game(nullptr)
{
    // Initialize the player's appearance
    initializeGeometry();
}

Player::~Player()
{
    // Clean up OpenGL resources
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
}

void Player::update(float deltaTime)
{
    // Move the player based on input
    if (glm::length(m_moveDirection) > 0.0f) {
        m_position += m_moveDirection * m_speed * deltaTime;

        // Clamp position to screen bounds (assuming game is available)
        if (m_game) {
            m_position.x = glm::clamp(m_position.x, 0.0f, static_cast<float>(m_game->getWidth()));
            m_position.y = glm::clamp(m_position.y, 0.0f, static_cast<float>(m_game->getHeight()));
        }
    }

    // Handle shooting
    if (m_shooting) {
        m_fireTimer += deltaTime;
        if (m_fireTimer >= m_fireRate) {
            m_fireTimer = 0.0f;

            // Fire a projectile
            if (m_game) {
                // Fire in the direction the player is facing (up for now)
                m_game->fireProjectile(m_position, glm::vec2(0.0f, -1.0f));
            }
        }
    } else {
        m_fireTimer = m_fireRate; // Allow immediate fire when button is pressed
    }

    // Update rotation to face movement direction
    if (glm::length(m_moveDirection) > 0.0f) {
        m_rotation = atan2(m_moveDirection.y, m_moveDirection.x) + glm::radians(90.0f);
    }
}

void Player::render(const Engine::Shader& shader)
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

    // Set color in shader (blue for player)
    shader.setVec3("color", glm::vec3(0.0f, 0.5f, 1.0f));

    // Bind VAO and draw
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void Player::initializeGeometry()
{
    // Create a triangle pointing upward
    float vertices[] = {
        // positions
         0.0f,  -0.5f, 0.0f,  // bottom
        -0.5f,   0.5f, 0.0f,  // top left
         0.5f,   0.5f, 0.0f   // top right
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

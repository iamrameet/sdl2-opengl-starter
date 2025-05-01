#include "Projectile.hpp"
#include "Shader.hpp"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

namespace Game {

Projectile::Projectile(const std::string& name, const glm::vec2& position, const glm::vec2& direction)
    : Engine::GameObject(name, position)
    , m_direction(glm::normalize(direction))
    , m_speed(400.0f)
    , m_lifetime(0.0f)
    , m_maxLifetime(2.0f)
{
    // Initialize the projectile's appearance
    initializeGeometry();

    // Set rotation based on direction
    m_rotation = atan2(m_direction.y, m_direction.x) + glm::radians(90.0f);
}

Projectile::~Projectile()
{
    // Clean up OpenGL resources
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
}

void Projectile::update(float deltaTime)
{
    // Move in the direction
    m_position += m_direction * m_speed * deltaTime;

    // Update lifetime
    m_lifetime += deltaTime;
    if (m_lifetime >= m_maxLifetime) {
        setActive(false);
    }
}

void Projectile::render(const Engine::Shader& shader)
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

    // Set color in shader (yellow for projectiles)
    shader.setVec3("color", glm::vec3(1.0f, 1.0f, 0.0f));

    // Bind VAO and draw
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void Projectile::initializeGeometry()
{
    // Create a small triangle
    float vertices[] = {
        // positions
         0.0f,  -0.5f, 0.0f,  // bottom
        -0.2f,   0.0f, 0.0f,  // middle left
         0.2f,   0.0f, 0.0f   // middle right
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

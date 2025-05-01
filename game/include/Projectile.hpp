#pragma once

#include "GameObject.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Game {

/**
 * @brief Projectile class for the top-down shooter game.
 *
 * This class represents a projectile fired by the player or enemies.
 */
class Projectile : public Engine::GameObject {
public:
    // Constructor and destructor
    Projectile(const std::string& name, const glm::vec2& position, const glm::vec2& direction);
    ~Projectile() override;

    // Game loop methods
    void update(float deltaTime) override;
    void render(const Engine::Shader& shader) override;

    // Projectile-specific methods
    void setDirection(const glm::vec2& direction) { m_direction = glm::normalize(direction); }
    const glm::vec2& getDirection() const { return m_direction; }

    void setSpeed(float speed) { m_speed = speed; }
    float getSpeed() const { return m_speed; }

private:
    // Initialize OpenGL geometry
    void initializeGeometry();

    // OpenGL objects
    GLuint m_vao;
    GLuint m_vbo;

    // Projectile properties
    glm::vec2 m_direction;
    float m_speed;
    float m_lifetime;
    float m_maxLifetime;
};

} // namespace Game

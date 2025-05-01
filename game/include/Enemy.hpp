#pragma once

#include "GameObject.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <memory>

namespace Game {

/**
 * @brief Enemy class for the top-down shooter game.
 *
 * This class represents an enemy character in the game.
 */
class Enemy : public Engine::GameObject {
public:
    // Constructor and destructor
    Enemy(const std::string& name, const glm::vec2& position);
    ~Enemy() override;

    // Game loop methods
    void update(float deltaTime) override;
    void render(const Engine::Shader& shader) override;

    // Enemy-specific methods
    void setTarget(std::shared_ptr<Engine::GameObject> target) { m_target = target; }
    std::shared_ptr<Engine::GameObject> getTarget() const { return m_target; }

    void setSpeed(float speed) { m_speed = speed; }
    float getSpeed() const { return m_speed; }

private:
    // Initialize OpenGL geometry
    void initializeGeometry();

    // OpenGL objects
    GLuint m_vao;
    GLuint m_vbo;

    // Enemy properties
    std::shared_ptr<Engine::GameObject> m_target;
    float m_speed;
    glm::vec3 m_color;
};

} // namespace Game

#pragma once

#include "GameObject.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Game {

/**
 * @brief Level class for the top-down shooter game.
 *
 * This class represents the game level/background.
 */
class Level : public Engine::GameObject {
public:
    // Constructor and destructor
    Level(const std::string& name, const glm::vec2& position);
    ~Level() override;

    // Game loop methods
    void update(float deltaTime) override;
    void render(const Engine::Shader& shader) override;

private:
    // Initialize OpenGL geometry
    void initializeGeometry();

    // OpenGL objects
    GLuint m_vao;
    GLuint m_vbo;

    // Level properties
    glm::vec3 m_backgroundColor;
    glm::vec3 m_gridColor;
    float m_gridSize;
};

} // namespace Game

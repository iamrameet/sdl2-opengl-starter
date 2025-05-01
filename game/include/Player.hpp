#pragma once

#include "GameObject.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Game {

class TopDownShooterGame;

/**
 * @brief Player class for the top-down shooter game.
 *
 * This class represents the player character in the game.
 */
class Player : public Engine::GameObject {
public:
    // Constructor and destructor
    Player(const std::string& name, const glm::vec2& position);
    ~Player() override;

    // Game loop methods
    void update(float deltaTime) override;
    void render(const Engine::Shader& shader) override;

    // Player-specific methods
    void setMoveDirection(const glm::vec2& direction) { m_moveDirection = direction; }
    const glm::vec2& getMoveDirection() const { return m_moveDirection; }

    void setShooting(bool shooting) { m_shooting = shooting; }
    bool isShooting() const { return m_shooting; }

    void setSpeed(float speed) { m_speed = speed; }
    float getSpeed() const { return m_speed; }

    void setFireRate(float fireRate) { m_fireRate = fireRate; }
    float getFireRate() const { return m_fireRate; }

    // Set the game reference
    void setGame(TopDownShooterGame* game) { m_game = game; }

private:
    // Initialize OpenGL geometry
    void initializeGeometry();

    // OpenGL objects
    GLuint m_vao;
    GLuint m_vbo;

    // Player properties
    glm::vec2 m_moveDirection;
    float m_speed;
    bool m_shooting;
    float m_fireRate;
    float m_fireTimer;

    // Reference to the game
    TopDownShooterGame* m_game;
};

} // namespace Game

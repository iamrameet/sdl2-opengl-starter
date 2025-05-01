#pragma once

#include "Application.hpp"
#include <memory>
#include <string>
#include <vector>

// Forward declarations
namespace Game {
    class Player;
    class Enemy;
    class Projectile;
    class Level;
}

/**
 * @brief Top-down shooter game implementation.
 *
 * This class implements a simple top-down shooter game using the engine.
 */
namespace Game {

class TopDownShooterGame : public Engine::Application {
public:
    // Constructor and destructor
    TopDownShooterGame(const std::string& title, int width, int height);
    ~TopDownShooterGame() override;

    // Game lifecycle methods that override the base class
    bool initialize() override;
    void shutdown() override;

    // Game-specific methods
    void spawnEnemy(const glm::vec2& position);
    void fireProjectile(const glm::vec2& position, const glm::vec2& direction);
    void handleCollisions();
    void updateScore(int points);
    int getScore() const { return m_score; }
    int getLives() const { return m_lives; }
    void loseLife();

private:
    // Override base class methods
    void processInput() override;
    void update(float deltaTime) override;
    void initializeGameObjects() override;

    // Helper methods for collision detection
    bool checkCollision(std::shared_ptr<Engine::GameObject> a, std::shared_ptr<Engine::GameObject> b);
    bool isOffScreen(std::shared_ptr<Engine::GameObject> obj);

    // Game-specific objects
    std::shared_ptr<Player> m_player;
    std::vector<std::shared_ptr<Enemy>> m_enemies;
    std::vector<std::shared_ptr<Projectile>> m_projectiles;
    std::shared_ptr<Level> m_currentLevel;

    // Game state
    int m_score;
    int m_lives;
    float m_enemySpawnTimer;
    float m_enemySpawnInterval;
    bool m_gameOver;

    // Input state
    bool m_moveUp;
    bool m_moveDown;
    bool m_moveLeft;
    bool m_moveRight;
    bool m_shooting;
};

} // namespace Game

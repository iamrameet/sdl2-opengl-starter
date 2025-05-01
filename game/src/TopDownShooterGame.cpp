#include "TopDownShooterGame.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

// Include game object headers
#include "Player.hpp"
#include "Enemy.hpp"
#include "Projectile.hpp"
#include "Level.hpp"
#include "Shader.hpp"
#include "UISystem.hpp"

namespace Game {

TopDownShooterGame::TopDownShooterGame(const std::string& title, int width, int height)
    : Engine::Application(title, width, height)
    , m_score(0)
    , m_lives(3)
    , m_enemySpawnTimer(0.0f)
    , m_enemySpawnInterval(2.0f)
    , m_gameOver(false)
    , m_moveUp(false)
    , m_moveDown(false)
    , m_moveLeft(false)
    , m_moveRight(false)
    , m_shooting(false)
{
}

TopDownShooterGame::~TopDownShooterGame()
{
    shutdown();
}

bool TopDownShooterGame::initialize()
{
    // Call the base class initialize method
    if (!Engine::Application::initialize()) {
        return false;
    }

    std::cout << "Top-Down Shooter Game initialized!" << std::endl;
    return true;
}

void TopDownShooterGame::shutdown()
{
    // Clear game-specific objects
    m_player.reset();
    m_enemies.clear();
    m_projectiles.clear();
    m_currentLevel.reset();

    // Call the base class shutdown method
    Engine::Application::shutdown();
}

void TopDownShooterGame::processInput()
{
    // Reset movement flags
    m_moveUp = false;
    m_moveDown = false;
    m_moveLeft = false;
    m_moveRight = false;
    m_shooting = false;

    // Check for quit events and key presses
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        // User requests quit
        if (e.type == SDL_QUIT) {
            quit();
        }
        // Key down events
        else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    quit();
                    break;
                case SDLK_w:
                case SDLK_UP:
                    m_moveUp = true;
                    break;
                case SDLK_s:
                case SDLK_DOWN:
                    m_moveDown = true;
                    break;
                case SDLK_a:
                case SDLK_LEFT:
                    m_moveLeft = true;
                    break;
                case SDLK_d:
                case SDLK_RIGHT:
                    m_moveRight = true;
                    break;
                case SDLK_SPACE:
                    m_shooting = true;
                    break;
            }
        }
        // Key up events
        else if (e.type == SDL_KEYUP) {
            switch (e.key.keysym.sym) {
                case SDLK_w:
                case SDLK_UP:
                    m_moveUp = false;
                    break;
                case SDLK_s:
                case SDLK_DOWN:
                    m_moveDown = false;
                    break;
                case SDLK_a:
                case SDLK_LEFT:
                    m_moveLeft = false;
                    break;
                case SDLK_d:
                case SDLK_RIGHT:
                    m_moveRight = false;
                    break;
                case SDLK_SPACE:
                    m_shooting = false;
                    break;
            }
        }
        // Mouse button events
        else if (e.type == SDL_MOUSEBUTTONDOWN) {
            if (e.button.button == SDL_BUTTON_LEFT) {
                m_shooting = true;
            }
        }
        else if (e.type == SDL_MOUSEBUTTONUP) {
            if (e.button.button == SDL_BUTTON_LEFT) {
                m_shooting = false;
            }
        }
    }

    // Get keyboard state for continuous input
    const Uint8* keyState = SDL_GetKeyboardState(NULL);
    if (keyState[SDL_SCANCODE_W] || keyState[SDL_SCANCODE_UP]) m_moveUp = true;
    if (keyState[SDL_SCANCODE_S] || keyState[SDL_SCANCODE_DOWN]) m_moveDown = true;
    if (keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_LEFT]) m_moveLeft = true;
    if (keyState[SDL_SCANCODE_D] || keyState[SDL_SCANCODE_RIGHT]) m_moveRight = true;
    if (keyState[SDL_SCANCODE_SPACE]) m_shooting = true;

    // Update player movement based on input
    if (m_player) {
        glm::vec2 moveDirection(0.0f);
        if (m_moveUp) moveDirection.y -= 1.0f;
        if (m_moveDown) moveDirection.y += 1.0f;
        if (m_moveLeft) moveDirection.x -= 1.0f;
        if (m_moveRight) moveDirection.x += 1.0f;

        // Normalize if moving diagonally
        if (glm::length(moveDirection) > 0.0f) {
            moveDirection = glm::normalize(moveDirection);
        }

        m_player->setMoveDirection(moveDirection);
        m_player->setShooting(m_shooting);
    }
}

void TopDownShooterGame::update(float deltaTime)
{
    // Don't update if game is over
    if (m_gameOver) {
        return;
    }

    // Update enemy spawn timer
    m_enemySpawnTimer += deltaTime;
    if (m_enemySpawnTimer >= m_enemySpawnInterval) {
        m_enemySpawnTimer = 0.0f;

        // Spawn enemy at random position along the edges
        float x, y;
        int side = rand() % 4; // 0: top, 1: right, 2: bottom, 3: left

        switch (side) {
            case 0: // top
                x = rand() % getWidth();
                y = 0;
                break;
            case 1: // right
                x = getWidth();
                y = rand() % getHeight();
                break;
            case 2: // bottom
                x = rand() % getWidth();
                y = getHeight();
                break;
            case 3: // left
                x = 0;
                y = rand() % getHeight();
                break;
        }

        spawnEnemy(glm::vec2(x, y));
    }

    // Update all game objects
    Engine::Application::update(deltaTime);

    // Handle collisions
    handleCollisions();

    // Check for game over condition
    if (m_lives <= 0) {
        m_gameOver = true;
        std::cout << "Game Over! Final Score: " << m_score << std::endl;
    }
}

void TopDownShooterGame::initializeGameObjects()
{
    // Create the player in the center of the screen
    m_player = std::make_shared<Player>("Player", glm::vec2(getWidth() / 2.0f, getHeight() / 2.0f));
    m_player->setScale(glm::vec2(30.0f, 30.0f));
    addGameObject(m_player);

    // Create the level
    m_currentLevel = std::make_shared<Level>("Level1", glm::vec2(0.0f, 0.0f));
    m_currentLevel->setScale(glm::vec2(getWidth(), getHeight()));
    addGameObject(m_currentLevel);

    std::cout << "Top-Down Shooter Game objects initialized" << std::endl;
}

void TopDownShooterGame::spawnEnemy(const glm::vec2& position)
{
    // Create a new enemy
    auto enemy = std::make_shared<Enemy>("Enemy" + std::to_string(m_enemies.size()), position);
    enemy->setScale(glm::vec2(25.0f, 25.0f));

    // Set the target to the player
    if (m_player) {
        enemy->setTarget(m_player);
    }

    // Add to game objects and enemy list
    addGameObject(enemy);
    m_enemies.push_back(enemy);
}

void TopDownShooterGame::fireProjectile(const glm::vec2& position, const glm::vec2& direction)
{
    // Create a new projectile
    auto projectile = std::make_shared<Projectile>(
        "Projectile" + std::to_string(m_projectiles.size()),
        position,
        direction
    );
    projectile->setScale(glm::vec2(10.0f, 10.0f));

    // Add to game objects and projectile list
    addGameObject(projectile);
    m_projectiles.push_back(projectile);
}

void TopDownShooterGame::handleCollisions()
{
    // Check for collisions between projectiles and enemies
    auto projectileIt = m_projectiles.begin();
    while (projectileIt != m_projectiles.end()) {
        bool projectileHit = false;

        // Check collision with enemies
        auto enemyIt = m_enemies.begin();
        while (enemyIt != m_enemies.end()) {
            if (checkCollision(*projectileIt, *enemyIt)) {
                // Remove enemy
                removeGameObject((*enemyIt)->getName());
                enemyIt = m_enemies.erase(enemyIt);

                // Mark projectile as hit
                projectileHit = true;

                // Increase score
                updateScore(100);
                break;
            } else {
                ++enemyIt;
            }
        }

        // Remove projectile if it hit something or went off-screen
        if (projectileHit || isOffScreen(*projectileIt)) {
            removeGameObject((*projectileIt)->getName());
            projectileIt = m_projectiles.erase(projectileIt);
        } else {
            ++projectileIt;
        }
    }

    // Check for collisions between player and enemies
    if (m_player) {
        auto enemyIt = m_enemies.begin();
        while (enemyIt != m_enemies.end()) {
            if (checkCollision(m_player, *enemyIt)) {
                // Remove enemy
                removeGameObject((*enemyIt)->getName());
                enemyIt = m_enemies.erase(enemyIt);

                // Player loses a life
                loseLife();
            } else {
                ++enemyIt;
            }
        }
    }
}

void TopDownShooterGame::updateScore(int points)
{
    m_score += points;
    std::cout << "Score: " << m_score << std::endl;
}

void TopDownShooterGame::loseLife()
{
    m_lives--;
    std::cout << "Lives remaining: " << m_lives << std::endl;
}

bool TopDownShooterGame::checkCollision(std::shared_ptr<Engine::GameObject> a, std::shared_ptr<Engine::GameObject> b)
{
    // Simple circle-circle collision detection
    float distance = glm::distance(a->getPosition(), b->getPosition());
    float radiusA = a->getScale().x / 2.0f;
    float radiusB = b->getScale().x / 2.0f;

    return distance < (radiusA + radiusB);
}

bool TopDownShooterGame::isOffScreen(std::shared_ptr<Engine::GameObject> obj)
{
    glm::vec2 pos = obj->getPosition();
    float radius = obj->getScale().x / 2.0f;

    return (pos.x + radius < 0 ||
            pos.x - radius > getWidth() ||
            pos.y + radius < 0 ||
            pos.y - radius > getHeight());
}

} // namespace Game

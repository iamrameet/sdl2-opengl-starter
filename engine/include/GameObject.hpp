#pragma once

#include <glm/glm.hpp>
#include <string>

namespace Engine {

// Forward declarations
class Shader;

/**
 * @brief Base class for all game objects.
 *
 * This class provides the foundation for creating game objects with
 * position, rotation, scale, and basic rendering capabilities.
 */
class GameObject {
public:
    GameObject(const std::string& name, const glm::vec2& position);
    virtual ~GameObject() = default;

    // Game loop methods
    virtual void update(float deltaTime);
    virtual void render(const Shader& shader);

    // Getters and setters
    const std::string& getName() const { return m_name; }
    void setName(const std::string& name) { m_name = name; }

    const glm::vec2& getPosition() const { return m_position; }
    void setPosition(const glm::vec2& position) { m_position = position; }
    void setPosition(const glm::vec3& position) { m_position = glm::vec2(position.x, position.y); }

    float getRotation() const { return m_rotation; }
    void setRotation(float rotation) { m_rotation = rotation; }

    const glm::vec2& getScale() const { return m_scale; }
    void setScale(const glm::vec2& scale) { m_scale = scale; }
    void setScale(const glm::vec3& scale) { m_scale = glm::vec2(scale.x, scale.y); }

    bool isActive() const { return m_active; }
    void setActive(bool active) { m_active = active; }

protected:
    std::string m_name;
    glm::vec2 m_position;
    float m_rotation;  // in radians
    glm::vec2 m_scale;
    bool m_active;
};

} // namespace Engine

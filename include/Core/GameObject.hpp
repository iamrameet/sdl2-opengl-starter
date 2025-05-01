#pragma once

#include <glm/glm.hpp>
#include <string>

// Forward declarations
class Shader;

class GameObject {
public:
    GameObject(const std::string& name, const glm::vec2& position);
    virtual ~GameObject() = default;

    // Game loop methods
    virtual void Update(float deltaTime);
    virtual void Render(const Shader& shader);

    // Getters and setters
    const std::string& GetName() const { return m_name; }
    void SetName(const std::string& name) { m_name = name; }

    const glm::vec2& GetPosition() const { return m_position; }
    void SetPosition(const glm::vec2& position) { m_position = position; }
    void SetPosition(const glm::vec3& position) { m_position = glm::vec2(position.x, position.y); }

    float GetRotation() const { return m_rotation; }
    void SetRotation(float rotation) { m_rotation = rotation; }

    const glm::vec2& GetScale() const { return m_scale; }
    void SetScale(const glm::vec2& scale) { m_scale = scale; }
    void SetScale(const glm::vec3& scale) { m_scale = glm::vec2(scale.x, scale.y); }

    bool IsActive() const { return m_active; }
    void SetActive(bool active) { m_active = active; }

protected:
    std::string m_name;
    glm::vec2 m_position;
    float m_rotation;  // in radians
    glm::vec2 m_scale;
    bool m_active;
};

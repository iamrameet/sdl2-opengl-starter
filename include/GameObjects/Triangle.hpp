#pragma once

#include "../Core/GameObject.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>

class Triangle : public GameObject {
public:
    // Default constructor
    Triangle();
    // Parameterized constructor
    Triangle(const std::string& name, const glm::vec2& position, const glm::vec3& color);
    ~Triangle() override;

    // Game loop methods
    void Update(float deltaTime) override;
    void Render(const Shader& shader) override;

    // Getters and setters
    const glm::vec3& GetColor() const { return m_color; }
    void SetColor(const glm::vec3& color) { m_color = color; }

private:
    // Initialize OpenGL geometry
    void InitializeGeometry();

    // OpenGL objects
    GLuint m_vao;
    GLuint m_vbo;

    // Triangle properties
    glm::vec3 m_color;

    // Animation properties
    float m_animTime;
};

#include "GameObjects/Triangle.hpp"
#include "Graphics/Shader.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <iostream>

Triangle::Triangle()
    : GameObject("Triangle", glm::vec2(0.0f, 0.0f))
    , m_vao(0)
    , m_vbo(0)
    , m_color(glm::vec3(1.0f, 1.0f, 1.0f))
    , m_animTime(0.0f)
{
    InitializeGeometry();
}

Triangle::Triangle(const std::string& name, const glm::vec2& position, const glm::vec3& color)
    : GameObject(name, position)
    , m_vao(0)
    , m_vbo(0)
    , m_color(color)
    , m_animTime(0.0f)
{
    InitializeGeometry();
}

void Triangle::InitializeGeometry()
{
    // Set up vertex data (much larger triangle)
    float vertices[] = {
        // positions
        -50.0f, -50.0f, 0.0f,  // bottom left
         50.0f, -50.0f, 0.0f,  // bottom right
          0.0f,  50.0f, 0.0f   // top
    };

    // Create VAO and VBO
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    // Bind the Vertex Array Object first, then bind and set vertex buffer(s)
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    std::cout << "Triangle geometry initialized" << std::endl;
}

Triangle::~Triangle()
{
    // Clean up OpenGL objects
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
}

void Triangle::Update(float deltaTime)
{
    // Update animation time
    m_animTime += deltaTime;

    // Animate rotation
    m_rotation = m_animTime * 0.5f;

    // Animate scale (but keep it large enough to be visible)
    float scale = 0.2f * std::sin(m_animTime) + 1.0f;
    m_scale = glm::vec2(scale, scale);
}

void Triangle::Render(const Shader& shader)
{
    if (!m_active) {
        return;
    }

    // Call base class to set up transformation
    GameObject::Render(shader);

    // Set color uniform with full opacity
    shader.SetVec3("color", m_color);
    shader.SetFloat("globalAlpha", 1.0f);

    // Draw the triangle
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // Print debug info
    std::cout << "Rendering triangle at position (" << m_position.x << ", " << m_position.y
              << ") with color (" << m_color.r << ", " << m_color.g << ", " << m_color.b << ")" << std::endl;
}

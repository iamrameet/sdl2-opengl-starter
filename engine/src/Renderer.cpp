#include "Renderer.hpp"
#include "Shader.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace Engine {

Renderer::Renderer()
    : m_width(0)
    , m_height(0)
    , m_shader(nullptr)
    , m_transform(1.0f)
    , m_globalAlpha(1.0f)
    , m_rectVAO(0)
    , m_rectVBO(0)
{
}

Renderer::~Renderer() {
    shutdown();
}

bool Renderer::initialize(int width, int height) {
    m_width = width;
    m_height = height;

    // Create a VAO and VBO for rendering rectangles
    glGenVertexArrays(1, &m_rectVAO);
    glGenBuffers(1, &m_rectVBO);

    glBindVertexArray(m_rectVAO);

    // Rectangle vertices (x, y, z)
    float vertices[] = {
        0.0f, 0.0f, 0.1f,          // bottom left
        1.0f, 0.0f, 0.1f,          // bottom right
        1.0f, 1.0f, 0.1f,          // top right
        0.0f, 0.0f, 0.1f,          // bottom left
        1.0f, 1.0f, 0.1f,          // top right
        0.0f, 1.0f, 0.1f           // top left
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_rectVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return true;
}

void Renderer::shutdown() {
    if (m_rectVAO) {
        glDeleteVertexArrays(1, &m_rectVAO);
        m_rectVAO = 0;
    }

    if (m_rectVBO) {
        glDeleteBuffers(1, &m_rectVBO);
        m_rectVBO = 0;
    }
}

void Renderer::beginFrame() {
    // Clear the screen with both color and depth buffers
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable depth testing for proper layering
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    // Enable blending for transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Reset the transformation matrix
    m_transform = glm::mat4(1.0f);

    // Reset the global alpha
    m_globalAlpha = 1.0f;
}

void Renderer::endFrame() {
    // Make sure all drawing commands are submitted
    glFlush();
}

void Renderer::setShader(std::shared_ptr<Shader> shader) {
    m_shader = shader;
    if (m_shader) {
        m_shader->use();
    }
}

std::shared_ptr<Shader> Renderer::getShader() const {
    return m_shader;
}

void Renderer::drawRect(int x, int y, int width, int height, const glm::vec3& color) {
    if (!m_shader) {
        std::cerr << "No shader set for rendering" << std::endl;
        return;
    }

    // Use a static depth value that decreases with each draw call
    // This ensures consistent rendering order
    static float depth = 0.9f;
    depth -= 0.0001f;
    if (depth < 0.1f) depth = 0.9f; // Reset when we get too close to the camera

    // Set up transformation
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(x, y, depth));
    model = glm::scale(model, glm::vec3(width, height, 1.0f));

    // Apply the current transformation
    model = m_transform * model;

    // Set up projection
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_width), static_cast<float>(m_height), 0.0f, -1.0f, 1.0f);

    // Set uniforms
    glm::mat4 mvp = projection * model;
    m_shader->setMat4("model", mvp);
    m_shader->setVec3("color", color);
    m_shader->setFloat("globalAlpha", m_globalAlpha);

    // Draw the rectangle
    glBindVertexArray(m_rectVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Renderer::drawText(const std::string& text, int x, int y, float scale, const glm::vec3& color) {
    // Simple text rendering using rectangles
    // In a real application, you would use a font rendering library
    int charWidth = static_cast<int>(8 * scale);
    int charHeight = static_cast<int>(16 * scale);
    int spacing = static_cast<int>(2 * scale);

    for (size_t i = 0; i < text.length(); i++) {
        // Draw a rectangle for each character
        drawRect(x + i * (charWidth + spacing), y, charWidth, charHeight, color);
    }
}

void Renderer::setGlobalAlpha(float alpha) {
    m_globalAlpha = glm::clamp(alpha, 0.0f, 1.0f);
}

float Renderer::getGlobalAlpha() const {
    return m_globalAlpha;
}

void Renderer::setTransform(const glm::mat4& transform) {
    m_transform = transform;
}

const glm::mat4& Renderer::getTransform() const {
    return m_transform;
}

} // namespace Engine

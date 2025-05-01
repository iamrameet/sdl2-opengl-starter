#include "Graphics/Renderer.hpp"
#include "Graphics/Shader.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

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
    Shutdown();
}

bool Renderer::Initialize(int width, int height) {
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    // Enable blending for transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Enable depth testing for proper layering
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    // Disable face culling to render both sides of polygons
    glDisable(GL_CULL_FACE);

    return true;
}

void Renderer::Shutdown() {
    if (m_rectVAO != 0) {
        glDeleteVertexArrays(1, &m_rectVAO);
        m_rectVAO = 0;
    }

    if (m_rectVBO != 0) {
        glDeleteBuffers(1, &m_rectVBO);
        m_rectVBO = 0;
    }
}

void Renderer::BeginFrame() {
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

    std::cout << "Begin frame - cleared screen" << std::endl;
}

void Renderer::EndFrame() {
    // Make sure all drawing commands are submitted
    glFlush();
}

void Renderer::SetShader(std::shared_ptr<Shader> shader) {
    m_shader = shader;
    if (m_shader) {
        m_shader->Use();
    }
}

std::shared_ptr<Shader> Renderer::GetShader() const {
    return m_shader;
}

void Renderer::DrawRect(int x, int y, int width, int height, const glm::vec3& color) {
    if (!m_shader) {
        std::cerr << "No shader set for rendering" << std::endl;
        return;
    }

    // Use a static depth value that decreases with each draw call
    // This ensures consistent rendering order
    static float depth = 0.9f;
    depth -= 0.0001f;
    if (depth < 0.1f) depth = 0.9f; // Reset when we get too close to the camera

    std::cout << "Drawing rectangle at (" << x << ", " << y << ") with size (" << width << ", " << height << ")" << std::endl;

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
    m_shader->SetMat4("model", mvp);
    m_shader->SetVec3("color", color);
    m_shader->SetFloat("globalAlpha", m_globalAlpha);

    // Draw the rectangle
    glBindVertexArray(m_rectVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Renderer::DrawText(const std::string& text, int x, int y, float scale, const glm::vec3& color) {
    // Calculate text width (approximate)
    int textWidth = static_cast<int>(text.length() * 15 * scale);
    int textHeight = static_cast<int>(30 * scale);

    // Save current global alpha
    float savedAlpha = m_globalAlpha;

    // Draw a solid black background for better contrast
    m_globalAlpha = 1.0f;
    DrawRect(x - 2, y - 2, textWidth + 4, textHeight + 4, glm::vec3(0.0f, 0.0f, 0.0f));

    // Draw a colored background
    m_globalAlpha = 0.9f;
    DrawRect(x, y, textWidth, textHeight, glm::vec3(0.2f, 0.2f, 0.3f));

    // Draw individual character rectangles with full opacity
    m_globalAlpha = 1.0f;
    for (size_t i = 0; i < text.length(); i++) {
        int charX = x + static_cast<int>(i * 15 * scale);
        int charWidth = static_cast<int>(10 * scale);
        int charHeight = static_cast<int>(20 * scale);
        int charY = y + (textHeight - charHeight) / 2; // Center vertically

        // Draw the character as a small rectangle with the specified color (or white for better visibility)
        DrawRect(charX, charY, charWidth, charHeight, glm::vec3(1.0f, 1.0f, 0.0f)); // Bright yellow for visibility
    }

    // Restore original alpha
    m_globalAlpha = savedAlpha;

    // For debugging, print the text to the console
    std::cout << "Rendering text: " << text << " at position (" << x << ", " << y << ")" << std::endl;
}

void Renderer::SetGlobalAlpha(float alpha) {
    m_globalAlpha = alpha;
}

float Renderer::GetGlobalAlpha() const {
    return m_globalAlpha;
}

void Renderer::SetTransform(const glm::mat4& transform) {
    m_transform = transform;
}

const glm::mat4& Renderer::GetTransform() const {
    return m_transform;
}

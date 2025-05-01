#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <memory>

namespace Engine {

// Forward declarations
class Shader;

/**
 * @brief Renderer class for handling OpenGL rendering.
 *
 * This class provides methods for rendering primitives and managing the render state.
 */
class Renderer {
public:
    Renderer();
    ~Renderer();

    // Initialize the renderer
    bool initialize(int width, int height);

    // Shutdown the renderer
    void shutdown();

    // Begin rendering a frame
    void beginFrame();

    // End rendering a frame
    void endFrame();

    // Set the current shader
    void setShader(std::shared_ptr<Shader> shader);

    // Get the current shader
    std::shared_ptr<Shader> getShader() const;

    // Draw a colored rectangle
    void drawRect(int x, int y, int width, int height, const glm::vec3& color);

    // Draw text (simplified as colored rectangles for now)
    void drawText(const std::string& text, int x, int y, float scale, const glm::vec3& color);

    // Set the global alpha value
    void setGlobalAlpha(float alpha);

    // Get the global alpha value
    float getGlobalAlpha() const;

    // Set the current transformation matrix
    void setTransform(const glm::mat4& transform);

    // Get the current transformation matrix
    const glm::mat4& getTransform() const;

    // Get the window dimensions
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

private:
    int m_width;
    int m_height;
    std::shared_ptr<Shader> m_shader;
    glm::mat4 m_transform;
    float m_globalAlpha;

    // OpenGL objects
    GLuint m_rectVAO;
    GLuint m_rectVBO;
};

} // namespace Engine

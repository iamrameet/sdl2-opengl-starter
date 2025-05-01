#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <memory>

class Shader;

class Renderer {
public:
    Renderer();
    ~Renderer();

    // Initialize the renderer
    bool Initialize(int width, int height);
    
    // Shutdown the renderer
    void Shutdown();
    
    // Begin rendering a frame
    void BeginFrame();
    
    // End rendering a frame
    void EndFrame();
    
    // Set the current shader
    void SetShader(std::shared_ptr<Shader> shader);
    
    // Get the current shader
    std::shared_ptr<Shader> GetShader() const;
    
    // Draw a colored rectangle
    void DrawRect(int x, int y, int width, int height, const glm::vec3& color);
    
    // Draw text (simplified as colored rectangles for now)
    void DrawText(const std::string& text, int x, int y, float scale, const glm::vec3& color);
    
    // Set the global alpha value
    void SetGlobalAlpha(float alpha);
    
    // Get the global alpha value
    float GetGlobalAlpha() const;
    
    // Set the current transformation matrix
    void SetTransform(const glm::mat4& transform);
    
    // Get the current transformation matrix
    const glm::mat4& GetTransform() const;
    
    // Get the window dimensions
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }

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

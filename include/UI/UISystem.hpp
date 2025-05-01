#pragma once

#include <string>
#include <memory>
#include <glm/glm.hpp>

class Renderer;

class UISystem {
public:
    UISystem();
    ~UISystem();

    // Initialize the UI system
    bool Initialize(std::shared_ptr<Renderer> renderer);
    
    // Shutdown the UI system
    void Shutdown();
    
    // Render text
    void RenderText(const std::string& text, int x, int y, float scale, const glm::vec3& color);
    
    // Render a button
    void RenderButton(const std::string& text, int x, int y, int width, int height, const glm::vec3& color, bool selected);
    
    // Render a progress bar
    void RenderProgressBar(int x, int y, int width, int height, float progress, const glm::vec3& backgroundColor, const glm::vec3& fillColor);
    
    // Check if a point is inside a rectangle
    bool IsPointInRect(int pointX, int pointY, int rectX, int rectY, int rectWidth, int rectHeight) const;

private:
    std::shared_ptr<Renderer> m_renderer;
};

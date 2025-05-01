#pragma once

#include <string>
#include <memory>
#include <glm/glm.hpp>

namespace Engine {

// Forward declarations
class Renderer;

/**
 * @brief UI system for rendering user interface elements.
 *
 * This class provides methods for rendering text, buttons, and other UI elements.
 */
class UISystem {
public:
    UISystem();
    ~UISystem();

    // Initialize the UI system
    bool initialize(std::shared_ptr<Renderer> renderer);

    // Shutdown the UI system
    void shutdown();

    // Render text
    void renderText(const std::string& text, int x, int y, float scale, const glm::vec3& color);

    // Render a button
    void renderButton(const std::string& text, int x, int y, int width, int height, const glm::vec3& color, bool selected);

    // Render a progress bar
    void renderProgressBar(int x, int y, int width, int height, float progress, const glm::vec3& backgroundColor, const glm::vec3& fillColor);

    // Check if a point is inside a rectangle
    bool isPointInRect(int pointX, int pointY, int rectX, int rectY, int rectWidth, int rectHeight) const;

private:
    std::shared_ptr<Renderer> m_renderer;
};

} // namespace Engine

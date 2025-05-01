#include "UI/UISystem.hpp"
#include "Graphics/Renderer.hpp"
#include <iostream>

UISystem::UISystem()
    : m_renderer(nullptr)
{
}

UISystem::~UISystem() {
    Shutdown();
}

bool UISystem::Initialize(std::shared_ptr<Renderer> renderer) {
    m_renderer = renderer;
    return true;
}

void UISystem::Shutdown() {
    m_renderer = nullptr;
}

void UISystem::RenderText(const std::string& text, int x, int y, float scale, const glm::vec3& color) {
    if (!m_renderer) {
        return;
    }

    // Draw text using the renderer
    m_renderer->DrawText(text, x, y, scale, color);

    // For debugging, print the text to the console
    std::cout << "Rendering text: " << text << " at position (" << x << ", " << y << ")" << std::endl;
}

void UISystem::RenderButton(const std::string& text, int x, int y, int width, int height, const glm::vec3& color, bool selected) {
    if (!m_renderer) {
        return;
    }

    // Save current global alpha
    float savedAlpha = m_renderer->GetGlobalAlpha();

    // Draw outer glow for selected buttons
    if (selected) {
        m_renderer->SetGlobalAlpha(0.7f);
        int glowSize = 5;
        m_renderer->DrawRect(x - glowSize, y - glowSize, width + 2 * glowSize, height + 2 * glowSize, glm::vec3(1.0f, 1.0f, 0.0f));
    }

    // Draw button outline with full opacity
    m_renderer->SetGlobalAlpha(1.0f);
    int outlineSize = 3;
    m_renderer->DrawRect(x - outlineSize, y - outlineSize, width + 2 * outlineSize, height + 2 * outlineSize, glm::vec3(0.0f, 0.0f, 0.0f));

    // Draw button background with full opacity
    m_renderer->SetGlobalAlpha(1.0f);
    glm::vec3 buttonColor = selected ? glm::vec3(0.8f, 0.8f, 0.2f) : color; // Bright yellow when selected
    m_renderer->DrawRect(x, y, width, height, buttonColor);

    // Draw button text with full opacity
    m_renderer->SetGlobalAlpha(1.0f);
    int textX = x + (width - static_cast<int>(text.length() * 15)) / 2;
    int textY = y + (height - 30) / 2;

    // Use contrasting text color based on button color
    glm::vec3 textColor = selected ? glm::vec3(0.0f, 0.0f, 0.0f) : glm::vec3(1.0f, 1.0f, 1.0f);
    RenderText(text, textX, textY, 1.0f, textColor);

    // Restore original alpha
    m_renderer->SetGlobalAlpha(savedAlpha);

    std::cout << "Rendering button: " << text << " at position (" << x << ", " << y << "), selected: " << (selected ? "true" : "false") << std::endl;
}

void UISystem::RenderProgressBar(int x, int y, int width, int height, float progress, const glm::vec3& backgroundColor, const glm::vec3& fillColor) {
    if (!m_renderer) {
        return;
    }

    // Save current global alpha
    float savedAlpha = m_renderer->GetGlobalAlpha();

    // Draw outer border for better visibility
    m_renderer->SetGlobalAlpha(1.0f);
    m_renderer->DrawRect(x - 2, y - 2, width + 4, height + 4, glm::vec3(1.0f, 1.0f, 1.0f));

    // Draw background with full opacity
    m_renderer->SetGlobalAlpha(1.0f);
    m_renderer->DrawRect(x, y, width, height, backgroundColor);

    // Draw fill with full opacity and a bright color
    m_renderer->SetGlobalAlpha(1.0f);
    int fillWidth = static_cast<int>(width * progress);
    if (fillWidth > 0) {
        m_renderer->DrawRect(x, y, fillWidth, height, glm::vec3(0.0f, 1.0f, 0.0f)); // Bright green
    }

    // Add a pulsing effect to the progress bar
    static float pulseAlpha = 0.0f;
    static float pulseDir = 0.05f;
    pulseAlpha += pulseDir;
    if (pulseAlpha > 1.0f || pulseAlpha < 0.0f) {
        pulseDir = -pulseDir;
        pulseAlpha = std::max(0.0f, std::min(1.0f, pulseAlpha));
    }

    // Draw a highlight line on top of the fill
    m_renderer->SetGlobalAlpha(pulseAlpha);
    if (fillWidth > 2) {
        m_renderer->DrawRect(x, y, fillWidth, 2, glm::vec3(1.0f, 1.0f, 1.0f));
    }

    // Restore original alpha
    m_renderer->SetGlobalAlpha(savedAlpha);

    std::cout << "Rendering progress bar at (" << x << ", " << y << ") with progress: " << progress * 100.0f << "%" << std::endl;
}

bool UISystem::IsPointInRect(int pointX, int pointY, int rectX, int rectY, int rectWidth, int rectHeight) const {
    return (pointX >= rectX && pointX <= rectX + rectWidth && pointY >= rectY && pointY <= rectY + rectHeight);
}

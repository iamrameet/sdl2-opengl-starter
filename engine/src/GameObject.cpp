#include "GameObject.hpp"
#include "Shader.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Engine {

GameObject::GameObject(const std::string& name, const glm::vec2& position)
    : m_name(name)
    , m_position(position)
    , m_rotation(0.0f)
    , m_scale(1.0f, 1.0f)
    , m_active(true)
{
}

void GameObject::update(float deltaTime)
{
    // Base implementation does nothing
    // Derived classes will override this
}

void GameObject::render(const Shader& shader)
{
    if (!m_active) {
        return;
    }

    // Create transformation matrix
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(m_position, 0.0f));
    model = glm::rotate(model, m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(m_scale, 1.0f));

    // Set the transformation uniform
    // Note: The projection matrix is set in Application::render
    shader.setMat4("model", model);

    // Derived classes will override this to render their specific geometry
}

} // namespace Engine

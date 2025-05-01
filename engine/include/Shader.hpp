#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

namespace Engine {

/**
 * @brief Shader class for compiling and using GLSL shaders.
 *
 * This class handles loading, compiling, and using GLSL shaders.
 * It provides methods for setting uniform values in the shader.
 */
class Shader {
public:
    // Constructor and destructor
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    // Use/activate the shader
    void use() const;

    // Utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec2(const std::string& name, const glm::vec2& value) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setVec4(const std::string& name, const glm::vec4& value) const;
    void setMat2(const std::string& name, const glm::mat2& mat) const;
    void setMat3(const std::string& name, const glm::mat3& mat) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;

    // Get the shader program ID
    GLuint getID() const { return m_id; }

private:
    // Program ID
    GLuint m_id;

    // Uniform location cache
    mutable std::unordered_map<std::string, GLint> m_uniformLocationCache;

    // Helper functions
    std::string readFile(const std::string& filePath);
    void checkCompileErrors(GLuint shader, const std::string& type);
    GLint getUniformLocation(const std::string& name) const;
};

} // namespace Engine

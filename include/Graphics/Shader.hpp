#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

class Shader {
public:
    // Constructor and destructor
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    // Use/activate the shader
    void Use() const;

    // Utility uniform functions
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetVec2(const std::string& name, const glm::vec2& value) const;
    void SetVec3(const std::string& name, const glm::vec3& value) const;
    void SetVec4(const std::string& name, const glm::vec4& value) const;
    void SetMat2(const std::string& name, const glm::mat2& mat) const;
    void SetMat3(const std::string& name, const glm::mat3& mat) const;
    void SetMat4(const std::string& name, const glm::mat4& mat) const;

private:
    // Program ID
    GLuint m_id;

    // Uniform location cache
    mutable std::unordered_map<std::string, GLint> m_uniformLocationCache;

    // Helper functions
    std::string ReadFile(const std::string& filePath);
    void CheckCompileErrors(GLuint shader, const std::string& type);
    GLint GetUniformLocation(const std::string& name) const;
};

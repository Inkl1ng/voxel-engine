#pragma once

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader {
public:
    Shader(const std::string& vert_path, const std::string& frag_path);

    void use() const;

    void set_mat4(const std::string& name, glm::mat4 value) const;

private:
    GLuint m_program;
};


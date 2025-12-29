#include "Shader.hpp"

#include <cassert>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& vert_path, const std::string& frag_path)
{
    int success;
    char info_log[512];

    std::ifstream vert_file(vert_path);
    assert(vert_file.is_open() && "Failed to open vertex shader file");
    std::stringstream vert_stream;
    vert_stream << vert_file.rdbuf();
    std::string vert_string = vert_stream.str();
    const char* vert_char = vert_string.c_str();

    GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert_shader, 1, &vert_char, NULL);
    glCompileShader(vert_shader);
    glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vert_shader, 512, NULL, info_log);
        std::cerr << "Vertex shader compilation failed\n" << info_log << '\n';
    }

    std::ifstream frag_file(frag_path);
    assert(frag_file.is_open() && "Failed to open vertex shader file");
    std::stringstream frag_stream;
    frag_stream << frag_file.rdbuf();
    std::string frag_string = frag_stream.str();
    const char* frag_char = frag_string.c_str();

    GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shader, 1, &frag_char, NULL);
    glCompileShader(frag_shader);
    glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(frag_shader, 512, NULL, info_log);
        std::cerr << "Fragment shader compilation failed\n" << info_log << '\n';
    }

    m_program = glCreateProgram();
    glAttachShader(m_program, vert_shader);
    glAttachShader(m_program, frag_shader);
    glLinkProgram(m_program);
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_program, 512, NULL, info_log);
        std::cerr << "Program linkage failed\n" << info_log << '\n';
    }

    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);
}

void Shader::use() const
{
    glUseProgram(m_program);
}

void Shader::set_mat4(const std::string& name, glm::mat4 value) const
{
    glUniformMatrix4fv(
            glGetUniformLocation(m_program, name.c_str()),
            1, GL_FALSE,
            glm::value_ptr(value)
            );
}


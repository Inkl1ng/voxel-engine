#pragma once

#include <array>

#include <glad/glad.h>

#include "Block.hpp"

class Chunk {
public:
    Chunk();

    void draw() const;

private:
    constexpr static int chunk_size = 8;

    void generate_mesh();

    std::array<std::array<std::array<Block, chunk_size>, chunk_size>, chunk_size> m_blocks;

    GLuint m_VAO = 0;
    GLuint m_VBO = 0;
    int m_num_vertices = 0;
};


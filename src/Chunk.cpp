#include "Chunk.hpp"
#include "App.hpp"

#include <vector>

Chunk::Chunk()
{
    generate_mesh();
}

void Chunk::draw() const
{
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, m_num_vertices);
}

void Chunk::generate_mesh()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);

    m_num_vertices = 0;

    constexpr std::array<float, 18> pos_x_face = {
        1.0f, 0.0f, 1.0f, // BL
        1.0f, 0.0f, 0.0f, // BR
        1.0f, 1.0f, 0.0f, // TR

        1.0f, 0.0f, 1.0f, // BL
        1.0f, 1.0f, 0.0f, // TR
        1.0f, 1.0f, 1.0f, // TL
    };
    constexpr std::array<float, 18> neg_x_face = {
        0.0f, 0.0f, 0.0f, // BL
        0.0f, 0.0f, 1.0f, // BR
        0.0f, 1.0f, 1.0f, // TR

        0.0f, 0.0f, 0.0f, // BL
        0.0f, 1.0f, 1.0f, // TR
        0.0f, 1.0f, 0.0f, // TL
    };
    constexpr std::array<float, 18> pos_y_face = {
        0.0f, 1.0f, 0.0f, // BL
        0.0f, 1.0f, 1.0f, // BR
        1.0f, 1.0f, 1.0f, // TR

        0.0f, 1.0f, 0.0f, // BL
        1.0f, 1.0f, 1.0f, // TR
        1.0f, 1.0f, 0.0f, // TL
    };
    constexpr std::array<float, 18> neg_y_face = {
        0.0f, 0.0f, 1.0f, // BL
        0.0f, 0.0f, 0.0f, // BR
        1.0f, 0.0f, 0.0f, // TR

        0.0f, 0.0f, 1.0f, // BL
        1.0f, 0.0f, 0.0f, // TR
        1.0f, 0.0f, 1.0f, // TL
    };
    constexpr std::array<float, 18> pos_z_face = {
        0.0f, 0.0f, 1.0f, // BL
        1.0f, 0.0f, 1.0f, // BR
        1.0f, 1.0f, 1.0f, // TR

        0.0f, 0.0f, 1.0f, // BL
        1.0f, 1.0f, 1.0f, // TR
        0.0f, 1.0f, 1.0f, // TL
    };
    constexpr std::array<float, 18> neg_z_face = {
        1.0f, 0.0f, 0.0f, // BL
        0.0f, 0.0f, 0.0f, // BR
        0.0f, 1.0f, 0.0f, // TR

        1.0f, 0.0f, 0.0f, // BL
        0.0f, 1.0f, 0.0f, // TR
        1.0f, 1.0f, 0.0f, // TL
    };

    constexpr std::array<std::array<float, 18>, 6> faces = {
        pos_x_face, neg_x_face,
        pos_y_face, neg_y_face,
        pos_z_face, neg_z_face
    };

    std::vector<float> vertices;
    //float vertices[] = {
    //    0.5f, 0.5f, 0.0f,
    //    0.5f, -0.5f, 0.0f,
    //    -0.5f, -0.5f, 0.0f,
    //};
    
    for (const auto& face : faces) {
        for (auto vertex : face) {
            vertices.push_back(vertex);
            ++m_num_vertices;
        }
    }

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

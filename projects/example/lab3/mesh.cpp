#include "mesh.h"
#include <iostream>
#include <glm/glm.hpp>

Mesh::Mesh(Vertices vertexData)
{
    this->vertices = vertexData;
    createIndices(vertexData, indices);

    // VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // VBO
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vec4), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    // IBO
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    
    // Store and bind everything to VAO
    glEnableVertexAttribArray(0);

    // Unbind buffers
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::~Mesh() {}

// Checks if any vectors has the same coordinates. Returns a vector with indices
// to those vertices.
void createIndices(Vertices input, Indices &output)
{
    Indices indices;
    for (int i = 0; i < input.size(); i++)
    {
        bool vertexFound = false;
        for (int j = 0; j < i; j++)
        {
            // If same vector found, reuse that index
            if (input[i] == input[j])
            {
                indices.push_back(j);
                vertexFound = true;
                break;
            }
        }

        if (!vertexFound)
        {
            indices.push_back(i);
        }
        else
        {
            vertexFound = false;
        }
    }
    output = indices;
}
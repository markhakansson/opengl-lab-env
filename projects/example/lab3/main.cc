#include "types.h"
#include <iostream>

Indices createIndices(Vertices vertices)
{
    Indices indices;
    for (int i = 0; i < vertices.size(); i++)
    {   
        bool vertexFound = false;
        for (int j = 0; j < i; j++)
        {
            // If same vector found, reuse that index
            if (vertices[i] == vertices[j])
            {
                indices.push_back(j);
                vertexFound = true;
                break;
            }
        }

        if(!vertexFound)
        {
            indices.push_back(i);
        } 
        else 
        {
            vertexFound = false;
        }
    }
    return indices;
}

int main(int argc, const char **argv)
{
    Vertices vertices = {
        vec4(1, 0, 0, 0),
        vec4(1, 0, 0, 0),
        vec4(1, 1, 1, 1),
        vec4(0, 4, 2, 1),
        vec4(0, 4, 2, 1),
        vec4(0, 4, 2, 0)};
    Indices indices = createIndices(vertices);
    std::cout << "Indices size: " << indices.size() << std::endl;
    for (int i = 0; i < indices.size(); i++)
    {
        std::cout << indices[i] << std::endl;
    }
}
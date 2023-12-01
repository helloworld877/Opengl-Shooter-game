#pragma once

#include <glad/gl.h>
#include "vertex.hpp"

namespace our {

    #define ATTRIB_LOC_POSITION 0
    #define ATTRIB_LOC_COLOR    1
    #define ATTRIB_LOC_TEXCOORD 2
    #define ATTRIB_LOC_NORMAL   3

    class Mesh {
        // Here, we store the object names of the 3 main components of a mesh:
        // A vertex array object, A vertex buffer and an element buffer
        unsigned int VBO, EBO;
        unsigned int VAO;
        // We need to remember the number of elements that will be draw by glDrawElements 
        GLsizei elementCount;
    public:

        // The constructor takes two vectors:
        // - vertices which contain the vertex data.
        // - elements which contain the indices of the vertices out of which each rectangle will be constructed.
        // The mesh class does not keep a these data on the RAM. Instead, it should create
        // a vertex buffer to store the vertex data on the VRAM,
        // an element buffer to store the element data on the VRAM,
        // a vertex array object to define how to read the vertex & element buffer during rendering 
        Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& elements)
        {
            //TODO: (Req 2) Write this function
            // remember to store the number of elements in "elementCount" since you will need it for drawing
            // For the attribute locations, use the constants defined above: ATTRIB_LOC_POSITION, ATTRIB_LOC_COLOR, etc


            // Generates vertex array object names and  binds the vertex array object to the current OpenGL context.
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            //Generates buffer object names and binds the buffer object to the specified target (GL_ARRAY_BUFFER).
            //then it allocates and fills the buffer with data (vertex data).
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

            //Generates buffer object names and binds the buffer object to the specified target (GL_ARRAY_BUFFER)
            //then it allocates and fills the buffer with data (elements data), used for indexed rendering.
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size()*sizeof(unsigned int), elements.data(), GL_STATIC_DRAW);

            // for the ATTRIB_LOC_POSITION defined above, this specifies how the vertex attribute data is stored in  VBO
            glVertexAttribPointer(ATTRIB_LOC_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
            glEnableVertexAttribArray(ATTRIB_LOC_POSITION);

            
            // for the ATTRIB_LOC_COLOR defined above
            glVertexAttribPointer(ATTRIB_LOC_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
            glEnableVertexAttribArray(ATTRIB_LOC_COLOR);

            // for the ATTRIB_LOC_TEXCOORD defined above
            glVertexAttribPointer(ATTRIB_LOC_TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coord));
            glEnableVertexAttribArray(ATTRIB_LOC_TEXCOORD);

            // for the ATTRIB_LOC_NORMAL defined above
            glVertexAttribPointer(ATTRIB_LOC_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
            glEnableVertexAttribArray(ATTRIB_LOC_NORMAL);

            //unbind the vertex array object
            glBindVertexArray(0);

            // set the element count as specified
            this->elementCount = static_cast<GLsizei>(elements.size());
        }

        // this function should render the mesh
        void draw() 
        {
            //TODO: (Req 2) Write this function
            
            // bind VAO to set up vertex attributes pointers
            glBindVertexArray(this->VAO);

            //draw command
            glDrawElements(GL_TRIANGLES, this->elementCount,GL_UNSIGNED_INT, 0);

            //unbind VAO 
            glBindVertexArray(0);
        }

        // this function should delete the vertex & element buffers and the vertex array object
        ~Mesh(){
            //TODO: (Req 2) Write this function
            glDeleteVertexArrays(1, &VAO);

            glDeleteBuffers(1, &VBO);
            
            glDeleteBuffers(1, &EBO);
        }

        Mesh(Mesh const &) = delete;
        Mesh &operator=(Mesh const &) = delete;
    };

}
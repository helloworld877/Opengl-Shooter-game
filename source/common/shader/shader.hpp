#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace our
{

    class ShaderProgram
    {

    private:
        // Shader Program Handle (OpenGL object name)
        GLuint program;

    public:
        ShaderProgram()
        {
            // TODO: (Req 1) Create A shader program
            // DONE
            program = glCreateProgram();
        }
        ~ShaderProgram()
        {
            // TODO: (Req 1) Delete a shader program
            // DONE
            glDeleteProgram(program);
        }

        bool attach(const std::string &filename, GLenum type) const;

        bool link() const;

        void use()
        {
            glUseProgram(program);
        }

        GLuint getUniformLocation(const std::string &name)
        {
            // TODO: (Req 1) Return the location of the uniform with the given name
            // DONE
            return glGetUniformLocation(this->program, name.c_str());
        }

        void set(const std::string &uniform, GLfloat value)
        {
            // TODO: (Req 1) Send the given float value to the given uniform
            // DONE
            // Get Location of the uniform
            GLuint location = this->getUniformLocation(uniform);
            // set float value
            glUniform1f(location, value);
        }

        void set(const std::string &uniform, GLuint value)
        {
            // TODO: (Req 1) Send the given unsigned integer value to the given uniform
            // DONE
            // Get Location of the uniform
            GLuint location = this->getUniformLocation(uniform);
            // set unsigned int value
            glUniform1ui(location, value);
        }

        void set(const std::string &uniform, GLint value)
        {
            // TODO: (Req 1) Send the given integer value to the given uniform
            // DONE
            // Get Location of the uniform
            GLuint location = this->getUniformLocation(uniform);
            // set int value
            glUniform1i(location, value);
        }

        void set(const std::string &uniform, glm::vec2 value)
        {
            // TODO: (Req 1) Send the given 2D vector value to the given uniform
            // DONE
            // Get Location of the uniform
            GLuint location = this->getUniformLocation(uniform);
            // set 2D vector value
            glUniform2f(location, value.x, value.y);
        }

        void set(const std::string &uniform, glm::vec3 value)
        {
            // TODO: (Req 1) Send the given 3D vector value to the given uniform
            // DONE
            // Get Location of the uniform
            GLuint location = this->getUniformLocation(uniform);
            // set 3D vector value
            glUniform3f(location, value.x, value.y, value.z);
        }

        void set(const std::string &uniform, glm::vec4 value)
        {
            // TODO: (Req 1) Send the given 4D vector value to the given uniform
            // DONE
            // Get Location of the uniform
            GLuint location = this->getUniformLocation(uniform);
            // set 4D vector value
            glUniform4f(location, value.x, value.y, value.z, value.w);
        }

        void set(const std::string &uniform, glm::mat4 matrix)
        {
            // TODO: (Req 1) Send the given matrix 4x4 value to the given uniform
            // DONE
            // Get Location of the uniform
            GLuint location = this->getUniformLocation(uniform);
            // set 4x4 matrix value
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
        }

        // TODO: (Req 1) Delete the copy constructor and assignment operator.
        // Question: Why do we delete the copy constructor and assignment operator?
        // DONE
        // Delete copy constructor
        ShaderProgram(const ShaderProgram &) = delete;
        // Delete assignment operator
        ShaderProgram &operator=(const ShaderProgram &) = delete;
    };

}

#endif
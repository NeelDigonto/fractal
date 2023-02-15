// clang-format off
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <engine/renderer/shader/Simple.hpp>
#include <engine/renderer/shader/Compiler.hpp>
// clang-format on

template <typename T> struct StreamBufferProps {
    T* buffer;
    unsigned int buffer_width;
    unsigned int buffer_height;
    glm::vec2 frame_width;
    glm::vec2 frame_height;
};

template <typename T> export class StreamBuffer {
  private:
    unsigned int vao_;
    unsigned int program_;
    unsigned int texture_;
    StreamBufferProps<T> stream_buffer_props_;

  public:
    void StreamBuffer(const StreamBufferProps<T>& _stream_buffer_props) {
        stream_buffer_props_ = _stream_buffer_props;
        float vertices[] = {
            // positions        // texture coords
            0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // top right
            0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
            -0.5f, 0.5f,  0.0f, 0.0f, 1.0f  // top left
        };
        unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };
        unsigned int VBO, EBO;
        glGenVertexArrays(1, &vao_);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                     GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                     GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                              (void*)0);
        glEnableVertexAttribArray(0);

        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                              (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // ---------
        glGenTextures(1, &texture_);
        glBindTexture(GL_TEXTURE_2D, texture);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                        GL_CLAMP_TO_EDGE); // set texture wrapping to GL_REPEAT
                                           // (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                     stream_buffer_props_.buffer_width,
                     stream_buffer_props_.buffer_height, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, stream_buffer_props_.buffer);
        // glGenerateMipmap(GL_TEXTURE_2D);
        // glTexSubImage2D

        program_ = CompileProgram({
            vertex : Shader::StreamBuffer::Vertex,
            fragment : Shader::StreamBuffer::Fragment
        });
    }

    void update() {
        glTexImage2D(GL_TEXTURE_2D, 0, 0, stream_buffer_props_.buffer_width,
                     stream_buffer_props_.buffer_height, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, stream_buffer_props_.buffer);

        return;
    }

    void render() {

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_);

        glUseProgram(program_);

        glBindVertexArray(vao_);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    ~StreamBuffer() {
        glDeleteVertexArrays(vao_);
        glDeleteProgram(program_);
    }
};

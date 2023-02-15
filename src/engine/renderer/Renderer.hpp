// clang-format off
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <engine/renderer/shader/Simple.hpp>
#include <engine/renderer/shader/Compiler.hpp>
// clang-format on

class Renderer {
  public:
    Renderer() {
        setClearColor({0, 0, 0});
        clear();
    }

    void setClearColor(glm::vec3 _color) {
        // ------
        glClearColor(_color.r, _color.g, _color.b, 1.0f);
    }

    void setClearColor(glm::vec4 _color) {
        // ------
        glClearColor(_color.r, _color.g, _color.b, _color.a);
    }

    void clear() { glClear(GL_COLOR_BUFFER_BIT); }

    void render() { clear(); }
};
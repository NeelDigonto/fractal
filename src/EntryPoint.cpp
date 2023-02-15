#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <engine/Engine.hpp>

constexpr EngineProps engine_props{render_width : 1080, render_height : 720};

int main() {

    std::cout << "App Started" << std::endl;

    Engine engine{engine_props};

    // StreamBufferProps stream_buffer_props;

    // engine.streamBuffer(stream_buffer_props);

    while (!engine.windowShouldClose()) {

        engine.update();
    }

    return 0;
}

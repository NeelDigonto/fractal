#include <string>
#include <optional>
#include <glad/glad.h>
#include <exception>

namespace Shader {

enum class ShaderType { vertex, fragment };

unsigned int CompileShader(const std::string& _shader_src,
                           ShaderType _shader_type) {

    unsigned int shader;

    if (_shader_type == ShaderType::vertex)
        shader = glCreateShader(GL_VERTEX_SHADER);
    else if (_shader_type == ShaderType::fragment)
        shader = glCreateShader(GL_FRAGMENT_SHADER);

    const auto data = _shader_src.data();

    glShaderSource(shader, 1, &data, NULL);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        throw std::runtime_error("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" +
                                 std::string(infoLog));
    }

    return shader;
}

struct CompileProgramProps {
    std::optional<std::string> vertex;
    std::optional<std::string> fragment;
};

unsigned int CompileProgram(CompileProgramProps _compile_program_props) {

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    if (_compile_program_props.vertex) {
        const auto vertexShader = CompileShader(
            _compile_program_props.vertex.value(), ShaderType::vertex);
        glAttachShader(shaderProgram, vertexShader);
        glDeleteShader(vertexShader);
    }
    if (_compile_program_props.fragment) {
        const auto fragmentShader = CompileShader(
            _compile_program_props.fragment.value(), ShaderType::fragment);
        glAttachShader(shaderProgram, fragmentShader);
        glDeleteShader(fragmentShader);
    }

    glLinkProgram(shaderProgram);

    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        throw std::runtime_error("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" +
                                 std::string(infoLog));
    }

    return shaderProgram;
}
} // namespace Shader
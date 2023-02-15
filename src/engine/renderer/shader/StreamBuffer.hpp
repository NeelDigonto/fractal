#include <string>

namespace Shader::StreamBuffer {
constexpr std::string Vertex() {
    return R"(
#version 460 core
    layout(location = 0) in vec3 aPos;
    layout (location = 1) in vec2 aTexCoord;

    out vec2 TexCoord;

    void main() { 
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.); 
        TexCoord = vec2(aTexCoord.x, aTexCoord.y);
    }
)";
}

constexpr std::string Fragment() {
    return R"(
#version 460 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture;

void main()
{
	FragColor = texture(texture, TexCoord);
)";
}
} // namespace Shader::StreamBuffer

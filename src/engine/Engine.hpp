#include <engine/renderer/Renderer.hpp>
#include <glm/glm.hpp>

void framebuffer_size_callback(GLFWwindow*, int, int);
void processInput(GLFWwindow*);

struct EngineProps {
    unsigned int render_width;
    unsigned int render_height;
};

class Engine {
  private:
    GLFWwindow* window_{nullptr};
    Renderer* renderer_;

  public:
    Engine(const EngineProps& _engine_props) {
        // glfw: initialize and configure
        // ------------------------------
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        // glfw window creation
        // --------------------
        window_ = glfwCreateWindow(_engine_props.render_width,
                                   _engine_props.render_height, "Fractal", NULL,
                                   NULL);
        if (window_ == NULL) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }
        glfwMakeContextCurrent(window_);
        glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            throw std::runtime_error("Failed to initialize GLAD");
        }

        renderer_ = new Renderer();
    }

    bool windowShouldClose() { return glfwWindowShouldClose(window_); }

    void update() {
        // input
        // -----
        processInput(window_);

        renderer_->render();

        // glfw: swap buffers and poll IO events (keys pressed/released,
        // mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window_);
        glfwPollEvents();
    }

        ~Engine() {
        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwTerminate();
    }
};

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width
    // and height will be significantly larger than specified on retina
    // displays.
    glViewport(0, 0, width, height);
}
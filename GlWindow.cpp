//
// Created by dacma on 2/20/2024.
//

#include <iostream>
#include "GlWindow.h"
#include "GlobalFlags.h"

void gl_error_callback(GLenum source,
                       GLenum type,
                       GLuint id,
                       GLenum severity,
                       GLsizei length,
                       const GLchar* message,
                       const void* userParam ) {
    fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
             ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
             type, severity, message );
}

void glfw_error_callback(int error, const char* desc) {
    throw std::runtime_error(desc);
}

GlWindow::GlWindow(const std::string& name, int width, int height) {
    fullscreen = false;
    resized = false;
    // Set window hints for new window
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE); // Make invisible until window is properly configured
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_DEPTH_BITS, 32);

    window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    this->width = width;
    this->height = height;
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        auto winObj = (GlWindow*) glfwGetWindowUserPointer(window);
        winObj->resized = true;
        winObj->width = width;
        winObj->height = height;
    });
    glfwSetErrorCallback(glfw_error_callback);

    // Center the window
    const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(window, (videoMode->width - width) / 2, (videoMode->height - height) / 2);

    // Finish window setup
    glfwMakeContextCurrent(window);
    glfwSwapInterval(GlobalFlags::VSYNC ? 1 : 0);
    glfwShowWindow(window);

    // GLEW Stuff
    glewExperimental = true;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cout << "Error: %s\n" << glewGetErrorString(err);
    }
    if (GlobalFlags::DEBUG) {
        std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << "\n";
        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    }

    if (!glewIsSupported("GL_ARB_shader_objects") || !glewIsSupported("GL_ARB_vertex_shader") || !glewIsSupported("GL_ARB_fragment_shader")) {
        std::cerr << "Missing necessary OpenGL extensions";
    }

    // Setup OpenGL
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    if (GlobalFlags::USE_MULTISAMPLING) {
        glEnable(GL_MULTISAMPLE);
    } else {
        glDisable(GL_MULTISAMPLE);
    }
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    if (GlobalFlags::DEBUG) {
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(gl_error_callback, nullptr);
    }

    // Setup VAO
    GLuint vertexArrayId;
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);
}

void GlWindow::exitWindow() {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void GlWindow::enableFullscreen() {
    if (fullscreen) {
        return;
    }
    fullscreen = true;
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    glfwGetWindowSize(window, &oldWindowW, &oldWindowH);
    glfwGetWindowPos(window, &oldWindowX, &oldWindowY);

    glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
    glfwSwapInterval(GlobalFlags::VSYNC ? 1 : 0);
}

void GlWindow::disableFullscreen() {
    if (!fullscreen) {
        return;
    }
    fullscreen = false;

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glfwSetWindowMonitor(window, nullptr, 0, 0, width, height, GLFW_DONT_CARE);

    glfwSetWindowSize(window, oldWindowW, oldWindowH);
    glfwSetWindowPos(window, oldWindowX, oldWindowY);
    glfwSwapInterval(GlobalFlags::VSYNC ? 1 : 0);
}

void GlWindow::setResized(bool value) {
    resized = value;
}

bool GlWindow::isFullscreen() const {
    return fullscreen;
}

GlWindow::~GlWindow() {
    glfwDestroyWindow(window);
}

GLFWwindow *GlWindow::getWindow() const {
    return window;
}

int GlWindow::getWidth() const {
    return width;
}

int GlWindow::getHeight() const {
    return height;
}

double GlWindow::getAspectRatio() const {
    return (double) getWidth() / getHeight();
}

bool GlWindow::isResized() const {
    return resized;
}
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <sstream>
#include <algorithm>
#include <forward_list>
#include <optional>
#include <charconv>
#include <format>
#include <chrono>
#include <filesystem>
#include <boost/uuid/uuid.hpp>
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <stb_vorbis.c>

#include "GlWindow.h"
#include "screens/ScreenManager.h"

// TODO: Change system for freeing Uniform Blocks (how can I tie to deleting a Material, etc?) (maybe std::weak_ptr?)
// Add render priorities for transparent / non transparent render tasks
// approach planet steps: transition to ATMOSPHERE LOD, render clouds (for a certain region), render heightmap (planet still rendering behind)

int main() {
    if (!glfwInit()) {
        std::cerr << "GLFW init failed" << std::endl;
    }
    glfwSetErrorCallback([](int error, const char* description) {
        std::cerr << "Error: " << description << std::endl;
    });

    GlWindow window("Space Game", 512, 384);
    ResourceCache resources(&window);
    ScreenManager manager(&resources);
    manager.run();

    // Exit
    glfwSetErrorCallback(nullptr);
    glfwTerminate();
    return 0;
}

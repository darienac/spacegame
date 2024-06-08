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
// Get rid of the ShaderPlanet class, replace method with code in GameRenderer and make it a basic Shader3D
// approach planet steps: transition to ATMOSPHERE LOD, render clouds (for a certain region), render heightmap (planet still rendering behind)
// uViewPosition is still 32 bit and uModelPosition as well, may need another uniform to replace need for 64 bit

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

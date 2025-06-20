#include <iostream>
#include <vector>
#include <queue>
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
// uViewPosition is still 32 bit and uModelPosition as well, may need another uniform to replace need for 64 bit
// TODO: Make collision detection start from the last encompassing hitbox from previous tick, go up or down tree as necessary
// TODO: Triangle-triangle collision seems to be bugged but Triangle-Box isn't

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

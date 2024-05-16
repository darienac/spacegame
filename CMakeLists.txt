cmake_minimum_required(VERSION 3.27)
project(spacegame)

set(CMAKE_CXX_STANDARD 23)

find_package(ASSIMP REQUIRED)

add_executable(spacegame main.cpp
        util/ResourceReader.cpp
        util/ResourceReader.h
        render/model/Material.cpp
        render/model/Material.h
        render/model/Mesh.cpp
        render/model/Mesh.h
        render/model/Model.cpp
        render/model/Model.h
        render/model/Texture.cpp
        render/model/Texture.h
        render/model/TextureCache.cpp
        render/model/TextureCache.h
        render/shader/Shader2D.cpp
        render/shader/Shader2D.h
        render/shader/Shader3D.cpp
        render/shader/Shader3D.h
        render/shader/ShaderEnv.cpp
        render/shader/ShaderEnv.h
        render/shader/ShaderProgram.cpp
        render/shader/ShaderProgram.h
        render/Camera.cpp
        render/Camera.h
        render/Environment.cpp
        render/Environment.h
        render/GameRenderer.cpp
        render/GameRenderer.h
        render/GlFramebuffer.cpp
        render/GlFramebuffer.h
        render/GlScreenBuffer.cpp
        render/GlScreenBuffer.h
        Controls.cpp
        Controls.h
        GlWindow.cpp
        GlobalFlags.h
        GlWindow.h
        game/GameState.h
        screens/ResourceCache.cpp
        screens/ResourceCache.h
        screens/IScreen.h
        screens/ScreenManager.cpp
        screens/ScreenManager.h
        screens/TestScreen.cpp
        screens/TestScreen.h
        game/IGameEngine.h
        game/FreeFlyGameEngine.cpp
        game/FreeFlyGameEngine.h
        render/GlBuffer.cpp
        render/GlBuffer.h
        render/shader/ShaderPerlin.cpp
        render/shader/ShaderPerlin.h
        render/model/Cubemap.cpp
        render/model/Cubemap.h
        render/shader/UniformBlock.cpp
        render/shader/UniformBlock.h
        render/shader/UniformBlockCache.cpp
        render/shader/UniformBlockCache.h
        render/shader/ShaderPlanet.cpp
        render/shader/ShaderPlanet.h
        render/StateRenderCache.cpp
        render/StateRenderCache.h
        render/shader/IPerlinRenderer.h)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glm::glm)
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glfw)
find_package(GLEW REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE GLEW::GLEW)
find_package(Stb REQUIRED)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${Stb_INCLUDE_DIR})

#set(Boost_USE_STATIC_LIBS OFF)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS uuid)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES})
endif()

# Include Assimp headers
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${ASSIMP_INCLUDE_DIRS})

# Link against Assimp library
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${ASSIMP_LIBRARIES})
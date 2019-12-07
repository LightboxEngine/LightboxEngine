cmake_minimum_required(VERSION 3.5)

add_subdirectory(Libraries/glfw) #Add glfw to the project

# Make sure we're running C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=return-type")


# Engine sources, used in EVERYTHING that uses the engine(for now).
file(GLOB EngineSOURCES
    "Engine/src/*.cpp" "Engine/src/*.h"
    "Engine/src/RenderDevice/*.cpp" "Engine/src/RenderDevice/*.h"
    "Engine/src/RenderDevice/OpenGL3/*.cpp" "Engine/src/RenderDevice/OpenGL3/*.h"
    "Engine/src/RenderDevice/OpenGLES3/*.cpp" "Engine/src/RenderDevice/OpenGLES3/*.h"
    "Engine/src/RenderDevice/None/*.cpp" "Engine/src/RenderDevice/None/*.h"
    "Engine/src/Math/*.cpp" "Engine/src/Math/*.h"
    "Engine/src/FrameWork/*.cpp" "Engine/src/FrameWork/*.h"
    "Engine/src/Renderer/*.cpp" "Engine/src/Renderer/*.h"
    "Libraries/glad/src/glad.c"
)

project (Engine)# Create project named Engine

add_executable(Engine ${EngineSOURCES})# Create executable with the sources and headers.

# Include all needed include directories.
target_include_directories(Engine PUBLIC Engine/src/)
target_include_directories(Engine PUBLIC Libraries/glfw/include)
target_include_directories(Engine PUBLIC Libraries/glm)
target_include_directories(Engine PUBLIC Libraries/glad/include)
target_include_directories(Engine PUBLIC Libraries/stb)

target_link_libraries(Engine glfw)# Link GLFW for window creation.
#end Engine

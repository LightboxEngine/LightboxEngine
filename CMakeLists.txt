cmake_minimum_required(VERSION 3.5)

set(GLFW_BUILD_DOCS off)

add_subdirectory(Libraries/glfw) #Add glfw to the project

# Make sure we're running C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=return-type")


# Engine sources, used in EVERYTHING that uses the engine(for now).
file(GLOB EngineSOURCES
"Engine/src/RenderDevice/*.cpp" "Engine/src/RenderDevice/*.h"
"Engine/src/RenderDevice/OpenGL/*.cpp" "Engine/src/RenderDevice/OpenGL/*.h"
"Engine/src/RenderDevice/None/*.cpp" "Engine/src/RenderDevice/None/*.h"
"Engine/src/Rendering/*.cpp" "Engine/src/Rendering/*.h"
"Engine/src/App/*.cpp" "Engine/src/App/*.h"
"Engine/src/Rendering/Renderables/*.cpp" "Engine/src/Rendering/Renderables/*.h"
"Engine/src/Managing/*.cpp" "Engine/src/Managing/*.h"
"Engine/src/Types/*.cpp" "Engine/src/Types/*.h"
"Engine/src/GameEssentials/*.cpp" "Engine/src/GameEssentials/*.h"
"Engine/src/Framework/*.h" "Engine/src/Framework/*.cpp"
"Engine/src/API/*.cpp" "Engine/src/API/*.h"
"Engine/src/ExtApp/*.cpp" "Engine/src/ExtApp/*.h"
"Libraries/whereami/src/whereami.c" "Libraries/glad/src/glad.c"
)

file(GLOB EngineLibSOURCES
"Engine/src/RenderDevice/*.cpp" "Engine/src/RenderDevice/*.h"
#"Engine/src/RenderDevice/OpenGL/*.cpp" "Engine/src/RenderDevice/OpenGL/*.h"
"Engine/src/Rendering/*.cpp" "Engine/src/Rendering/*.h"
"Engine/src/App/*.cpp" "Engine/src/App/*.h"
"Engine/src/Rendering/Renderables/*.cpp" "Engine/src/Rendering/Renderables/*.h"
"Engine/src/Managing/*.cpp" "Engine/src/Managing/*.h"
"Engine/src/Types/*.cpp" "Engine/src/Types/*.h"
"Engine/src/GameEssentials/*.cpp" "Engine/src/GameEssentials/*.h"
"Engine/src/Framework/*.h" "Engine/src/Framework/*.cpp"
"Engine/src/API/*.cpp" "Engine/src/API/*.h"
"Engine/src/ExtApp/*.cpp" "Engine/src/ExtApp/*.h"
"Libraries/whereami/src/whereami.c"
)

file(GLOB EngineExtAppEngineSOURCES "Engine/src/ExtApp/Engine/*.cpp" "Engine/src/ExtApp/Engine/*.h")# Used for the Engine it self.
file(GLOB EngineExtAppGameSOURCES "Engine/src/ExtApp/Game/*.cpp" "Engine/src/ExtApp/Game/*.h")# Used for games/apps that the engine load's and executes.

project (Engine)# Create project named Engine

file(GLOB EnginesrcSources "Engine/src/*.cpp" "Engine/src/*.h")

add_executable(Engine ${EnginesrcSources} ${EngineSOURCES} ${EngineExtAppEngineSOURCES})# Create executable with the sources and headers.

# Include all needed include directories.
target_include_directories(Engine PUBLIC Libraries/whereami/src)
target_include_directories(Engine PUBLIC Engine/src/)
target_include_directories(Engine PUBLIC Libraries/glfw/include)
target_include_directories(Engine PUBLIC Libraries/glm)
target_include_directories(Engine PUBLIC Libraries/glad/include)
target_include_directories(Engine PUBLIC Libraries/stb)

target_link_libraries(Engine glfw)# Link GLFW for window creation.
#end Engine


project (Test1)# Create project named Engine  |  This project is used to test the engine functionality.

file(GLOB Test1Sources "Tests/Test1/src/*.cpp" "Tests/Test1/src/*.h" "Libraries/imgui/imgui*.cpp")

add_library(Test1 SHARED ${Test1Sources}  ${EngineLibSOURCES} ${EngineExtAppGameSOURCES})

# Include all needed include directories.
target_include_directories(Test1 PUBLIC Libraries/whereami/src)
target_include_directories(Test1 PUBLIC Engine/src/)
target_include_directories(Test1 PUBLIC Libraries/glfw/include)
target_include_directories(Test1 PUBLIC Libraries/glm)
target_include_directories(Test1 PUBLIC Libraries/glad/include)
target_include_directories(Test1 PUBLIC Libraries/stb)

target_include_directories(Test1 PUBLIC Libraries/imgui)

target_link_libraries(Test1 glfw)# Link GLFW for window creation.  |  Shouldn't be needed, but currently it can't compile without it.
#End Test1


project (TestGame)# Create project named Engine  |  This project is used to test the engine functionality.

file(GLOB TestGameSources "Tests/TestGame/src/*.cpp" "Tests/TestGame/src/*.h" "Libraries/imgui/imgui*.cpp")

add_library(TestGame SHARED ${TestGameSources}  ${EngineLibSOURCES} ${EngineExtAppGameSOURCES})

# Include all needed include directories.
target_include_directories(TestGame PUBLIC Libraries/whereami/src)
target_include_directories(TestGame PUBLIC Engine/src/)
target_include_directories(TestGame PUBLIC Libraries/glfw/include)
target_include_directories(TestGame PUBLIC Libraries/glm)
target_include_directories(TestGame PUBLIC Libraries/glad/include)
target_include_directories(TestGame PUBLIC Libraries/stb)

target_include_directories(TestGame PUBLIC Libraries/imgui)

target_link_libraries(TestGame glfw)# Link GLFW for window creation.  |  Shouldn't be needed, but currently it can't compile without it.
#End TestGame


project (TestRenderDevice)# Create project named Engine  |  This project is used to test the engine functionality.

file(GLOB TestRenderDeviceSources "Tests/TestRenderDevice/src/*.cpp" "Tests/TestRenderDevice/src/*.h" "Libraries/imgui/imgui*.cpp")

add_executable(TestRenderDevice ${TestRenderDeviceSources}  ${EngineSOURCES} ${EngineExtAppGameSOURCES})

# Include all needed include directories.
target_include_directories(TestRenderDevice PUBLIC Libraries/whereami/src)
target_include_directories(TestRenderDevice PUBLIC Engine/src/)
target_include_directories(TestRenderDevice PUBLIC Libraries/glfw/include)
target_include_directories(TestRenderDevice PUBLIC Libraries/glm)
target_include_directories(TestRenderDevice PUBLIC Libraries/glad/include)
target_include_directories(TestRenderDevice PUBLIC Libraries/stb)

target_include_directories(TestRenderDevice PUBLIC Libraries/imgui)

target_link_libraries(TestRenderDevice glfw)# Link GLFW for window creation.  |  Shouldn't be needed, but currently it can't compile without it.
#End TestGame


project (Editor)# Create project named Engine  |  This project is used to test the engine functionality.

file(GLOB EditorSources
"Editor/src/*.cpp" "Editor/src/*.h"
"Editor/src/Editor/*.cpp" "Editor/src/Editor/*.h"
"Editor/src/GUI/*.cpp" "Editor/src/GUI/*.h"
"Editor/src/EngineHandling/*.cpp" "Editor/src/EngineHandling/*.h"
"Editor/src/ExtModule/*.cpp" "Editor/src/ExtModule/*.h"
"Editor/src/ExtModule/Editor/*.cpp" "Editor/src/ExtModule/Editor/*.h"
"Editor/src/ExtModule/Module/*.cpp" "Editor/src/ExtModule/Module/*.h"
"Libraries/imgui/imgui*.cpp")

add_library(Editor SHARED ${EditorSources}   ${EngineLibSOURCES} ${EngineExtAppGameSOURCES})

# Include all needed include directories.
target_include_directories(Editor PUBLIC Libraries/whereami/src)
target_include_directories(Editor PUBLIC Engine/src/)
target_include_directories(Editor PUBLIC Editor/src/)
target_include_directories(Editor PUBLIC Libraries/glfw/include)
target_include_directories(Editor PUBLIC Libraries/glm)
target_include_directories(Editor PUBLIC Libraries/glad/include)
target_include_directories(Editor PUBLIC Libraries/stb)

target_include_directories(Editor PUBLIC Libraries/imgui)

#target_link_libraries(Editor glfw)# Link GLFW for window creation.  |  Shouldn't be needed, but currently it can't compile without it.

#Copy TestAssets for Engine
message(STATUS "Copying asset files.")
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Engine/TestResources/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

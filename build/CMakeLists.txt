cmake_minimum_required(VERSION 3.20)
project(CadCam LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- System dependencies ---
find_package(OpenCASCADE REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(Java REQUIRED COMPONENTS Runtime)

include(FetchContent)

# ===================================================================
# ANTLR4 — tool jar (downloaded) + C++ runtime (built from source)
# ===================================================================
set(ANTLR4_TAG "4.13.2")

# Download the ANTLR4 generator jar
set(ANTLR4_JAR "${CMAKE_BINARY_DIR}/antlr-${ANTLR4_TAG}-complete.jar")
if(NOT EXISTS "${ANTLR4_JAR}")
    message(STATUS "Downloading ANTLR4 tool jar v${ANTLR4_TAG} ...")
    file(DOWNLOAD
        "https://www.antlr.org/download/antlr-${ANTLR4_TAG}-complete.jar"
        "${ANTLR4_JAR}"
        SHOW_PROGRESS
    )
endif()

# Fetch and build the standalone C++ runtime (~1.5 MB source zip)
FetchContent_Declare(antlr4_runtime
    URL "https://www.antlr.org/download/antlr4-cpp-runtime-${ANTLR4_TAG}-source.zip"
)
set(ANTLR4_INSTALL OFF CACHE BOOL "" FORCE)
set(ANTLR_BUILD_CPP_TESTS OFF CACHE BOOL "" FORCE)
set(ANTLR_BUILD_SHARED OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(antlr4_runtime)

# ===================================================================
# Generate C++ parser from the .g4 grammar
# ===================================================================
set(ANTLR4_GEN_DIR "${CMAKE_BINARY_DIR}/antlr4_generated")
file(MAKE_DIRECTORY "${ANTLR4_GEN_DIR}")

set(GRAMMAR_FILE "${CMAKE_SOURCE_DIR}/grammar/OpenSCAD.g4")

set(ANTLR4_GENERATED_SOURCES
    "${ANTLR4_GEN_DIR}/OpenSCADLexer.cpp"
    "${ANTLR4_GEN_DIR}/OpenSCADParser.cpp"
    "${ANTLR4_GEN_DIR}/OpenSCADVisitor.cpp"
    "${ANTLR4_GEN_DIR}/OpenSCADBaseVisitor.cpp"
)

add_custom_command(
    OUTPUT  ${ANTLR4_GENERATED_SOURCES}
            "${ANTLR4_GEN_DIR}/OpenSCADLexer.h"
            "${ANTLR4_GEN_DIR}/OpenSCADParser.h"
            "${ANTLR4_GEN_DIR}/OpenSCADVisitor.h"
            "${ANTLR4_GEN_DIR}/OpenSCADBaseVisitor.h"
    COMMAND "${Java_JAVA_EXECUTABLE}" -jar "${ANTLR4_JAR}"
            -Dlanguage=Cpp
            -visitor
            -no-listener
            -o "${ANTLR4_GEN_DIR}"
            "${GRAMMAR_FILE}"
    DEPENDS "${GRAMMAR_FILE}"
    COMMENT "ANTLR4: generating C++ parser from OpenSCAD.g4"
    VERBATIM
)

# ===================================================================
# ImGui (docking branch) — cloned by user into extern/imgui
# ===================================================================
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/extern/imgui")
if(NOT EXISTS "${IMGUI_DIR}/imgui.h")
    message(FATAL_ERROR
        "ImGui not found at ${IMGUI_DIR}\n"
        "Clone the docking branch:\n"
        "  git clone -b docking https://github.com/ocornut/imgui.git extern/imgui"
    )
endif()

set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# ===================================================================
# Application
# ===================================================================
set(APP_SOURCES
    src/main.cpp
    src/Viewport3D.cpp
    src/ScadParser.cpp
    src/OcctBridge.cpp
)

add_executable(cadcam
    ${APP_SOURCES}
    ${IMGUI_SOURCES}
    ${ANTLR4_GENERATED_SOURCES}
)

target_include_directories(cadcam PRIVATE
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${OpenCASCADE_INCLUDE_DIR}
    ${ANTLR4_GEN_DIR}
    ${antlr4_runtime_SOURCE_DIR}/runtime/src
    src
)

target_compile_definitions(cadcam PRIVATE
    IMGUI_IMPL_OPENGL_LOADER_GLEW
)

# OCCT libraries we actually use
set(OCCT_LIBS
    TKernel TKMath TKBRep TKTopAlgo TKPrim TKMesh TKG3d TKGeomBase
)

target_link_libraries(cadcam PRIVATE
    glfw
    OpenGL::GL
    GLEW::GLEW
    glm::glm
    antlr4_static
    ${OCCT_LIBS}
)

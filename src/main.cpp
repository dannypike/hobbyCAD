#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Viewport3D.h"
#include "ScadParser.h"
#include "OcctBridge.h"

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <sys/stat.h>

// ---------------------------------------------------------------------------
// Config directory: ~/.config/hobbyCAD/
// ---------------------------------------------------------------------------
static std::string getConfigDir() {
    std::string dir;
    const char* xdg = std::getenv("XDG_CONFIG_HOME");
    if (xdg && xdg[0]) {
        dir = std::string(xdg) + "/hobbyCAD";
    } else {
        const char* home = std::getenv("HOME");
        dir = std::string(home ? home : ".") + "/.config/hobbyCAD";
    }
    mkdir(dir.c_str(), 0755);
    return dir;
}

static std::string configDir;
static std::string imguiIniPath;
static std::string windowCfgPath;

static void saveWindowGeometry(GLFWwindow* window) {
    int x, y, w, h;
    glfwGetWindowPos(window, &x, &y);
    glfwGetWindowSize(window, &w, &h);
    std::ofstream f(windowCfgPath);
    if (f.is_open()) {
        f << x << " " << y << " " << w << " " << h << "\n";
    }
}

struct WinGeom { int x = 100, y = 100, w = 1600, h = 900; bool valid = false; };

static WinGeom loadWindowGeometry() {
    WinGeom g;
    std::ifstream f(windowCfgPath);
    if (f.is_open() && (f >> g.x >> g.y >> g.w >> g.h)) {
        g.valid = true;
    }
    return g;
}

// ---------------------------------------------------------------------------
// File dialog via zenity (XFCE-friendly)
// ---------------------------------------------------------------------------
static std::string openFileDialog() {
    FILE* fp = popen(
        "zenity --file-selection "
        "--title='Open OpenSCAD File' "
        "--file-filter='OpenSCAD files (*.scad)|*.scad' "
        "--file-filter='All files|*' "
        "2>/dev/null",
        "r");
    if (!fp) return "";
    char buf[1024];
    std::string result;
    while (std::fgets(buf, sizeof(buf), fp))
        result += buf;
    pclose(fp);
    if (!result.empty() && result.back() == '\n')
        result.pop_back();
    return result;
}

// ---------------------------------------------------------------------------
// Application state
// ---------------------------------------------------------------------------
struct AppState {
    Viewport3D     viewport;
    SceneMesh      sceneMesh;
    ScadModel      scadModel;
    std::string    loadedFile;
    std::vector<std::string> logMessages;
    bool           showLog = true;

    void log(const std::string& msg) {
        logMessages.push_back(msg);
    }
};

// ---------------------------------------------------------------------------
// GLFW error callback
// ---------------------------------------------------------------------------
static void glfwErrorCB(int error, const char* desc) {
    std::fprintf(stderr, "GLFW error %d: %s\n", error, desc);
}

// ---------------------------------------------------------------------------
// Main
// ---------------------------------------------------------------------------
int main(int /*argc*/, char* /*argv*/[]) {
    glfwSetErrorCallback(glfwErrorCB);
    if (!glfwInit()) {
        std::fprintf(stderr, "Failed to initialise GLFW\n");
        return 1;
    }

    // Config paths
    configDir     = getConfigDir();
    imguiIniPath  = configDir + "/imgui.ini";
    windowCfgPath = configDir + "/window.cfg";

    WinGeom geom = loadWindowGeometry();

    // OpenGL 3.3 core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(geom.w, geom.h, "hobbyCAD", nullptr, nullptr);
    if (!window) {
        std::fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return 1;
    }
    if (geom.valid) {
        glfwSetWindowPos(window, geom.x, geom.y);
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // vsync

    // GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::fprintf(stderr, "Failed to initialise GLEW\n");
        return 1;
    }

    // ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = imguiIniPath.c_str();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    // App
    AppState app;
    app.viewport.init();
    app.log("hobbyCAD started.  File > Open SCAD to load a .scad file.");

    // --- Main loop ---
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Full-window dockspace
        ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(),
                                     ImGuiDockNodeFlags_PassthruCentralNode);

        // ---- Menu bar ----
        bool wantOpen = false;
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Open SCAD...", "Ctrl+O"))
                    wantOpen = true;
                ImGui::Separator();
                if (ImGui::MenuItem("Quit", "Ctrl+Q"))
                    glfwSetWindowShouldClose(window, GLFW_TRUE);
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("View")) {
                if (ImGui::MenuItem("Reset Camera"))
                    app.viewport.resetCamera();
                ImGui::MenuItem("Show Log", nullptr, &app.showLog);
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        // Ctrl+O shortcut
        if (io.KeyCtrl && ImGui::IsKeyPressed(ImGuiKey_O))
            wantOpen = true;
        // Ctrl+Q shortcut
        if (io.KeyCtrl && ImGui::IsKeyPressed(ImGuiKey_Q))
            glfwSetWindowShouldClose(window, GLFW_TRUE);

        // ---- Open file ----
        if (wantOpen) {
            std::string path = openFileDialog();
            if (!path.empty()) {
                app.log("Opening: " + path);
                app.scadModel  = parseScadFile(path);
                app.loadedFile = path;

                for (auto& w : app.scadModel.warnings)
                    app.log("[WARN] " + w);

                if (app.scadModel.empty()) {
                    app.log("No geometry found in file.");
                } else {
                    app.log("Parsed " + std::to_string(app.scadModel.nodes.size()) + " top-level node(s).");
                    app.sceneMesh = buildMeshFromScad(app.scadModel);
                    app.viewport.setMesh(app.sceneMesh);
                    app.viewport.zoomToFit(app.sceneMesh);
                    app.log("Mesh built: "
                        + std::to_string(app.sceneMesh.vertices.size()) + " verts, "
                        + std::to_string(app.sceneMesh.indices.size() / 3) + " tris.");
                }
            }
        }

        // ---- 3D Viewport window ----
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        if (ImGui::Begin("3D Viewport")) {
            ImVec2 size = ImGui::GetContentRegionAvail();
            int w = static_cast<int>(size.x);
            int h = static_cast<int>(size.y);

            if (w > 0 && h > 0) {
                GLuint tex = app.viewport.render(w, h);
                ImGui::Image(static_cast<ImTextureID>(static_cast<uintptr_t>(tex)),
                             size, ImVec2(0, 1), ImVec2(1, 0));  // flip Y

                // Mouse interaction in viewport
                if (ImGui::IsItemHovered()) {
                    // Scroll to zoom
                    if (io.MouseWheel != 0.0f)
                        app.viewport.onMouseScroll(io.MouseWheel);

                    // Left drag to orbit
                    if (ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
                        ImVec2 delta = io.MouseDelta;
                        app.viewport.onMouseDrag(delta.x, delta.y, true, false);
                    }
                    // Middle drag to pan
                    if (ImGui::IsMouseDragging(ImGuiMouseButton_Middle)) {
                        ImVec2 delta = io.MouseDelta;
                        app.viewport.onMouseDrag(delta.x, delta.y, false, true);
                    }
                }
            }
        }
        ImGui::End();
        ImGui::PopStyleVar();

        // ---- Properties panel ----
        if (ImGui::Begin("Properties")) {
            if (app.loadedFile.empty()) {
                ImGui::TextWrapped("No file loaded.\nUse File > Open SCAD to load a .scad file.");
            } else {
                ImGui::Text("File: %s", app.loadedFile.c_str());
                ImGui::Separator();
                ImGui::Text("Top-level nodes: %zu", app.scadModel.nodes.size());
                ImGui::Separator();
                ImGui::Text("Vertices: %zu", app.sceneMesh.vertices.size());
                ImGui::Text("Triangles: %zu", app.sceneMesh.indices.size() / 3);
            }
        }
        ImGui::End();

        // ---- Log window ----
        if (app.showLog) {
            if (ImGui::Begin("Log", &app.showLog)) {
                for (const auto& msg : app.logMessages)
                    ImGui::TextUnformatted(msg.c_str());
                if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
                    ImGui::SetScrollHereY(1.0f);
            }
            ImGui::End();
        }

        // ---- Render ----
        ImGui::Render();
        int fbW, fbH;
        glfwGetFramebufferSize(window, &fbW, &fbH);
        glViewport(0, 0, fbW, fbH);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Save state
    saveWindowGeometry(window);

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

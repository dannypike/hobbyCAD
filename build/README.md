# CadCam v0.1

Standalone CAD application using ImGui (docking) + OpenCASCADE.
Reads OpenSCAD `.scad` files and renders the geometry.

**Supported OpenSCAD statements:** `cube()` only (v0.1).

**Parser:** ANTLR4-generated from `grammar/OpenSCAD.g4`.

## Dependencies (EndeavourOS / Arch)

### From pacman

```
sudo pacman -S cmake make gcc glfw-x11 glew glm zenity jre-openjdk
```

> Java (JRE) is needed at build time — CMake invokes the ANTLR4 jar
> to generate the C++ parser from the grammar.

### From AUR (OpenCASCADE)

```
yay -S opencascade
```

### ImGui (docking branch)

```
cd cadcam
git clone -b docking https://github.com/ocornut/imgui.git extern/imgui
```

### Automatic (handled by CMake at build time)

- **ANTLR4 tool jar** — downloaded into the build directory
- **ANTLR4 C++ runtime** — fetched and compiled via FetchContent

## Build

```
cd cadcam
mkdir build && cd build
cmake ..
make -j$(nproc)
```

The first build downloads the ANTLR4 jar (~2 MB) and C++ runtime
source (~1.5 MB), then compiles the runtime.  Subsequent builds
only regenerate the parser if `grammar/OpenSCAD.g4` has changed.

## Run

```
./cadcam
```

Then: **File > Open SCAD** (or `Ctrl+O`) and select a `.scad` file.

A sample `test.scad` is provided in the project root.

## 3D Viewport Controls

| Action       | Input              |
|--------------|--------------------|
| Orbit        | Left-drag          |
| Pan          | Middle-drag        |
| Zoom         | Scroll wheel       |
| Reset camera | View > Reset Camera|

## Project Structure

```
cadcam/
├── CMakeLists.txt
├── README.md
├── test.scad
├── grammar/
│   └── OpenSCAD.g4     ← ANTLR4 grammar (cube only, v0.1)
├── extern/
│   └── imgui/          ← cloned docking branch
└── src/
    ├── main.cpp        ← GLFW + ImGui + app logic
    ├── Viewport3D.h/cpp← FBO, camera, OpenGL rendering
    ├── ScadParser.h/cpp← ANTLR4 visitor wrapping parse tree → ScadModel
    ├── OcctBridge.h/cpp← OCCT shape creation + tessellation
    └── Mesh.h          ← vertex/mesh data structures
```

## Extending the Grammar

Edit `grammar/OpenSCAD.g4` and rebuild — CMake will automatically
re-invoke the ANTLR4 tool and recompile the generated sources.
Then add handling for the new constructs in `ScadParser.cpp`
(the `ScadBuildVisitor` class).

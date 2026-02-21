#pragma once

#include "Mesh.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

class Viewport3D {
public:
    Viewport3D();
    ~Viewport3D();

    // Call once after OpenGL context is ready
    void init();

    // Upload new mesh data to GPU
    void setMesh(const SceneMesh& mesh);

    // Render the scene into the internal FBO at the given size.
    // Returns the colour-attachment texture ID for ImGui::Image().
    GLuint render(int width, int height);

    // Camera interaction (call from ImGui input handling)
    void onMouseDrag(float dx, float dy, bool rotate, bool pan);
    void onMouseScroll(float delta);
    void resetCamera();

private:
    void initShaders();
    void initGrid();
    void ensureFBO(int w, int h);
    void renderGrid(const glm::mat4& vp);
    void renderMesh(const glm::mat4& view, const glm::mat4& proj);

    // FBO
    GLuint fbo_       = 0;
    GLuint colorTex_  = 0;
    GLuint depthRbo_  = 0;
    int    fboW_      = 0;
    int    fboH_      = 0;

    // Shaders
    GLuint meshProg_  = 0;
    GLuint gridProg_  = 0;
    GLuint edgeProg_  = 0;

    // Mesh GPU objects
    GLuint meshVAO_ = 0, meshVBO_ = 0, meshEBO_ = 0;
    GLuint edgeVAO_ = 0, edgeVBO_ = 0;
    int    meshIndexCount_ = 0;
    int    edgeVertCount_  = 0;

    // Grid GPU objects
    GLuint gridVAO_ = 0, gridVBO_ = 0;
    int    gridVertCount_ = 0;

    // Camera (orbit)
    float camDist_  = 80.0f;
    float camAz_    = 45.0f;    // degrees
    float camEl_    = 30.0f;    // degrees
    glm::vec3 camTarget_{0.0f, 0.0f, 0.0f};
};

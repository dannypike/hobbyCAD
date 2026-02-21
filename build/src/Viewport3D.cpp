#include "Viewport3D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>
#include <cstdio>
#include <vector>

// ===== Shader sources =====

static const char* meshVertSrc = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;
out vec3 vNormal;
out vec3 vFragPos;
void main() {
    vec4 wp = uModel * vec4(aPos, 1.0);
    vFragPos = wp.xyz;
    vNormal  = mat3(transpose(inverse(uModel))) * aNormal;
    gl_Position = uProj * uView * wp;
}
)";

static const char* meshFragSrc = R"(
#version 330 core
in vec3 vNormal;
in vec3 vFragPos;
out vec4 FragColor;
uniform vec3 uLightDir;
uniform vec3 uViewPos;
uniform vec3 uColor;
void main() {
    vec3 n = normalize(vNormal);
    vec3 l = normalize(uLightDir);
    float diff = max(dot(n, l), 0.0);
    vec3 ambient = 0.18 * uColor;
    vec3 diffuse = diff * uColor * 0.72;
    vec3 v = normalize(uViewPos - vFragPos);
    vec3 r = reflect(-l, n);
    float spec = pow(max(dot(v, r), 0.0), 48.0);
    vec3 specular = 0.35 * spec * vec3(1.0);
    FragColor = vec4(ambient + diffuse + specular, 1.0);
}
)";

static const char* lineVertSrc = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
uniform mat4 uMVP;
void main() {
    gl_Position = uMVP * vec4(aPos, 1.0);
}
)";

static const char* lineFragSrc = R"(
#version 330 core
out vec4 FragColor;
uniform vec3 uLineColor;
void main() {
    FragColor = vec4(uLineColor, 1.0);
}
)";

// ===== Helpers =====

static GLuint compileShader(GLenum type, const char* src) {
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, nullptr);
    glCompileShader(s);
    int ok;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[512];
        glGetShaderInfoLog(s, 512, nullptr, log);
        std::fprintf(stderr, "Shader compile error:\n%s\n", log);
    }
    return s;
}

static GLuint linkProgram(const char* vSrc, const char* fSrc) {
    GLuint vs = compileShader(GL_VERTEX_SHADER, vSrc);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fSrc);
    GLuint p = glCreateProgram();
    glAttachShader(p, vs);
    glAttachShader(p, fs);
    glLinkProgram(p);
    int ok;
    glGetProgramiv(p, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[512];
        glGetProgramInfoLog(p, 512, nullptr, log);
        std::fprintf(stderr, "Program link error:\n%s\n", log);
    }
    glDeleteShader(vs);
    glDeleteShader(fs);
    return p;
}

// ===== Viewport3D =====

Viewport3D::Viewport3D()  = default;
Viewport3D::~Viewport3D() {
    if (fbo_)      glDeleteFramebuffers(1, &fbo_);
    if (colorTex_) glDeleteTextures(1, &colorTex_);
    if (depthRbo_) glDeleteRenderbuffers(1, &depthRbo_);
    if (meshVAO_)  glDeleteVertexArrays(1, &meshVAO_);
    if (meshVBO_)  glDeleteBuffers(1, &meshVBO_);
    if (meshEBO_)  glDeleteBuffers(1, &meshEBO_);
    if (edgeVAO_)  glDeleteVertexArrays(1, &edgeVAO_);
    if (edgeVBO_)  glDeleteBuffers(1, &edgeVBO_);
    if (gridVAO_)  glDeleteVertexArrays(1, &gridVAO_);
    if (gridVBO_)  glDeleteBuffers(1, &gridVBO_);
    if (meshProg_) glDeleteProgram(meshProg_);
    if (gridProg_) glDeleteProgram(gridProg_);
    if (edgeProg_) glDeleteProgram(edgeProg_);
}

void Viewport3D::init() {
    initShaders();
    initGrid();
}

void Viewport3D::initShaders() {
    meshProg_ = linkProgram(meshVertSrc, meshFragSrc);
    gridProg_ = linkProgram(lineVertSrc, lineFragSrc);
    edgeProg_ = linkProgram(lineVertSrc, lineFragSrc);
}

void Viewport3D::initGrid() {
    // Ground grid on XY plane, ±200 mm, every 10 mm
    std::vector<float> verts;
    const float extent = 200.0f;
    const float step   = 10.0f;

    for (float v = -extent; v <= extent; v += step) {
        // Lines parallel to Y
        verts.push_back(v); verts.push_back(-extent); verts.push_back(0.0f);
        verts.push_back(v); verts.push_back( extent); verts.push_back(0.0f);
        // Lines parallel to X
        verts.push_back(-extent); verts.push_back(v); verts.push_back(0.0f);
        verts.push_back( extent); verts.push_back(v); verts.push_back(0.0f);
    }
    gridVertCount_ = static_cast<int>(verts.size() / 3);

    glGenVertexArrays(1, &gridVAO_);
    glGenBuffers(1, &gridVBO_);
    glBindVertexArray(gridVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, gridVBO_);
    glBufferData(GL_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(verts.size() * sizeof(float)),
        verts.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glBindVertexArray(0);
}

void Viewport3D::ensureFBO(int w, int h) {
    if (w <= 0) w = 1;
    if (h <= 0) h = 1;
    if (fbo_ && fboW_ == w && fboH_ == h) return;

    if (fbo_)      glDeleteFramebuffers(1, &fbo_);
    if (colorTex_) glDeleteTextures(1, &colorTex_);
    if (depthRbo_) glDeleteRenderbuffers(1, &depthRbo_);

    glGenFramebuffers(1, &fbo_);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_);

    glGenTextures(1, &colorTex_);
    glBindTexture(GL_TEXTURE_2D, colorTex_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTex_, 0);

    glGenRenderbuffers(1, &depthRbo_);
    glBindRenderbuffer(GL_RENDERBUFFER, depthRbo_);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthRbo_);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    fboW_ = w;
    fboH_ = h;
}

void Viewport3D::setMesh(const SceneMesh& mesh) {
    // Upload face triangles
    if (!meshVAO_) {
        glGenVertexArrays(1, &meshVAO_);
        glGenBuffers(1, &meshVBO_);
        glGenBuffers(1, &meshEBO_);
    }

    glBindVertexArray(meshVAO_);

    glBindBuffer(GL_ARRAY_BUFFER, meshVBO_);
    glBufferData(GL_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(mesh.vertices.size() * sizeof(MeshVertex)),
        mesh.vertices.data(), GL_STATIC_DRAW);

    // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex),
        reinterpret_cast<void*>(offsetof(MeshVertex, px)));
    // normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex),
        reinterpret_cast<void*>(offsetof(MeshVertex, nx)));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshEBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(mesh.indices.size() * sizeof(uint32_t)),
        mesh.indices.data(), GL_STATIC_DRAW);

    meshIndexCount_ = static_cast<int>(mesh.indices.size());
    glBindVertexArray(0);

    // Upload edge lines
    if (!edgeVAO_) {
        glGenVertexArrays(1, &edgeVAO_);
        glGenBuffers(1, &edgeVBO_);
    }

    glBindVertexArray(edgeVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, edgeVBO_);
    glBufferData(GL_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(mesh.edgeVerts.size() * sizeof(float)),
        mesh.edgeVerts.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    edgeVertCount_ = static_cast<int>(mesh.edgeVerts.size() / 3);
    glBindVertexArray(0);
}

GLuint Viewport3D::render(int width, int height) {
    ensureFBO(width, height);

    glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
    glViewport(0, 0, width, height);
    glClearColor(0.15f, 0.15f, 0.18f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // Camera matrices
    float azRad = glm::radians(camAz_);
    float elRad = glm::radians(camEl_);
    glm::vec3 eye;
    eye.x = camTarget_.x + camDist_ * std::cos(elRad) * std::cos(azRad);
    eye.y = camTarget_.y + camDist_ * std::cos(elRad) * std::sin(azRad);
    eye.z = camTarget_.z + camDist_ * std::sin(elRad);

    glm::mat4 view = glm::lookAt(eye, camTarget_, glm::vec3(0, 0, 1));
    float aspect = (height > 0) ? static_cast<float>(width) / static_cast<float>(height) : 1.0f;
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 10000.0f);
    glm::mat4 vp = proj * view;

    // Grid
    renderGrid(vp);

    // Mesh faces
    if (meshIndexCount_ > 0) {
        renderMesh(view, proj);
    }

    // Edges on top of faces
    if (edgeVertCount_ > 0) {
        glUseProgram(edgeProg_);
        glUniformMatrix4fv(glGetUniformLocation(edgeProg_, "uMVP"), 1, GL_FALSE, glm::value_ptr(vp));
        glUniform3f(glGetUniformLocation(edgeProg_, "uLineColor"), 0.1f, 0.1f, 0.1f);

        glEnable(GL_POLYGON_OFFSET_LINE);
        glPolygonOffset(-1.0f, -1.0f);

        glBindVertexArray(edgeVAO_);
        glLineWidth(1.5f);
        glDrawArrays(GL_LINES, 0, edgeVertCount_);
        glBindVertexArray(0);

        glDisable(GL_POLYGON_OFFSET_LINE);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return colorTex_;
}

void Viewport3D::renderGrid(const glm::mat4& vp) {
    glUseProgram(gridProg_);
    glUniformMatrix4fv(glGetUniformLocation(gridProg_, "uMVP"), 1, GL_FALSE, glm::value_ptr(vp));
    glUniform3f(glGetUniformLocation(gridProg_, "uLineColor"), 0.35f, 0.35f, 0.35f);

    glBindVertexArray(gridVAO_);
    glLineWidth(1.0f);
    glDrawArrays(GL_LINES, 0, gridVertCount_);
    glBindVertexArray(0);
}

void Viewport3D::renderMesh(const glm::mat4& view, const glm::mat4& proj) {
    glUseProgram(meshProg_);

    glm::mat4 model(1.0f);
    glUniformMatrix4fv(glGetUniformLocation(meshProg_, "uModel"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(meshProg_, "uView"),  1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(meshProg_, "uProj"),  1, GL_FALSE, glm::value_ptr(proj));

    // Light from upper-right-front
    glUniform3f(glGetUniformLocation(meshProg_, "uLightDir"), 0.4f, 0.3f, 0.8f);

    // Camera position for specular
    float azRad = glm::radians(camAz_);
    float elRad = glm::radians(camEl_);
    glm::vec3 eye;
    eye.x = camTarget_.x + camDist_ * std::cos(elRad) * std::cos(azRad);
    eye.y = camTarget_.y + camDist_ * std::cos(elRad) * std::sin(azRad);
    eye.z = camTarget_.z + camDist_ * std::sin(elRad);
    glUniform3f(glGetUniformLocation(meshProg_, "uViewPos"), eye.x, eye.y, eye.z);

    // Object colour: steel blue
    glUniform3f(glGetUniformLocation(meshProg_, "uColor"), 0.45f, 0.58f, 0.72f);

    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0f, 1.0f);

    glBindVertexArray(meshVAO_);
    glDrawElements(GL_TRIANGLES, meshIndexCount_, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    glDisable(GL_POLYGON_OFFSET_FILL);
}

// ===== Camera controls =====

void Viewport3D::onMouseDrag(float dx, float dy, bool rotate, bool pan) {
    if (rotate) {
        camAz_ -= dx * 0.3f;
        camEl_ += dy * 0.3f;
        camEl_ = glm::clamp(camEl_, -89.0f, 89.0f);
    }
    if (pan) {
        float azRad = glm::radians(camAz_);
        // Pan in the plane perpendicular to view direction
        glm::vec3 right(-std::sin(azRad), std::cos(azRad), 0.0f);
        glm::vec3 up(0.0f, 0.0f, 1.0f);
        float scale = camDist_ * 0.002f;
        camTarget_ -= right * dx * scale;
        camTarget_ += up * dy * scale;
    }
}

void Viewport3D::onMouseScroll(float delta) {
    camDist_ *= (1.0f - delta * 0.1f);
    camDist_ = glm::clamp(camDist_, 1.0f, 5000.0f);
}

void Viewport3D::resetCamera() {
    camDist_   = 80.0f;
    camAz_     = 45.0f;
    camEl_     = 30.0f;
    camTarget_ = glm::vec3(0.0f);
}

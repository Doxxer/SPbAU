#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <boost/format.hpp>

#include "shader.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "Terrain.hpp"

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::inverse;
using glm::mat4;
using glm::normalize;

typedef struct {
    vec3 pt;
    vec2 texcoord;
} vertex2_t;

const char *attributeLocations[] = { "Position" };
const char *attribLocSecondPass[] = { "Position", "Texture" };

namespace attribsSecondPass {
enum {
    POSITION,
    TEXCOORD
};
}

struct bufferObjects {
    unsigned int vao;
    unsigned int ibo;
    unsigned int numIndices;
    unsigned int vbo;
} bufferSecondPass;

int width = 1300;
int height = 900;

Camera cam(width, height);
GLFWwindow *window;

double lastTime = glfwGetTime();
GLuint framesCounter = 0;

GLuint vao, vbo, ibo;
GLuint positionLocation = 0;
GLuint posLocSecondPass = 0;
GLuint texLocSecondPass = 0;
int triVerticesToDraw;
GLuint depthTexture = 0;
GLuint normalTexture = 0;
GLuint positionTexture = 0;
GLuint colorTexture = 0;
GLuint worldPosTexture = 0;
GLuint FBO = 0;

GLuint shaderProgram;
GLuint shaderSecondPassProgram;

int noiseOctaves = 4;
float noiseLacunarity = 0.07;
float noiseGain = 0.35;

struct Tess {
    float innerTessellation;
    vec3 outerTessellation;
} tessellation, tessellation2;

static void error_callback(int error, const char *description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_RELEASE)
        return;
    bool shift = (mods == GLFW_MOD_SHIFT);
    
    double move_offset = (shift ? 2.0 : 0.2);
    
    switch (key) {
        case GLFW_KEY_Z:
            cam.pos.z -= move_offset;
            cam.lookPos.z -= move_offset;
            break;
        case GLFW_KEY_X:
            cam.pos.z += move_offset;
            cam.lookPos.z += move_offset;
            break;
        case GLFW_KEY_S:
            cam.pos.y -= move_offset;
            cam.lookPos.y -= move_offset;
            break;
        case GLFW_KEY_W:
            cam.pos.y += move_offset;
            cam.lookPos.y += move_offset;
            break;
        case GLFW_KEY_A:
            cam.pos.x -= move_offset;
            cam.lookPos.x -= move_offset;
            break;
        case GLFW_KEY_D:
            cam.pos.x += move_offset;
            cam.lookPos.x += move_offset;
            break;

        case GLFW_KEY_I:
            if (shift)
                tessellation.innerTessellation += 1.0;
            else {
                if (tessellation.innerTessellation > 1.0)
                    tessellation.innerTessellation -= 1.0;
            }
            break;
        case GLFW_KEY_O:
            if (shift)
                tessellation.outerTessellation += vec3(1.0);
            else {
                if (tessellation.outerTessellation.x > 1.0)
                    tessellation.outerTessellation -= vec3(1.0);
            }
            break;
        case GLFW_KEY_T:
            tessellation.innerTessellation = 14.0;
            tessellation.outerTessellation = vec3(14.0);
            tessellation2.innerTessellation = 6.0;
            tessellation2.outerTessellation = vec3(6.0);
            break;

        case GLFW_KEY_P:
            noiseGain += (shift ? 0.01 : -0.01);
            break;
        case GLFW_KEY_R:
            noiseLacunarity += (shift ? 0.01 : -0.01);
            break;
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;
    }
}

void updateTitleFPS()
{
    boost::format mainWindowTitle("GPU Terrain | %4.2f FPS");
    double currentTime = glfwGetTime();
    framesCounter++;
    if (currentTime - lastTime >= 0.5) {
        mainWindowTitle % (framesCounter / (currentTime - lastTime));
        glfwSetWindowTitle(window, mainWindowTitle.str().c_str());
        framesCounter = 0;
        lastTime = currentTime;
    }
}

void init()
{
    vec2 meshX = vec2(-800.0, 800.0);
    vec2 meshZ = vec2(1.0, 2500.0);

    Terrain terrain(meshX.x, meshX.y, meshZ.x, meshZ.y);
    terrain.GenerateTerrainData();

    // Find an unused name for the buffer and create it
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create a buffer object to place data
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 terrain.vertices.size() * sizeof(vec3),
                 &terrain.vertices[0],
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 terrain.faces.size() * sizeof(Triangle),
                 &terrain.faces[0],
                 GL_STATIC_DRAW);
    triVerticesToDraw = 3 * (int)terrain.faces.size();

    // Unplug Vertex Array
    glBindVertexArray(0);
}

void bindTexture(int w, int h, GLuint &texture, bool depth = false)
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    if (depth) {
        glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, w, h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    }
    else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, w, h, 0, GL_RGBA, GL_FLOAT, 0);
    }
}

void initFBO(int w, int h)
{
    GLenum FBOstatus;

    glActiveTexture(GL_TEXTURE0);

    glGenTextures(1, &depthTexture);
    glGenTextures(1, &normalTexture);
    glGenTextures(1, &positionTexture);
    glGenTextures(1, &colorTexture);
    glGenTextures(1, &worldPosTexture);

    bindTexture(w, h, depthTexture, true);
    bindTexture(w, h, normalTexture);
    bindTexture(w, h, positionTexture);
    bindTexture(w, h, colorTexture);
    bindTexture(w, h, worldPosTexture);

    // create a framebuffer object
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    // Instruct openGL that we won't bind a color texture with the currently binded FBO
    glReadBuffer(GL_NONE);
    GLint normal_loc = glGetFragDataLocation(shaderProgram, "out_Normal");
    GLint position_loc = glGetFragDataLocation(shaderProgram, "out_Position");
    GLint color_loc = glGetFragDataLocation(shaderProgram, "out_Color");
    GLint worldPos_loc = glGetFragDataLocation(shaderProgram, "out_WorldPos");
    GLenum draws[4];
    draws[normal_loc] = GL_COLOR_ATTACHMENT0;
    draws[position_loc] = GL_COLOR_ATTACHMENT1;
    draws[color_loc] = GL_COLOR_ATTACHMENT2;
    draws[worldPos_loc] = GL_COLOR_ATTACHMENT3;
    glDrawBuffers(4, draws);

    // attach the texture to FBO depth attachment point
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);
    glBindTexture(GL_TEXTURE_2D, normalTexture);
    glFramebufferTexture(GL_FRAMEBUFFER, draws[normal_loc], normalTexture, 0);
    glBindTexture(GL_TEXTURE_2D, positionTexture);
    glFramebufferTexture(GL_FRAMEBUFFER, draws[position_loc], positionTexture, 0);
    glBindTexture(GL_TEXTURE_2D, colorTexture);
    glFramebufferTexture(GL_FRAMEBUFFER, draws[color_loc], colorTexture, 0);
    glBindTexture(GL_TEXTURE_2D, worldPosTexture);
    glFramebufferTexture(GL_FRAMEBUFFER, draws[worldPos_loc], worldPosTexture, 0);

    // check FBO status
    FBOstatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (FBOstatus != GL_FRAMEBUFFER_COMPLETE) {
        printf("GL_FRAMEBUFFER_COMPLETE failed, CANNOT use FBO\n");
    }

    // switch back to window-system-provided framebuffer
    glClear(GL_DEPTH_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void bindFBO()
{
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0); // Bad mojo to unbind the framebuffer using the texture
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
}

void initSecondPass()
{

    // Screen positions and texture coordinates
    vertex2_t verts[] = { { vec3(-1, 1, 0), vec2(0, 1) }, { vec3(-1, -1, 0), vec2(0, 0) },
                          { vec3(1, -1, 0), vec2(1, 0) }, { vec3(1, 1, 0), vec2(1, 1) } };

    // Indices to create triangle using above vertices
    unsigned short indices[] = { 0, 1, 2, 0, 2, 3 };
    bufferSecondPass.numIndices = 6;

    // Allocate vertex array
    // Vertex arrays encapsulate a set of generic vertex attributes and the buffers they are bound
    // too
    glGenVertexArrays(1, &(bufferSecondPass.vao));
    glBindVertexArray(bufferSecondPass.vao);

    // Allocate vbos for data - The vbo will haveboth positions and textures
    glGenBuffers(1, &(bufferSecondPass.vbo));
    glGenBuffers(1, &(bufferSecondPass.ibo));

    // Upload vertex data
    glBindBuffer(GL_ARRAY_BUFFER, bufferSecondPass.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    // Use of strided data, Array of Structures instead of Structures of Arrays
    glVertexAttribPointer(attribsSecondPass::POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(vertex2_t), 0);
    glVertexAttribPointer(attribsSecondPass::TEXCOORD,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(vertex2_t),
                          (void *)sizeof(vec3));
    glEnableVertexAttribArray(attribsSecondPass::POSITION);
    glEnableVertexAttribArray(attribsSecondPass::TEXCOORD);

    // indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferSecondPass.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 bufferSecondPass.numIndices * sizeof(GLushort),
                 indices,
                 GL_STATIC_DRAW);

    // Unplug Vertex Array
    glBindVertexArray(0);
}

int perm[256] = { 151, 160, 137, 91,  90,  15,  131, 13,  201, 95,  96,  53,  194, 233, 7,   225,
                  140, 36,  103, 30,  69,  142, 8,   99,  37,  240, 21,  10,  23,  190, 6,   148,
                  247, 120, 234, 75,  0,   26,  197, 62,  94,  252, 219, 203, 117, 35,  11,  32,
                  57,  177, 33,  88,  237, 149, 56,  87,  174, 20,  125, 136, 171, 168, 68,  175,
                  74,  165, 71,  134, 139, 48,  27,  166, 77,  146, 158, 231, 83,  111, 229, 122,
                  60,  211, 133, 230, 220, 105, 92,  41,  55,  46,  245, 40,  244, 102, 143, 54,
                  65,  25,  63,  161, 1,   216, 80,  73,  209, 76,  132, 187, 208, 89,  18,  169,
                  200, 196, 135, 130, 116, 188, 159, 86,  164, 100, 109, 198, 173, 186, 3,   64,
                  52,  217, 226, 250, 124, 123, 5,   202, 38,  147, 118, 126, 255, 82,  85,  212,
                  207, 206, 59,  227, 47,  16,  58,  17,  182, 189, 28,  42,  223, 183, 170, 213,
                  119, 248, 152, 2,   44,  154, 163, 70,  221, 153, 101, 155, 167, 43,  172, 9,
                  129, 22,  39,  253, 19,  98,  108, 110, 79,  113, 224, 232, 178, 185, 112, 104,
                  218, 246, 97,  228, 251, 34,  242, 193, 238, 210, 144, 12,  191, 179, 162, 241,
                  81,  51,  145, 235, 249, 14,  239, 107, 49,  192, 214, 31,  181, 199, 106, 157,
                  184, 84,  204, 176, 115, 121, 50,  45,  127, 4,   150, 254, 138, 236, 205, 93,
                  222, 114, 67,  29,  24,  72,  243, 141, 128, 195, 78,  66,  215, 61,  156, 180 };

int grad3[16][3] = { { 0, 1, 1 },  { 0, 1, -1 },  { 0, -1, 1 }, { 0, -1, -1 },
                     { 1, 0, 1 },  { 1, 0, -1 },  { -1, 0, 1 }, { -1, 0, -1 },
                     { 1, 1, 0 },  { 1, -1, 0 },  { -1, 1, 0 }, { -1, -1, 0 }, // 12 cube edges
                     { 1, 0, -1 }, { -1, 0, -1 }, { 0, -1, 1 }, { 0, 1, 1 } }; // 4 more to make 16

vector<char> pixels(256 * 256 * 4);

void initNoiseTexture(GLuint *texID)
{
    glGenTextures(1, texID);              // Generate a unique texture ID
    glBindTexture(GL_TEXTURE_2D, *texID); // Bind the texture to texture unit 0

    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            int offset = (i * 256 + j) * 4;
            char value = perm[(j + perm[i]) & 0xFF];
            pixels[offset] = grad3[value & 0x0F][0] * 64 + 64;     // Gradient x
            pixels[offset + 1] = grad3[value & 0x0F][1] * 64 + 64; // Gradient y
            pixels[offset + 2] = grad3[value & 0x0F][2] * 64 + 64; // Gradient z
            pixels[offset + 3] = value;                            // Permuted index
        }
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, *texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glUniform1i(glGetUniformLocation(shaderProgram, "u_Noise"), 0);
}

vec4 nearModelView;
vec4 farModelView;

// Create uniforms for the first pass
void GetUniforms()
{
    mat4 view = cam.GetViewTransform();
    mat4 perspective = cam.GetPerspective();

    GLuint tex = 0;
    initNoiseTexture(&tex);

    nearModelView = view * vec4(0, 0, cam.near, 1);
    farModelView = view * vec4(0, 0, cam.far, 1);

    // The tessellation distance - Terrain that is closer to camera than this value is tessellated
    float tessDist = -((1.0 * cam.far - cam.near) / 3.0 + cam.near);
    float tessDist2 = -(2.0 * (cam.far - cam.near) / 3.0 + cam.near);

    float rangeX = abs(cam.right - cam.left) / 2.0;
    float extraX = abs(tessDist2) * tan(cam.fovx * M_PI / 180.0 / 2.0);

    float rangeY = abs(cam.top - cam.bottom) / 2.0;
    float extraY = abs(cam.far) * tan(cam.fovy * M_PI / 180.0 / 2.0);

    glUniform1f(glGetUniformLocation(shaderProgram, "u_Near"), -cam.near);
    glUniform1f(glGetUniformLocation(shaderProgram, "u_Far"), -cam.far);
    glUniform1f(glGetUniformLocation(shaderProgram, "u_Left"), -rangeX - extraX);
    glUniform1f(glGetUniformLocation(shaderProgram, "u_Right"), rangeX + extraX);
    glUniform1f(glGetUniformLocation(shaderProgram, "u_Bottom"), -rangeY - extraY);
    glUniform1f(glGetUniformLocation(shaderProgram, "u_Top"), rangeY + extraY);

    glUniform1i(glGetUniformLocation(shaderProgram, "u_Display"), 0);

    glUniform1f(glGetUniformLocation(shaderProgram, "u_TessDistance"), tessDist);
    glUniform1f(glGetUniformLocation(shaderProgram, "u_TessDistance2"), tessDist2);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "u_View"), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(
        glGetUniformLocation(shaderProgram, "u_Persp"), 1, GL_FALSE, &perspective[0][0]);
    glUniform1f(glGetUniformLocation(shaderProgram, "u_InnerTessLevel"),
                tessellation.innerTessellation);
    glUniform3f(glGetUniformLocation(shaderProgram, "u_OuterTessLevel"),
                tessellation.outerTessellation.x,
                tessellation.outerTessellation.y,
                tessellation.outerTessellation.z);
    glUniform1f(glGetUniformLocation(shaderProgram, "u_InnerTessLevel2"),
                tessellation2.innerTessellation);
    glUniform3f(glGetUniformLocation(shaderProgram, "u_OuterTessLevel2"),
                tessellation2.outerTessellation.x,
                tessellation2.outerTessellation.y,
                tessellation2.outerTessellation.z);

    glUniform1i(glGetUniformLocation(shaderProgram, "u_NoiseOctaves"), noiseOctaves);
    glUniform1f(glGetUniformLocation(shaderProgram, "u_NoiseLacunarity"), noiseLacunarity);
    glUniform1f(glGetUniformLocation(shaderProgram, "u_NoiseGain"), noiseGain);
}

void GetUniformsSecondPass()
{
    mat4 view = cam.GetViewTransform();
    mat4 perspective = cam.GetPerspective();
    nearModelView = view * vec4(0, 0, cam.near, 1);
    farModelView = view * vec4(0, 0, cam.far, 1);

    glUniform1f(glGetUniformLocation(shaderSecondPassProgram, "u_NearModel"), -nearModelView.z);
    glUniform1f(glGetUniformLocation(shaderSecondPassProgram, "u_FarModel"), -farModelView.z);

    glUniform1i(glGetUniformLocation(shaderSecondPassProgram, "u_ScreenWidth"), width);
    glUniform1i(glGetUniformLocation(shaderSecondPassProgram, "u_ScreenHeight"), height);

    glUniform1i(glGetUniformLocation(shaderSecondPassProgram, "u_Display"), 0);
    glUniform1i(glGetUniformLocation(shaderSecondPassProgram, "u_DisplayFog"), 0);

    glUniformMatrix4fv(
        glGetUniformLocation(shaderSecondPassProgram, "u_View"), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(
        glGetUniformLocation(shaderSecondPassProgram, "u_Persp"), 1, GL_FALSE, &perspective[0][0]);
}

void displaySecondPass()
{
    glUseProgram(shaderSecondPassProgram);
    GetUniformsSecondPass();

    glBindVertexArray(bufferSecondPass.vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferSecondPass.ibo);

    glEnable(GL_TEXTURE_2D);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glUniform1i(glGetUniformLocation(shaderSecondPassProgram, "u_Depthtex"), 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, normalTexture);
    glUniform1i(glGetUniformLocation(shaderSecondPassProgram, "u_Normaltex"), 1);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, positionTexture);
    glUniform1i(glGetUniformLocation(shaderSecondPassProgram, "u_Positiontex"), 2);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, colorTexture);
    glUniform1i(glGetUniformLocation(shaderSecondPassProgram, "u_Colortex"), 3);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, worldPosTexture);
    glUniform1i(glGetUniformLocation(shaderSecondPassProgram, "u_WorldPostex"), 4);
    
    glDrawElements(GL_TRIANGLES, bufferSecondPass.numIndices, GL_UNSIGNED_SHORT, 0);

    glBindVertexArray(0);
}

void display()
{
    bindFBO();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // First use the shaders to tessellate and get the correct geometry in the first pass
    glUseProgram(shaderProgram);
    glPatchParameteri(GL_PATCH_VERTICES, 3);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    GetUniforms();

    glClearColor(0, 0, 0, 1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBindVertexArray(vao);
    glEnable(GL_TEXTURE_2D);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glDrawElements(GL_PATCHES, triVerticesToDraw, GL_UNSIGNED_INT, 0);

    // Set the textures from the first pass to display it in the second pass
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
    //
    // Always want to show solid mesh here as the vbos in this pass are in screen space
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    displaySecondPass();

    updateTitleFPS();
}

void freeFBO()
{
    glDeleteTextures(1, &depthTexture);
    glDeleteTextures(1, &normalTexture);
    glDeleteTextures(1, &positionTexture);
    glDeleteTextures(1, &colorTexture);
    glDeleteTextures(1, &worldPosTexture);
    glDeleteFramebuffers(1, &FBO);
}

int main(void)
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width, height, "", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        exit(EXIT_FAILURE);
    }

    std::cout << "loading..." << std::endl;
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl
              << "Glew version: " << glewGetString(GLEW_VERSION) << std::endl;

    tessellation.innerTessellation = 1.0f;
    tessellation.outerTessellation = vec3(1);

    // Create, compile and attach shaders
    shaderProgram = LoadShaders("simpleVS.glsl",
                                "simpleFS.glsl",
                                "simpleGS.glsl",
                                "Terrain_TCS.glsl",
                                "Terrain_TES.glsl",
                                attributeLocations,
                                1);

    shaderSecondPassProgram = LoadShaders(
        "secondPassVS.glsl", "secondPassFS.glsl", NULL, NULL, NULL, attribLocSecondPass, 2);

    initFBO(width, height);
    init();
    initSecondPass();

    std::cout << "GPU Terrain Generator" << std::endl;

    while (!glfwWindowShouldClose(window)) {
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    freeFBO();
    exit(EXIT_SUCCESS);
}
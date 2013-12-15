#include <GL/glew.h>
#include <cstdio>
#include <vector>
#include <fstream>
#include <iostream>
#include "shader.hpp"

std::string ReadFile(char const *file_path)
{
    std::string shaderCode;
    std::ifstream fileStream(file_path, std::ios::in);
    if (fileStream.is_open()) {
        std::string line = "";
        while (getline(fileStream, line))
            shaderCode += "\n" + line;
        fileStream.close();
    } else {
        printf("Impossible to open %s\n", file_path);
    }
    return shaderCode;
}

void LoadShader(GLuint &shaderID, char const *shader_file_path)
{
    printf("Reading shader file: %s\n", shader_file_path);
    std::string shaderCode = ReadFile(shader_file_path);

    printf("Compiling shader: %s\n", shader_file_path);
    char const *shaderSourcePointer = shaderCode.c_str();
    glShaderSource(shaderID, 1, &shaderSourcePointer, NULL);
    glCompileShader(shaderID);

    printf("Checking shader: %s\n", shader_file_path);
    GLint compile_result = GL_FALSE;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compile_result);
    if (compile_result != GL_TRUE) {
        printf("Shader %s was not compiled!\n", shader_file_path);
        int logLength;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);

        std::vector<char> errorMessage(logLength);
        glGetShaderInfoLog(shaderID, logLength, NULL, errorMessage.data());

        std::cout << "Compile log:" << std::endl << std::string(errorMessage.data()) << std::endl;
    }

    std::cout << "------------------------" << std::endl;
}

GLuint LinkProgram(shaders &s, const char *attributeLocations[], GLuint numberOfLocations)
{
    printf("Linking program...\n");
    GLuint programID = glCreateProgram();

    for (GLuint i = 0; i < numberOfLocations; ++i) {
        glBindAttribLocation(programID, i, attributeLocations[i]);
    }

    glAttachShader(programID, s.vertex);
    glAttachShader(programID, s.fragment);

    if (s.geometry)
        glAttachShader(programID, s.geometry);
    if (s.tess_control)
        glAttachShader(programID, s.tess_control);
    if (s.tess_eval)
        glAttachShader(programID, s.tess_eval);

    glLinkProgram(programID);

    printf("Checking linking program... ");
    GLint link_result = GL_FALSE;
    glGetProgramiv(programID, GL_LINK_STATUS, &link_result);
    printf("%s!\n", link_result ? "success" : "failed");

    if (link_result != GL_TRUE) {
        printf("Program was not linked!\n");
        int logLength;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);

        std::vector<char> errorMessage(logLength);
        glGetProgramInfoLog(programID, logLength, NULL, errorMessage.data());
        std::cout << "Linking log:" << std::endl << std::string(errorMessage.data()) << std::endl;
    }
    s.free();
    std::cout << "#########################" << std::endl;
    return programID;
}

GLuint LoadShaders(const char *vertex_file_path,
                   const char *fragment_file_path,
                   const char *geometry_file_path,
                   const char *tess_control_file_path,
                   const char *tess_eval_file_path,
                   const char *attributeLocations[],
                   GLuint numberOfLocations)
{
    GLuint v = 0;
    if (vertex_file_path) {
        v = glCreateShader(GL_VERTEX_SHADER);
        LoadShader(v, vertex_file_path);
    }

    GLuint f = 0;
    if (fragment_file_path) {
        f = glCreateShader(GL_FRAGMENT_SHADER);
        LoadShader(f, fragment_file_path);
    }

    GLuint g = 0;
    if (geometry_file_path) {
        g = glCreateShader(GL_GEOMETRY_SHADER);
        LoadShader(g, geometry_file_path);
    }

    GLuint tc = 0;
    if (tess_control_file_path) {
        tc = glCreateShader(GL_TESS_CONTROL_SHADER);
        LoadShader(tc, tess_control_file_path);
    }

    GLuint te = 0;
    if (tess_eval_file_path) {
        te = glCreateShader(GL_TESS_EVALUATION_SHADER);
        LoadShader(te, tess_eval_file_path);
    }

    shaders s(v, f, g, tc, te);
    return LinkProgram(s, attributeLocations, numberOfLocations);
}
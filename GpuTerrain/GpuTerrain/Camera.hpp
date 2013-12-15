#ifndef GpuTerrain_Camera_hpp
#define GpuTerrain_Camera_hpp

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

struct Camera {
    vec3 pos;
    vec3 translate;
    vec3 rot;

    vec3 up;
    vec3 lookPos;

    float fovy;
    float fovx;
    float aspect;
    float near;
    float far;

    float left;
    float right;
    float bottom;
    float top;

    int width;
    int height;

    Camera(int window_width, int window_height) : width(window_width), height(window_height)
    {
        pos = glm::vec3(0, 5, -1);
        translate = glm::vec3(0, 0, 0);
        rot = glm::vec3(0, 0, 0);

        up = glm::vec3(0, 1, 0);
        lookPos = glm::vec3(0, 0, -200);

        fovy = 60.0;
        aspect = width / height;
        fovx = atan(aspect * tan(fovy * M_PI / 180.0 / 2.0)) * 2.0;
        fovx *= 180.0 / M_PI;
        near = 3.0f;
        far = 200.0f;

        left = -10;
        right = 10;
        bottom = -10;
        top = 10;
    }

    glm::mat4 GetViewTransform()
    {
        glm::mat4 model_view = glm::lookAt(pos + translate, lookPos, up);
        model_view *= glm::rotate(model_view, rot.x, glm::vec3(1, 0, 0)) *
                      glm::rotate(model_view, rot.y, glm::vec3(0, 1, 0)) *
                      glm::rotate(model_view, rot.z, glm::vec3(0, 0, 1));

        return model_view;
    }

    glm::mat4 GetPerspective()
    {
        glm::mat4 persp = glm::perspective(fovy, aspect, near, far);
        left = near * (persp[0][2] - 1) / persp[0][0];
        right = near * (persp[0][2] + 1) / persp[0][0];
        bottom = near * (persp[1][2] - 1) / persp[1][1];
        top = near * (persp[1][2] + 1) / persp[1][1];
        return persp;
    }
};

#endif

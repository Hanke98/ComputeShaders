//
// Created by ljf on 2020/6/22.
//

#include "BaseRender.h"
#include <iostream>


BaseRender::BaseRender(Param& param): 
        window(nullptr),
        shader(nullptr),
        height(param.height),
        width(param.width),
        v_glsl(param.vertex_shader),
        f_glsl(param.fragment_shader)
{

}

BaseRender::~BaseRender() {

}

void BaseRender::Initialize() {
    if (!glfwInit()) {
        std::cout << "init glfw error" << std::endl;
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
//    glfwWindowHint(GLFW_SAMPLES, 16);

    window = glfwCreateWindow(height, width, "ComputeShaders", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "create window error" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        return;
    }
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//    glfwSetCursorPosCallback(window, MouseFunc);

    glEnable(GL_DEPTH_TEST);

}

bool BaseRender::Step() {
    ProcessInput();
    glfwSwapBuffers(window);
    glfwPollEvents();
    return glfwWindowShouldClose(window) == GL_TRUE;
}

void BaseRender::Draw() {
    glClearColor(0.4, 0.5, 0.6, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader->Use();
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 9);
}

void BaseRender::ProcessInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void BaseRender::InitData() {

    float data[] = {
            -1, -1, 0,
            1, -1, 0,
            0, 1, 0
    };

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    VAOs.push_back(vao);
    VBOs.push_back(vbo);
}

void BaseRender::InitShaders() {
    shader = new Shader(v_glsl.data(), f_glsl.data());
}

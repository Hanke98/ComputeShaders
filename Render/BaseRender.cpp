//
// Created by ljf on 2020/6/22.
//

#include "BaseRender.h"
#include <iostream>
#include <cassert>


BaseRender::BaseRender(Param& param): 
        window(nullptr),
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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
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
    InitShaders();
    InitTextures();
    InitData();
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
    shaders[0]->Use();
    glBindVertexArray(VAOs[0]);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex_output);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void BaseRender::ProcessInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void BaseRender::InitData() {

    float data[] = {
            0.8f,  0.8f, 0.0f,  1.0f, 1.0f,   // 右上
            0.8f, -0.8f, 0.0f,  1.0f, 0.0f,   // 右下
            -0.8f, -0.8f, 0.0f,  0.0f, 0.0f,   // 左下
            -0.8f,  0.8f, 0.0f,  0.0f, 1.0f    // 左上
    };

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float )));
    glEnableVertexAttribArray(1);
    VAOs.push_back(vao);
    VBOs.push_back(vbo);
}

void BaseRender::InitShaders() {
    auto* shader = new Shader(v_glsl.data(), f_glsl.data());
    shaders.emplace_back(shader);
    auto* compute_shader = new Shader("../glsl/compute.glsl");
    shaders.emplace_back(compute_shader);
    CheckWorkGroupMaxValue();
}

void BaseRender::InitTextures() {
    int size = width * 0.8 * height * 0.8 * 4;
    float *data = new float [size];
    for(int i = 0; i < size; i+=4) {
        data[i] = 0.5f;
        data[i + 1] = 0.f;
        data[i + 2] = 0.f;
        data[i + 3] = 1.f;
    }

    glGenTextures(1, &tex_output);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex_output);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width * 0.8, height * 0.8, 0, GL_RGBA, GL_FLOAT,data);
    glBindImageTexture(0, tex_output, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
}

void BaseRender::RunComputeShader() {
    assert(shaders.size() >= 1);
    assert(shaders[1]);
    shaders[1]->Use();

    glDispatchCompute(width/24, height/24, 1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

void BaseRender::CheckWorkGroupMaxValue() {
    int work_grp_cnt[3];

    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &work_grp_cnt[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &work_grp_cnt[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &work_grp_cnt[2]);

    printf("max global (total) work group counts x:%i y:%i z:%i\n",
           work_grp_cnt[0], work_grp_cnt[1], work_grp_cnt[2]);
    int work_grp_size[3];

    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &work_grp_size[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &work_grp_size[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &work_grp_size[2]);

    printf("max local (in one shader) work group sizes x:%i y:%i z:%i\n",
           work_grp_size[0], work_grp_size[1], work_grp_size[2]);
}

void BaseRender::Start() {
    time_st = glfwGetTime();
}

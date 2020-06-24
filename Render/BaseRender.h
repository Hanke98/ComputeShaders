//
// Created by ljf on 2020/6/22.
//

#ifndef COMPUTESHADERS_BASERENDER_H
#define COMPUTESHADERS_BASERENDER_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include "Shader.h"

class BaseRender {
public:
    struct Param{
        double height;
        double width;
        std::string vertex_shader;
        std::string fragment_shader;
    };

    explicit BaseRender(Param& param);
    virtual ~BaseRender(); 

    void Initialize();
    bool Step();
    void Draw();
    void Start();

    void RunComputeShader();

protected:
    GLFWwindow *window;
    std::vector<Shader*> shaders;
    double height;
    double width;

    std::string v_glsl;
    std::string f_glsl;

    std::vector<GLuint> VAOs;
    std::vector<GLuint> VBOs;
    GLuint tex_output;

    void ProcessInput();
    void InitData();
    void InitShaders();
    void InitTextures();

    void CheckWorkGroupMaxValue();

    double time_st;

};


#endif //COMPUTESHADERS_BASERENDER_H

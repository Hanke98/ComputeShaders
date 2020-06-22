//
// Created by ljf on 2020/6/22.
//

#ifndef COMPUTESHADERS_BASERENDER_H
#define COMPUTESHADERS_BASERENDER_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class BaseRender {

    struct Param{
        std::string vertex_shader;
        std::string fragment_shader;
    };

    explicit BaseRender(Param& param) ;
    virtual ~BaseRender()
protected:
    GLFWwindow *window;
};


#endif //COMPUTESHADERS_BASERENDER_H

#include <iostream>
#include "Render/BaseRender.h"

int main() {
    BaseRender::Param param;
    param.height = 600;
    param.width = 600;
    param.vertex_shader = "/Users/liujiafeng/learning/ComputeShaders/glsl/v.glsl";
    param.fragment_shader = "/Users/liujiafeng/learning/ComputeShaders/glsl/f.glsl";

    BaseRender* render = new BaseRender(param);
    render->Initialize();
    render->InitShaders();
    render->InitData();


    while (true) {
        render->Draw();
        if (render->Step()) break;
    }
    delete render;
    return 0;
}

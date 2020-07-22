#include <iostream>
#include "Render/BaseRender.h"
#include "Render/ParticleRender.h"
#include <unistd.h>

int main() {
    BaseRender::Param param;
    param.height = 600;
    param.width = 600;
    param.vertex_shader = "../glsl/v.glsl";
    param.fragment_shader = "../glsl/f.glsl";

    BaseRender* render = new BaseRender(param);

//    BaseRender::Param param;
//    param.height = 600;
//    param.width  = 600;
//    param.vertex_shader = "../glsl/v_particle.glsl";
//    param.fragment_shader = "../glsl/f.glsl";
//
//    BaseRender* render = new ParticleRender(param);

    render->Initialize();
    bool flag = true;
    while (true) {
        render->RunComputeShader();
        render->Draw();
        if (flag) {
            flag = false;
        }
        usleep(100000/60);
        if (render->Step()) break;
    }
    delete render;
    return 0;
}

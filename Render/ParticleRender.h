//
// Created by ljf on 2020/6/30.
//

#ifndef COMPUTESHADERS_PARTICLERENDER_H
#define COMPUTESHADERS_PARTICLERENDER_H
#include "BaseRender.h"

class ParticleRender : public BaseRender{

public:
    ParticleRender(Param &param);

    ~ParticleRender() override;
    void Draw() override;

    void RunComputeShader() override;

protected:
    void InitData() override;
    void InitShaders() override;
    void InitTextures() override;

    GLuint velocity_vbo;
    GLuint position_vbo;
    GLuint velocity_tbo;
    GLuint position_tbo;
};


#endif //COMPUTESHADERS_PARTICLERENDER_H

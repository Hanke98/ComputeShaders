//
// Created by ljf on 2020/6/30.
//

#include "ParticleRender.h"
#include "../Utils/MathUtils.h"
#include <cassert>

enum
{
    PARTICLE_GROUP_SIZE     = 1024,
    PARTICLE_GROUP_COUNT    = 8192,
    PARTICLE_COUNT          = (PARTICLE_GROUP_SIZE * PARTICLE_GROUP_COUNT),
    MAX_ATTRACTORS          = 64
};


ParticleRender::ParticleRender(BaseRender::Param &param) : BaseRender(param) {

}

ParticleRender::~ParticleRender() {

}

void ParticleRender::InitData() {
    // gen vao
    GLuint vao;
    glGenVertexArrays(1, &vao);
    VAOs.push_back(vao);

    // init buffer
    glGenBuffers(1, &velocity_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, velocity_vbo);
    int buffer_size = PARTICLE_COUNT * sizeof(float ) * 4;
    glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_DYNAMIC_COPY);
    auto * velocity = (float *)glMapBufferRange(GL_ARRAY_BUFFER,
                                              0,
                                              buffer_size,
                                              GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
    for(int i = 0; i < buffer_size; i+=4) {
        velocity[i] = MathUtils::RandomFloat(-0.1, 0.1);
        velocity[i + 1] = MathUtils::RandomFloat(-0.1, 0.1);
        velocity[i + 2] = 0;
        velocity[i + 3] = 0;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);

    glGenBuffers(1, &position_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
    glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_DYNAMIC_COPY);
    auto * position = (float *)glMapBufferRange(GL_ARRAY_BUFFER,
                                                0,
                                                buffer_size,
                                                GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
    for(int i = 0; i < buffer_size; i+=4) {
        position[i] = 0;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);

    // gen texture
    glGenTextures(1, &velocity_tbo);
    glGenTextures(1, &velocity_tbo);

    glBindTexture(GL_TEXTURE_BUFFER, velocity_tbo);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, velocity_vbo);

    glBindTexture(GL_TEXTURE_BUFFER, position_tbo);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, position_vbo);


}

void ParticleRender::Draw() {
}

void ParticleRender::InitShaders() {
    auto* shader = new Shader(v_glsl.data(), f_glsl.data());
    shaders.emplace_back(shader);
    auto* compute_shader = new Shader("../glsl/c_particle.glsl");
    shaders.emplace_back(compute_shader);
    CheckWorkGroupMaxValue();
}

void ParticleRender::InitTextures() {

}

void ParticleRender::RunComputeShader() {

}


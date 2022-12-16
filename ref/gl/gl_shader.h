#ifndef GL_SHADER_H
#define GL_SHADER_H

#include "shaders/gl_shader_test.h"
#include "shaders/gl_shader_ao.h"

enum
{
	GL_SHADER_NONE = -1,
    GL_SHADER_TEST,     // pp no-op
    GL_SHADER_AO,       // pp ambient occlusion
    GL_SHADER_MAX,
};

static char* SHADER_VERT_SOURCES[] = {
    SHADER_VERT_TEST,
    SHADER_VERT_AO,
};

static char* SHADER_FRAG_SOURCES[] = {
    SHADER_FRAG_TEST,
    SHADER_FRAG_AO,
};

#endif // GL_SHADER_H

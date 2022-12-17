#ifndef GL_SHADER_H
#define GL_SHADER_H

#include "shaders/gl_shader_test.h"
#include "shaders/gl_shader_cc.h"
#include "shaders/gl_shader_cabr.h"
#include "shaders/gl_shader_vignette.h"

enum
{
	GL_SHADER_NONE = -1,
    GL_SHADER_TEST,     // pp no-op
    GL_SHADER_CC,       // pp color correction
    GL_SHADER_VIGNETTE, // pp vignette
    GL_SHADER_CABR,     // pp chromatic aberration
    GL_SHADER_MAX,
};

static char* SHADER_VERT_SOURCES[] = {
    SHADER_VERT_TEST,
    SHADER_VERT_CC,
    SHADER_VERT_VIGNETTE,
    SHADER_VERT_CABR,
};

static char* SHADER_FRAG_SOURCES[] = {
    SHADER_FRAG_TEST,
    SHADER_FRAG_CC,
    SHADER_FRAG_VIGNETTE,
    SHADER_FRAG_CABR,
};

#endif // GL_SHADER_H

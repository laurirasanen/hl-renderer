#ifndef GL_SHADER_H
#define GL_SHADER_H

enum
{
	GL_SHADER_NONE = -1,
    GL_SHADER_TEST,
    GL_SHADER_MAX,
};

static char SHADER_VERT_TEST[] =
    "#version 330 core\n"

    "layout(location = 0) in vec2 a_pos;\n"

    "out vec2 uv;\n"

    "void main()\n"
    "{\n"
        "gl_Position = vec4(a_pos, 0, 1.0);\n"
        "uv.xy = vec2(max(0, a_pos.x), max(0, a_pos.y));\n"
    "}";

static char SHADER_FRAG_TEST[] =
    "#version 330 core\n"

    "in vec2 uv;\n"

    "uniform sampler2D uTex;\n"

    "out vec4 fragColor;\n"

    "void main()\n"
    "{\n"
        "fragColor = texture(uTex, uv);\n"
    "}";

static char* SHADER_VERT_SOURCES[] = {
    SHADER_VERT_TEST
};

static char* SHADER_FRAG_SOURCES[] = {
    SHADER_FRAG_TEST
};

#endif // GL_SHADER_H

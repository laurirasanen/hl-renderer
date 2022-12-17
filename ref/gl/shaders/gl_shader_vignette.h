#ifndef GL_SHADER_VIGNETTE_H
#define GL_SHADER_VIGNETTE_H

static char SHADER_VERT_VIGNETTE[] =
    "#version 330 core\n"

    "layout(location = 0) in vec2 a_pos;\n"

    "out vec2 uv;\n"

    "void main()\n"
    "{\n"
        "gl_Position = vec4(a_pos, 0, 1.0);\n"
        "uv.xy = vec2(max(0, a_pos.x), max(0, a_pos.y));\n"
    "}";

static char SHADER_FRAG_VIGNETTE[] =
    "#version 330 core\n"

    "in vec2 uv;\n"

    "uniform sampler2D uTex;\n"
    "uniform float uStrength;\n"
    "uniform float uDistance;\n"
    "uniform float uCurvature;\n"

    "out vec4 fragColor;\n"

    "void main()\n"
    "{\n"
        "vec4 tex = texture(uTex, uv);\n"
        
        "vec2 curve = pow(abs(uv * 2.0 - 1.0), vec2(1.0 / uCurvature));\n"
        "float dist = pow(length(curve), uCurvature);\n"
        "float vig = 1.0 - uStrength * smoothstep(uDistance, 1.0, dist);\n"

        "tex.rgb *= vig;\n"
        "fragColor = tex;\n"
    "}";

#endif // GL_SHADER_VIGNETTE_H
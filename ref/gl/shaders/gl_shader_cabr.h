#ifndef GL_SHADER_CABR_H
#define GL_SHADER_CABR_H

static char SHADER_VERT_CABR[] =
    "#version 330 core\n"

    "layout(location = 0) in vec2 a_pos;\n"

    "out vec2 uv;\n"

    "void main()\n"
    "{\n"
        "gl_Position = vec4(a_pos, 0, 1.0);\n"
        "uv.xy = vec2(max(0, a_pos.x), max(0, a_pos.y));\n"
    "}";

static char SHADER_FRAG_CABR[] =
    "#version 330 core\n"

    "in vec2 uv;\n"

    "uniform sampler2D uTex;\n"
    "uniform float uStrength;\n"
    "uniform float uDistance;\n"
    "uniform float uBias;\n"

    "out vec4 fragColor;\n"

    "void main()\n"
    "{\n"
        "vec4 tex = texture(uTex, uv);\n"

        "float bias = distance(uv, vec2(0.5)) * uBias;\n"

        "vec3 abbr;\n"
        "abbr.r += texture(uTex, uv + uDistance / 100.0).r;\n"
        "abbr.g = tex.g;\n"
        "abbr.b += texture(uTex, uv - uDistance / 100.0).b;\n"

        "fragColor = tex;\n"
        "fragColor.rgb = mix(fragColor.rgb, abbr, uStrength + bias);\n"
    "}";

#endif // GL_SHADER_CABR_H
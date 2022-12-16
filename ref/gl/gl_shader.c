#include "gl_local.h"
#include "gl_shader.h"

static GLhandleARB gl_shaders[GL_SHADER_MAX];
static uint gl_numShaders;

void R_ShaderInit( void )
{
    gEngfuncs.Con_Printf( S_OPENGL_NOTE "R_ShaderInit()\n" );
    gl_numShaders = 0;
    for (size_t i = 0; i < GL_SHADER_MAX; i++)
    {
        R_ShaderProgramCompile(SHADER_VERT_SOURCES[i], SHADER_FRAG_SOURCES[i]);
    }
}

GLhandleARB R_ShaderCompile( const GLcharARB *src, GLenum type )
{
    int tmp = -1;
    char *log;

    GLhandleARB handle = pglCreateShaderObjectARB(type);
    pglShaderSourceARB(handle, 1, &src, &tmp);
    pglCompileShaderARB(handle);

    pglGetObjectParameterivARB(handle, GL_OBJECT_COMPILE_STATUS_ARB, &tmp);
    if (!tmp)
    {
        pglGetObjectParameterivARB(handle, GL_OBJECT_INFO_LOG_LENGTH_ARB, &tmp);
        log = Mem_Malloc(r_temppool, tmp);
        pglGetInfoLogARB(handle, tmp, &tmp, log);
        gEngfuncs.Con_Printf( S_OPENGL_ERROR "Compiling shader src:\n%s\n", src );
        gEngfuncs.Con_Printf( S_OPENGL_ERROR "%s\n", log );
        ASSERT( false );
    }

    return handle;
}

void R_ShaderProgramCompile( const GLcharARB *vertSrc, const GLcharARB *fragSrc )
{
    GLhandleARB vertShader = 0;
    GLhandleARB fragShader = 0;
    GLhandleARB program = pglCreateProgramObjectARB();

    ASSERT( gl_numShaders < GL_SHADER_MAX );

    if (vertSrc)
    {
        vertShader = R_ShaderCompile(vertSrc, GL_VERTEX_SHADER_ARB);
        pglAttachObjectARB(program, vertShader);
    }
    if (fragSrc)
    {
        fragShader = R_ShaderCompile(fragSrc, GL_FRAGMENT_SHADER_ARB);
        pglAttachObjectARB(program, fragShader);
    }

    pglLinkProgramARB(program);

    if (vertShader)
    {
        pglDeleteObjectARB(vertShader);
    }
    if (fragShader)
    {
        pglDeleteObjectARB(fragShader);
    }

    gEngfuncs.Con_Printf( S_OPENGL_NOTE "Compiled shader %u\n", gl_numShaders );

    gl_shaders[gl_numShaders] = program;
    gl_numShaders++;
}

void R_ShaderUse( int prog )
{
    ASSERT( prog >= GL_SHADER_NONE && prog < GL_SHADER_MAX );

    if (prog == GL_SHADER_NONE)
    {
        pglUseProgramObjectARB(0);
    }

    pglUseProgramObjectARB(gl_shaders[prog]);
}

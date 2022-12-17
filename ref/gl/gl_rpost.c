#include "gl_rpost.h"
#include "gl_local.h"
#include "gl_shader.h"
#include "xash3d_mathlib.h"
#include "cvar.h"

static CVAR_DEFINE_AUTO( gl_cg_red,   "1.0", FCVAR_ARCHIVE|FCVAR_FILTERABLE, "color grading red"   );
static CVAR_DEFINE_AUTO( gl_cg_green, "1.0", FCVAR_ARCHIVE|FCVAR_FILTERABLE, "color grading green" );
static CVAR_DEFINE_AUTO( gl_cg_blue,  "1.0", FCVAR_ARCHIVE|FCVAR_FILTERABLE, "color grading blue"  );
static CVAR_DEFINE_AUTO( gl_cg_gamma, "1.0", FCVAR_ARCHIVE|FCVAR_FILTERABLE, "color grading gamma" );

static CVAR_DEFINE_AUTO( gl_vignette_strength,  "0.2", FCVAR_ARCHIVE|FCVAR_FILTERABLE, "vignette strength" );
static CVAR_DEFINE_AUTO( gl_vignette_distance,  "0.8", FCVAR_ARCHIVE|FCVAR_FILTERABLE, "vignette distance" );
static CVAR_DEFINE_AUTO( gl_vignette_curvature, "0.3", FCVAR_ARCHIVE|FCVAR_FILTERABLE, "vignette curvature" );

//static gl_texture_t* post_texture = NULL;
static unsigned int post_texture = 0;

void R_InitPost( void )
{
    gEngfuncs.Cvar_RegisterVariable( (cvar_t *)&gl_cg_red );
    gEngfuncs.Cvar_RegisterVariable( (cvar_t *)&gl_cg_green );
    gEngfuncs.Cvar_RegisterVariable( (cvar_t *)&gl_cg_blue );
    gEngfuncs.Cvar_RegisterVariable( (cvar_t *)&gl_cg_gamma );

    gEngfuncs.Cvar_RegisterVariable( (cvar_t *)&gl_vignette_strength );
    gEngfuncs.Cvar_RegisterVariable( (cvar_t *)&gl_vignette_distance );
    gEngfuncs.Cvar_RegisterVariable( (cvar_t *)&gl_vignette_curvature );

    //post_texture = GL_AllocTexture( POST_TEXTURE, TF_NEAREST );
    pglGenTextures( 1, &post_texture );
}

/*
================
R_DrawPost
================
*/
void R_DrawPost( void )
{
    // ASSERT( post_texture > 0 );

    pglEnable( GL_TEXTURE_2D );
    pglDisable( GL_BLEND );
    pglDisable( GL_CULL_FACE );

    // pglTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
    // pglTexEnvi( GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_REPLACE );
    // pglTexEnvi( GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB, GL_TEXTURE );

    // pglMatrixMode( GL_TEXTURE );
    // pglLoadIdentity();
    // pglScalef( 1, 1, 1 );

    pglReadBuffer( GL_BACK );
    pglDrawBuffer( GL_BACK );

    GL_SelectTexture( XASH_TEXTURE0 );
    pglBindTexture( GL_TEXTURE_2D, post_texture );

    //R_PostTest();
    R_PostCC();
    R_PostVignette();

    R_ShaderUse( GL_SHADER_NONE );
    // pglBindTexture( GL_TEXTURE_2D, 0 );
    pglEnable( GL_CULL_FACE );
}

void R_PostRead( void )
{
    int width = gpGlobals->width;
    int height = gpGlobals->height;
    pglCopyTexImage2D( GL_TEXTURE_2D, 0, GL_RGB8, 0, 0, width, height, 0 );
}

void R_PostWrite( void )
{
    pglClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    pglBegin( GL_QUADS );
		pglVertex2f( -1.0f, -1.0f );
		pglVertex2f(  1.0f, -1.0f );
		pglVertex2f(  1.0f,  1.0f );
		pglVertex2f( -1.0f,  1.0f );
	pglEnd();
}

void R_PostTest( void )
{
    R_PostRead();
    R_ShaderUse( GL_SHADER_TEST );
    R_PostWrite();
}

void R_PostCC( void )
{
    R_PostRead();
    R_ShaderUse( GL_SHADER_CC );
    pglUniform3fARB( 1, gl_cg_red.value, gl_cg_green.value, gl_cg_blue.value );
    pglUniform1fARB( 2, gl_cg_gamma.value );
    R_PostWrite();
}

void R_PostVignette( void )
{
    R_PostRead();
    R_ShaderUse( GL_SHADER_VIGNETTE );
    pglUniform1fARB( 1, gl_vignette_strength.value );
    pglUniform1fARB( 2, gl_vignette_distance.value );
    pglUniform1fARB( 3, gl_vignette_curvature.value );
    R_PostWrite();
}
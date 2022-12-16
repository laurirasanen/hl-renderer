#include "gl_rpost.h"
#include "gl_local.h"
#include "gl_shader.h"
#include "xash3d_mathlib.h"

//static gl_texture_t* post_texture = NULL;
static unsigned int post_texture = 0;

void R_InitPost( void )
{
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
    ASSERT( post_texture > 0 );

    pglEnable( GL_TEXTURE_2D );
    pglDisable( GL_BLEND );
    pglDisable( GL_CULL_FACE );

    pglMatrixMode( GL_TEXTURE );
    pglLoadIdentity();
    pglScalef( 1, 1, 1 );

    pglReadBuffer( GL_BACK );
    pglDrawBuffer( GL_BACK );

    GL_SelectTexture( XASH_TEXTURE5 );
    pglBindTexture( GL_TEXTURE_2D, post_texture );

    R_PostNuke();

    GL_SelectTexture( XASH_TEXTURE0 );
    R_ShaderUse( GL_SHADER_NONE );
    pglBindTexture( GL_TEXTURE_2D, 0 );
    pglEnable( GL_CULL_FACE );
}

void R_PostRead( void )
{
    int width = gpGlobals->width;
    int height = gpGlobals->height;
    pglCopyTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, 0, 0, width, height, 0 );
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

void R_PostNuke( void )
{
    R_PostRead();
    R_ShaderUse( GL_SHADER_TEST );
    R_PostWrite();
}
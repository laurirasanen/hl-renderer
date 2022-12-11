#include "gl_local.h"
#include "xash3d_mathlib.h"

/*
================
R_DrawPost
================
*/
void R_DrawPost( void )
{
    char *buffer;
    int tempsize = 100;
    int width = gpGlobals->width;
    int height = gpGlobals->height;
    int stride = 4;
    int size = width * height * stride;

    pglDisable( GL_TEXTURE_2D );
    pglDisable( GL_BLEND );
    pglReadBuffer( GL_BACK );
    pglDrawBuffer( GL_BACK );

	buffer = Mem_Malloc( r_temppool, size );
    pglReadPixels( 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer );

    R_PostNuke( buffer, width, height, stride, size );

    // FIXME: read/draw pixels is very slow.
    // this is just to get things up and running
    pglDrawPixels( width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer );

    Mem_Free( buffer );

    pglEnable( GL_TEXTURE_2D );
	pglDisable( GL_BLEND );
}

void R_PostNuke( char *buffer, int width, int height, int stride, int size )
{
    for ( size_t i = 0; i < size; i++ )
    {
        buffer[i] += 128;
    }    
}
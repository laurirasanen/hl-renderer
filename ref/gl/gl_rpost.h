#ifndef GL_POST_H
#define GL_POST_H

static char POST_TEXTURE[] = "post_texture";

void R_PostRead( void );
void R_PostPass( void );
void R_PostTest( void );
void R_PostCC( void );
void R_PostChromaticAberration( void );
void R_PostVignette( void );

#endif // GL_POST_H
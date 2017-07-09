#include <GL/glew.h>
#include <SDL2/SDL.h>



int main(){

    GLenum err = glewInit();

    int attribs[] =
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 1,
        WGL_CONTEXT_FLAGS_ARB, 0,
        0
    };

    m_hrc = wglCreateContextAttribsARB(pDC->m_hDC,0, attribs);
    
    wglMakeCurrent(NULL,NULL);
    wglDeleteContext(tempContext);



    return 0;
}

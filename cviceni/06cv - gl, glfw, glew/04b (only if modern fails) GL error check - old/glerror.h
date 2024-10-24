#ifndef __glerror_h__
#define __glerror_h__

#include <GLFW/glfw3.h>

const char * explain_gl_error(const GLenum errcode);
void gl_check_error(void);

#endif __glerror_h__

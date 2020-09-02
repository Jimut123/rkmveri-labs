#ifndef Z_SHADER_H_INCLUDED
#define Z_SHADER_H_INCLUDED

extern GLuint opengl_createshader(GLenum, const char *);
extern void opengl_deleteshader(GLuint);

extern GLuint opengl_createprogram(GLuint *, GLuint *);

//extern GLuint opengl_createvao(void);
//extern GLuint opengl_createvbo(const GLvoid *, GLuint);

#endif

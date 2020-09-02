#ifndef Z_MAT_H_INCLUDED
#define Z_MAT_H_INCLUDED

#include <GL/glew.h>

extern void sub_vec3(GLfloat[3], GLfloat[3], GLfloat[]);

extern void add_vec3(GLfloat[3], GLfloat[3], GLfloat[]);
extern void add_mat4(GLfloat[4][4], GLfloat[4][4], GLfloat[][4]);

void mult_mat4(GLfloat[4][4], GLfloat[4][4], GLfloat[][4]);

extern void cross_vec3(GLfloat[3], GLfloat[3], GLfloat[]);
extern GLfloat dot_vec3(GLfloat[3], GLfloat[3]);

extern void normalize_vec3(GLfloat[]);
extern void mult_mat4(GLfloat[4][4], GLfloat[4][4], GLfloat[][4]);

extern void set_identity_mat4(GLfloat[][4]);

extern void zero_vec3(GLfloat v[]);
extern void unit_vec3(GLfloat v[]);

extern void set_vec2(GLfloat, GLfloat, GLfloat v[]);
extern void set_vec3(GLfloat, GLfloat, GLfloat, GLfloat v[]);
extern void set_vec4(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat v[]);

extern void copy_vec2(GLfloat[2], GLfloat[]);
extern void copy_vec3(GLfloat[3], GLfloat[]);
extern void copy_vec4(GLfloat[4], GLfloat[]);

extern void copy_mat3(GLfloat[4][4], GLfloat[][3]);
extern void copy_mat4(GLfloat[4][4], GLfloat[][4]);

extern void transpose_mat4(GLfloat[4][4], GLfloat[][4]);

extern void print_mat2(char *, GLfloat[][3]);
extern void print_mat3(char *, GLfloat[][3]);
extern void print_mat4(char *, GLfloat[][4]);

extern void print_vec3(char *, GLfloat[]);
extern void print_vec4(char *, GLfloat[]);

extern void inverse_mat2(GLfloat[3][3], GLfloat[][3]);
extern void inverse_mat3(GLfloat[3][3], GLfloat[][3]);
extern void inverse_mat4(GLfloat[4][4], GLfloat[][4]);

#endif

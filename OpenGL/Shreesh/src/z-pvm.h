#ifndef Z_PVM_H_INCLUDED
#define Z_PVM_H_INCLUDED

extern void pvm_calculate_model_mat4(GLfloat[3], GLfloat[3], GLfloat[3],
				     GLfloat, GLfloat[][4]);
extern void pvm_calculate_view_mat4(GLfloat[3], GLfloat[3], GLfloat[3],
				    GLfloat[][4]);
extern void pvm_calculate_proj_mat4(GLfloat, GLfloat, GLfloat, GLfloat,
				    GLfloat[][4]);

extern GLfloat degtorad(GLfloat);
extern GLfloat radtodeg(GLfloat);

#endif

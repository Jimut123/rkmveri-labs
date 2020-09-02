#ifndef Z_WORLD_H_INCLUDED
#define Z_WORLD_H_INCLUDED

#include "z-models.h"
#include "z-materials.h"

struct object_st {
    int id;
    char *name;

    struct model_st *model;
    struct material_st *material;

    struct modelblk_st {
	GLfloat modelmat[4][4];
	GLfloat normalmat[4][4];
    } modelblk;

    GLint modelblk_offset;
    GLint modelblk_size;

    GLfloat translate[3];
    GLfloat scale[3];
    GLfloat rotate_axis[3];
    GLfloat rotate_angle;

};

extern void world_init(GLfloat, GLfloat, GLfloat);

extern void obj_abs_translate(struct object_st *, GLfloat, GLfloat, GLfloat);
extern void obj_abs_scale(struct object_st *, GLfloat, GLfloat, GLfloat);
extern void obj_abs_rotate(struct object_st *, GLfloat, GLfloat, GLfloat,
			   GLfloat);
extern void obj_set_material(struct object_st *, int);

extern void obj_set_modelblk_offset(struct object_st *, int);
extern void obj_set_modelblk_size(struct object_st *, int);

extern void calculate_model_mat4(struct object_st *);
extern void calculate_normal_mat4(struct object_st *);

extern struct object_st *obj_create_object(char *, struct model_st *,
					   struct material_st *);

#endif

#ifndef Z_LIGHT_H_INCLUDED
#define Z_LIGHT_H_INCLUDED

#include <GL/glew.h>

#define MAXLIGHTS 4

struct light_st {
    struct lightblk_st {
	GLfloat ambience[3];
	GLfloat _pad1;
	GLfloat emission[MAXLIGHTS][4];
	GLfloat pos[MAXLIGHTS][4];
	GLuint num;
    } lightblk;

    int lightblk_offset;
    int lightblk_size;
};

extern void light_init(struct light_st *);

extern struct light_st *light_create_light(void);
extern void light_set_light(struct light_st *, int, GLfloat[3], GLfloat[3]);
extern void light_set_ambience(struct light_st *, GLfloat[3]);

extern void light_set_lightblk_offset(struct light_st *, int);
extern void light_set_lightblk_size(struct light_st *, int);

#endif

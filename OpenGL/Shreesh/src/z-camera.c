#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include <GL/glew.h>

#include "z-mat.h"
#include "z-pvm.h"

#include "z-camera.h"

void camera_init(struct scene_st *c)
{
    set_vec3(1.5f, -1.5f, 1.5f, c->sceneblk.camera_position);
    set_vec3(0.0f, 0.0f, 0.0f, c->sceneblk.camera_target);
    set_vec3(0.0f, 0.0f, 1.0f, c->sceneblk.camera_up);

    c->camera_fovy = 90.0f * M_PI / 180.0f;
    c->camera_aspect = 4.0f / 3.0f;
    c->camera_znear = 1.0f;
    c->camera_zfar = 10.0f;

}

struct scene_st *camera_create_scene(void)
{
    struct scene_st *tmp;

    tmp = (struct scene_st *)malloc(sizeof(struct scene_st));
    if (tmp == NULL) {
	perror("Cannot allocate memory for scene_st");
    }
}

GLfloat camera_set_fovy(struct scene_st *sc, GLfloat val)
{
    GLfloat oldval;

    oldval = sc->camera_fovy;
    sc->camera_fovy = val;
    return oldval;
}

GLfloat camera_get_fovy(struct scene_st * sc)
{
    return sc->camera_fovy;
}

GLfloat camera_set_aspect(struct scene_st * sc, GLfloat val)
{
    GLfloat oldval;

    oldval = sc->camera_aspect;
    sc->camera_aspect = val;
    return oldval;
}

GLfloat camera_get_aspect(struct scene_st * sc)
{
    return sc->camera_aspect;
}

GLfloat camera_set_znear(struct scene_st * sc, GLfloat val)
{
    GLfloat oldval;

    oldval = sc->camera_znear;
    sc->camera_znear = val;
    return oldval;
}

GLfloat camera_get_znear(struct scene_st * sc)
{
    return sc->camera_znear;
}

GLfloat camera_set_zfar(struct scene_st * sc, GLfloat val)
{
    GLfloat oldval;

    oldval = sc->camera_zfar;
    sc->camera_zfar = val;
    return oldval;
}

GLfloat camera_get_zfar(struct scene_st * sc)
{
    return sc->camera_zfar;
}

void camera_set_position(struct scene_st *sc, GLfloat p[3])
{
    for (int i = 0; i < 3; i++)
	sc->sceneblk.camera_position[i] = p[i];
}

void camera_get_position(struct scene_st *sc, GLfloat p[])
{
    for (int i = 0; i < 3; i++)
	p[i] = sc->sceneblk.camera_position[i];
}

void camera_set_target(struct scene_st *sc, GLfloat p[3])
{
    for (int i = 0; i < 3; i++)
	sc->sceneblk.camera_target[i] = p[i];
}

void camera_get_target(struct scene_st *sc, GLfloat p[])
{
    for (int i = 0; i < 3; i++)
	p[i] = sc->sceneblk.camera_target[i];
}

void camera_set_up(struct scene_st *sc, GLfloat p[3])
{
    for (int i = 0; i < 3; i++)
	sc->sceneblk.camera_up[i] = p[i];
}

void camera_get_up(struct scene_st *sc, GLfloat p[])
{
    for (int i = 0; i < 3; i++)
	p[i] = sc->sceneblk.camera_up[i];
}

void camera_reset(struct scene_st *sc)
{
    sc->sceneblk.camera_up[0] = 0.0f;
    sc->sceneblk.camera_up[1] = 0.0f;
    sc->sceneblk.camera_up[2] = 1.0f;

    GLfloat front[3];
    GLfloat right[3];
    GLfloat target[3];

    sub_vec3(sc->sceneblk.camera_target, sc->sceneblk.camera_position,
	     target);
    cross_vec3(target, sc->sceneblk.camera_up, right);
    cross_vec3(sc->sceneblk.camera_up, right, front);
    normalize_vec3(front);

    add_vec3(sc->sceneblk.camera_position, front, sc->sceneblk.camera_target);
}

void calculate_proj_mat4(struct scene_st *sc)
{
    pvm_calculate_proj_mat4(sc->camera_fovy, sc->camera_aspect,
			    sc->camera_znear, sc->camera_zfar,
			    sc->sceneblk.projmat);
}

void calculate_view_mat4(struct scene_st *sc)
{
    pvm_calculate_view_mat4(sc->sceneblk.camera_position,
			    sc->sceneblk.camera_target,
			    sc->sceneblk.camera_up, sc->sceneblk.viewmat);
}

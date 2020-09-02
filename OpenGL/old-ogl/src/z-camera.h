#ifndef Z_CAMERA_H_INCLUDED
#define Z_CAMERA_H_INCLUDED

struct scene_st {
    int id;
    char *name;
    struct sceneblk_st {
	GLfloat viewmat[4][4];
	GLfloat projmat[4][4];
	GLfloat camera_position[3];
	GLfloat camera_target[3];
	GLfloat camera_up[3];
    } sceneblk;

    GLfloat camera_fovy;
    GLfloat camera_aspect;
    GLfloat camera_znear;
    GLfloat camera_zfar;

    int sceneblk_offset;
    int sceneblk_size;
};

extern void camera_init(struct scene_st *);

extern struct scene_st *camera_create_scene(void);
extern void camera_destroy_scene(struct scene_st *);

extern GLfloat camera_set_fovy(struct scene_st *, GLfloat);
extern GLfloat camera_get_fovy(struct scene_st *);
extern GLfloat camera_set_aspect(struct scene_st *, GLfloat);
extern GLfloat camera_get_aspect(struct scene_st *);
extern GLfloat camera_set_znear(struct scene_st *, GLfloat);
extern GLfloat camera_get_znear(struct scene_st *);
extern GLfloat camera_set_zfar(struct scene_st *, GLfloat);
extern GLfloat camera_get_zfar(struct scene_st *);
extern void camera_set_position(struct scene_st *, GLfloat[3]);
extern void camera_get_position(struct scene_st *, GLfloat[3]);
extern void camera_set_target(struct scene_st *, GLfloat[3]);
extern void camera_get_target(struct scene_st *, GLfloat[3]);
extern void camera_set_up(struct scene_st *, GLfloat[3]);
extern void camera_get_up(struct scene_st *, GLfloat[3]);
extern void camera_reset(struct scene_st *);

void calculate_proj_mat4(struct scene_st *);
void calculate_view_mat4(struct scene_st *);

#endif

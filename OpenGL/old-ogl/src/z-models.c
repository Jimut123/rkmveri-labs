#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>

#include "z-models.h"
#include "z-mat.h"
#include "debug.h"

// Data for a cube

int cube_vcount = 36;

GLfloat cube_vertices[] = {
    0.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,

    0.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,

    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,

    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,

    0.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,

    0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,

    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,

    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,

    1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,

    0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,

    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,
};

GLfloat cube_normals[] = {
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,

    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,

    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,

    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,

    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,

    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,

    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,

    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,

    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,

    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,

    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,

    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
};

GLfloat cube_tcoords[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,

    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,

    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,

    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,

    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,

    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,

    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
};

GLint square_vcount = 6;

GLfloat square_vertices[] = {
    0.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,

    0.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
};

GLfloat square_normals[] = {
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,

    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
};

GLfloat square_tcoords[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,

    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
};

GLfloat point_vertices[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat point_normals[] = { 0.0f, 0.0f, 1.0f };
GLfloat point_tcoords[] = { 0.0f, 0.0f };

struct model_st *std_model = NULL;

int num_std_models = 0;

static int id = 0;

void mdl_init(void)
{
    num_std_models = 4;

    std_model = mdl_new_model(num_std_models);

    std_model[MODEL_NONE].id = (int)(MODEL_NONE);
    std_model[MODEL_NONE].name = strdup("nil_model");
    std_model[MODEL_NONE].vcount = 0;
    std_model[MODEL_NONE].vertices = NULL;
    std_model[MODEL_NONE].normals = NULL;
    std_model[MODEL_NONE].tcoords = NULL;
    std_model[MODEL_NONE].vbo_offset = 0;
    std_model[MODEL_NONE].draw_mode = GL_POINTS;

    std_model[MODEL_POINT].id = (int)(MODEL_POINT);
    std_model[MODEL_POINT].name = strdup("point_model");
    std_model[MODEL_POINT].vcount = 1;
    std_model[MODEL_POINT].vertices = point_vertices;
    std_model[MODEL_POINT].normals = point_normals;
    std_model[MODEL_POINT].tcoords = point_tcoords;
    std_model[MODEL_POINT].vbo_offset = 0;
    std_model[MODEL_POINT].draw_mode = GL_POINTS;

    std_model[MODEL_CUBE].id = (int)(MODEL_CUBE);
    std_model[MODEL_CUBE].name = strdup("cube_model");
    std_model[MODEL_CUBE].vcount = cube_vcount;
    std_model[MODEL_CUBE].vertices = cube_vertices;
    std_model[MODEL_CUBE].normals = cube_normals;
    std_model[MODEL_CUBE].tcoords = cube_tcoords;
    std_model[MODEL_CUBE].vbo_offset = 0;
    std_model[MODEL_CUBE].draw_mode = GL_TRIANGLES;

    std_model[MODEL_SQUARE].id = (int)(MODEL_SQUARE);
    std_model[MODEL_SQUARE].name = strdup("square_model");
    std_model[MODEL_SQUARE].vcount = square_vcount;
    std_model[MODEL_SQUARE].vertices = square_vertices;
    std_model[MODEL_SQUARE].normals = square_normals;
    std_model[MODEL_SQUARE].tcoords = square_tcoords;
    std_model[MODEL_SQUARE].vbo_offset = 0;
    std_model[MODEL_SQUARE].draw_mode = GL_TRIANGLES;

    id = MODEL_MAX;
}

GLint mdl_get_vcount(struct model_st *model)
{
    return model->vcount;
}

GLfloat *mdl_get_vertices(struct model_st * model)
{
    return model->vertices;
}

GLfloat *mdl_get_normals(struct model_st * model)
{
    return model->normals;
}

GLfloat *mdl_get_tcoords(struct model_st * model)
{
    return model->tcoords;
}

GLint mdl_get_vbo_offset(struct model_st * model)
{
    return model->vbo_offset;
}

void mdl_set_vbo_offset(struct model_st *model, GLint offset)
{
    model->vbo_offset = offset;
}

struct model_st *mdl_get_std_model(int m)
{
    return &(std_model[m]);
}

void subdivide(GLfloat u1[2], GLfloat u2[2], GLfloat u3[2],
	       GLfloat cutoff, int depth,
	       GLfloat(*curv) (GLfloat[2]),
	       void (*surf) (GLfloat[2], GLfloat *, GLfloat *, GLfloat *)
    )
{
    GLfloat v1[3], v2[3], v3[3];
    GLfloat n1[3], n2[3], n3[3];
    GLfloat t1[2], t2[2], t3[2];
    GLfloat u12[2], u23[2], u31[2];
    GLint i;

    if (depth == 0 || ((*curv) (u1) < cutoff &&
		       (*curv) (u2) < cutoff && (*curv) (u3) < cutoff)) {
	(*surf) (u1, v1, n1, t1);
	(*surf) (u2, v2, n2, t2);
	(*surf) (u3, v3, n3, t3);
	return;
    }
    for (i = 0; i < 2; i++) {
	u12[i] = (u1[i] + u2[i]) / 2.0;
	u23[i] = (u2[i] + u3[i]) / 2.0;
	u31[i] = (u3[i] + u1[i]) / 2.0;
    }
    subdivide(u1, u12, u31, cutoff, depth - 1, curv, surf);
    subdivide(u2, u23, u12, cutoff, depth - 1, curv, surf);
    subdivide(u3, u31, u23, cutoff, depth - 1, curv, surf);
    subdivide(u12, u23, u31, cutoff, depth - 1, curv, surf);
}

struct model_st *mdl_new_model(int num)
{
    struct model_st *tmp = (struct model_st *)
	malloc(sizeof(struct model_st) * num);
    if (tmp == NULL) {
	perror("Cannot allocate memory for new_model.");
	exit(EXIT_FAILURE);
    }
    for (int i = 0; i < num; i++) {
	tmp[i].vcount = 0;
	tmp[i].vertices = NULL;
	tmp[i].normals = NULL;
	tmp[i].tcoords = NULL;
	tmp[i].tex = NULL;
	tmp[i].id = id++;
	tmp[i].name = NULL;
	tmp[i].vbo_offset = 0;
	tmp[i].draw_mode = GL_POINTS;
    }
    return tmp;
}

void mdl_delete_model(struct model_st *p)
{
    free(p);
}

struct model_st *mdl_create_square_model(int xnum, int ynum, GLfloat lx,
					 GLfloat by, GLfloat rx, GLfloat ty)
{
    struct model_st *tmp;

    tmp = mdl_new_model(1);

    tmp->name = strdup("checker_model");

    int vcount = 6 * xnum * ynum;

    GLfloat dx = 1.0f / xnum;
    GLfloat dy = 1.0f / ynum;

    GLfloat(*vertices)[4] =
	(GLfloat(*)[4]) malloc(sizeof(GLfloat) * 4 * vcount);
    GLfloat(*tcoords)[2] =
	(GLfloat(*)[2]) malloc(sizeof(GLfloat) * 2 * vcount);
    GLfloat(*normals)[3] =
	(GLfloat(*)[3]) malloc(sizeof(GLfloat) * 3 * vcount);

    int k = 0;
    for (int i = 0; i < xnum; i++) {
	for (int j = 0; j < ynum; j++) {
	    set_vec4(i * dx, j * dy, 0.0, 1.0, vertices[k]);
	    set_vec4((i + 1) * dx, j * dy, 0.0, 1.0, vertices[k + 1]);
	    set_vec4(i * dx, (j + 1) * dy, 0.0, 1.0, vertices[k + 2]);

	    set_vec4(i * dx, (j + 1) * dy, 0.0, 1.0, vertices[k + 3]);
	    set_vec4((i + 1) * dx, j * dy, 0.0, 1.0, vertices[k + 4]);
	    set_vec4((i + 1) * dx, (j + 1) * dy, 0.0, 1.0, vertices[k + 5]);

	    set_vec2(lx, by, tcoords[k]);
	    set_vec2(rx, by, tcoords[k + 1]);
	    set_vec2(lx, ty, tcoords[k + 2]);

	    set_vec2(lx, ty, tcoords[k + 3]);
	    set_vec2(rx, by, tcoords[k + 4]);
	    set_vec2(rx, ty, tcoords[k + 5]);

	    set_vec3(0.0, 0.0, 1.0, normals[k]);
	    set_vec3(0.0, 0.0, 1.0, normals[k + 1]);
	    set_vec3(0.0, 0.0, 1.0, normals[k + 2]);

	    set_vec3(0.0, 0.0, 1.0, normals[k + 3]);
	    set_vec3(0.0, 0.0, 1.0, normals[k + 4]);
	    set_vec3(0.0, 0.0, 1.0, normals[k + 5]);

	    k += 6;
	}
    }

    tmp->vcount = vcount;
    tmp->vertices = (GLfloat *) vertices;
    tmp->tcoords = (GLfloat *) tcoords;
    tmp->normals = (GLfloat *) normals;
    tmp->draw_mode = GL_TRIANGLES;

    for (int i = 0; i < vcount; i++)
	DBG_TRACE(0, "V[%d] = %f %f %f %f\n", i,
		  tmp->vertices[4 * i + 0],
		  tmp->vertices[4 * i + 1],
		  tmp->vertices[4 * i + 2], tmp->vertices[4 * i + 3]);
    return tmp;
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>

#include "z-materials.h"
#include "z-mat.h"

struct material_st *std_material = NULL;
int num_std_materials = 0;

static GLfloat **std_color = NULL;
int num_std_colors = 0;

static int id = 0;

static struct material_st black_mat = {
    MATERIAL_NONE, "nil",
    {
     {0.0f, 0.0f, 0.0f, 0.0f},
     {0.0f, 0.0f, 0.0f, 0.0f},
     {0.0f, 0.0f, 0.0f, 0.0f},
     0.0f,
     0.0f,
     {0.0f, 0.0f},
     {0.0f, 0.0f}
     },
    NULL
};

void copy_material(struct material_st src, struct material_st *dst)
{
    copy_vec4(src.matblk.ambient, dst->matblk.ambient);
    copy_vec4(src.matblk.diffuse, dst->matblk.diffuse);
    copy_vec4(src.matblk.specular, dst->matblk.specular);
    dst->matblk.shininess = src.matblk.shininess;
    dst->tex = src.tex;
}

void mtr_set_matblk_offset(struct material_st *m, int offset)
{
    m->matblk_offset = offset;
}

void mtr_set_matblk_size(struct material_st *m, int sz)
{
    m->matblk_size = sz;
}

void mtr_get_std_color(int color, GLfloat c[])
{
    copy_vec4(std_color[color], c);
}

void color_set(GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat res[])
{
    res[0] = r;
    res[1] = g;
    res[2] = b;
    res[3] = a;
}

void color_init(void)
{
    num_std_colors = COLOR_MAX;

    std_color = (GLfloat **) malloc(sizeof(GLfloat *) * num_std_colors);
    if (std_color == NULL) {
	perror("Cannot allocate memory for std_color");
	exit(EXIT_FAILURE);
    }
    for (int i = 0; i < num_std_colors; i++) {
	std_color[i] = (GLfloat *) malloc(sizeof(GLfloat) * 4);
	if (std_color[i] == NULL) {
	    perror("Cannot allocate memory for std_color[i]");
	    exit(EXIT_FAILURE);
	}
    }

    color_set(0.0, 0.0, 0.0, 0.0, std_color[COLOR_NONE]);
    color_set(1.0, 1.0, 1.0, 1.0, std_color[COLOR_WHITE]);
    color_set(0.0, 0.0, 0.0, 1.0, std_color[COLOR_BLACK]);

    color_set(1.0, 0.0, 0.0, 0.0, std_color[COLOR_1000]);
    color_set(0.0, 1.0, 0.0, 0.0, std_color[COLOR_0100]);
    color_set(0.0, 0.0, 1.0, 0.0, std_color[COLOR_0010]);
    color_set(0.0, 0.0, 0.0, 1.0, std_color[COLOR_0001]);

    color_set(1.0, 0.0, 0.0, 1.0, std_color[COLOR_RED]);
    color_set(0.0, 1.0, 0.0, 1.0, std_color[COLOR_GREEN]);
    color_set(0.0, 0.0, 1.0, 1.0, std_color[COLOR_BLUE]);

    color_set(1.0, 1.0, 0.0, 1.0, std_color[COLOR_YELLOW]);
    color_set(1.0, 0.0, 1.0, 1.0, std_color[COLOR_MAGENTA]);
    color_set(0.0, 1.0, 1.0, 1.0, std_color[COLOR_CYAN]);

    color_set(1.0, 0.5, 0.0, 1.0, std_color[COLOR_ORANGE]);
    color_set(1.0, 0.0, 0.5, 1.0, std_color[COLOR_PINK]);
    color_set(0.5, 1.0, 0.0, 1.0, std_color[COLOR_LEMON_YELLOW]);
    color_set(0.0, 1.0, 0.5, 1.0, std_color[COLOR_LEMON_GREEN]);
    color_set(0.5, 0.0, 1.0, 1.0, std_color[COLOR_PURPLE]);
    color_set(0.0, 0.5, 1.0, 1.0, std_color[COLOR_SEABLUE]);

    color_set(0.5, 0.0, 0.0, 1.0, std_color[COLOR_DARKRED]);
    color_set(0.0, 0.5, 0.0, 1.0, std_color[COLOR_DARKGREEN]);
    color_set(0.0, 0.0, 0.5, 1.0, std_color[COLOR_DARKBLUE]);

    color_set(0.5, 0.5, 0.0, 1.0, std_color[COLOR_DARKYELLOW]);
    color_set(0.5, 0.0, 0.5, 1.0, std_color[COLOR_DARKMAGENTA]);
    color_set(0.0, 0.5, 0.5, 1.0, std_color[COLOR_DARKCYAN]);

    color_set(0.5, 0.5, 0.5, 1.0, std_color[COLOR_GRAY]);

    color_set(1.0, 0.5, 0.5, 1.0, std_color[COLOR_LIGHTRED]);
    color_set(0.5, 1.0, 0.5, 1.0, std_color[COLOR_LIGHTGREEN]);
    color_set(0.5, 0.5, 1.0, 1.0, std_color[COLOR_LIGHTBLUE]);

    color_set(1.0, 1.0, 0.5, 1.0, std_color[COLOR_LIGHTYELLOW]);
    color_set(1.0, 0.5, 1.0, 1.0, std_color[COLOR_LIGHTMAGENTA]);
    color_set(0.5, 1.0, 1.0, 1.0, std_color[COLOR_LIGHTCYAN]);

}

void mtr_init(void)
{
    num_std_materials = MATERIAL_MAX;

    color_init();

    std_material =
	(struct material_st *)malloc(sizeof(struct material_st) *
				     num_std_materials);
    if (std_material == NULL) {
	perror("Cannot allocate memory for std_material.\n");
	exit(EXIT_FAILURE);
    }

    int mat = 0;
    GLfloat color[4];

    mat = MATERIAL_NONE;
    mtr_get_std_color(COLOR_NONE, color);
    copy_material(black_mat, &(std_material[mat]));
    copy_vec4(color, std_material[mat].matblk.ambient);
    copy_vec4(color, std_material[mat].matblk.diffuse);
    std_material[mat].id = mat;
    std_material[mat].name = strdup("none");

    mat = MATERIAL_WHITE;
    mtr_get_std_color(COLOR_WHITE, color);
    copy_material(black_mat, &std_material[mat]);
    copy_vec4(color, std_material[mat].matblk.ambient);
    copy_vec4(color, std_material[mat].matblk.diffuse);
    std_material[mat].id = mat;
    std_material[mat].name = strdup("white");

    mat = MATERIAL_BLACK;
    mtr_get_std_color(COLOR_BLACK, color);
    copy_material(black_mat, &std_material[mat]);
    copy_vec4(color, std_material[mat].matblk.ambient);
    copy_vec4(color, std_material[mat].matblk.diffuse);
    std_material[mat].id = mat;
    std_material[mat].name = strdup("black");

    mat = MATERIAL_RED;
    mtr_get_std_color(COLOR_RED, color);
    copy_material(black_mat, &std_material[mat]);
    copy_vec4(color, std_material[mat].matblk.ambient);
    copy_vec4(color, std_material[mat].matblk.diffuse);
    std_material[mat].id = mat;
    std_material[mat].name = strdup("red");

    mat = MATERIAL_BLUE;
    mtr_get_std_color(COLOR_BLUE, color);
    copy_material(black_mat, &std_material[mat]);
    copy_vec4(color, std_material[mat].matblk.ambient);
    copy_vec4(color, std_material[mat].matblk.diffuse);
    std_material[mat].id = mat;
    std_material[mat].name = strdup("blue");

    mat = MATERIAL_GREEN;
    mtr_get_std_color(COLOR_GREEN, color);
    copy_material(black_mat, &std_material[mat]);
    copy_vec4(color, std_material[mat].matblk.ambient);
    copy_vec4(color, std_material[mat].matblk.diffuse);
    std_material[mat].id = mat;
    std_material[mat].name = strdup("green");

    mat = MATERIAL_YELLOW;
    mtr_get_std_color(COLOR_YELLOW, color);
    copy_material(black_mat, &std_material[mat]);
    copy_vec4(color, std_material[mat].matblk.ambient);
    copy_vec4(color, std_material[mat].matblk.diffuse);
    std_material[mat].id = mat;
    std_material[mat].name = strdup("yellow");

    mat = MATERIAL_MAGENTA;
    mtr_get_std_color(COLOR_MAGENTA, color);
    copy_material(black_mat, &std_material[mat]);
    copy_vec4(color, std_material[mat].matblk.ambient);
    copy_vec4(color, std_material[mat].matblk.diffuse);
    std_material[mat].id = mat;
    std_material[mat].name = strdup("magenta");

    mat = MATERIAL_CYAN;
    mtr_get_std_color(COLOR_CYAN, color);
    copy_material(black_mat, &std_material[mat]);
    copy_vec4(color, std_material[mat].matblk.ambient);
    copy_vec4(color, std_material[mat].matblk.diffuse);
    std_material[mat].id = mat;
    std_material[mat].name = strdup("cyan");

    mat = MATERIAL_1000;
    mtr_get_std_color(COLOR_1000, color);
    copy_material(black_mat, &std_material[mat]);
    copy_vec4(color, std_material[mat].matblk.ambient);
    copy_vec4(color, std_material[mat].matblk.diffuse);
    std_material[mat].id = mat;
    std_material[mat].name = strdup("mat1000");

    mat = MATERIAL_0100;
    mtr_get_std_color(COLOR_0100, color);
    copy_material(black_mat, &std_material[mat]);
    copy_vec4(color, std_material[mat].matblk.ambient);
    copy_vec4(color, std_material[mat].matblk.diffuse);
    std_material[mat].id = mat;
    std_material[mat].name = strdup("mat0100");

    mat = MATERIAL_0010;
    mtr_get_std_color(COLOR_0010, color);
    copy_material(black_mat, &std_material[mat]);
    copy_vec4(color, std_material[mat].matblk.ambient);
    copy_vec4(color, std_material[mat].matblk.diffuse);
    std_material[mat].id = mat;
    std_material[mat].name = strdup("mat0010");

    mat = MATERIAL_0001;
    mtr_get_std_color(COLOR_0001, color);
    copy_material(black_mat, &std_material[mat]);
    copy_vec4(color, std_material[mat].matblk.ambient);
    copy_vec4(color, std_material[mat].matblk.diffuse);
    std_material[mat].id = mat;
    std_material[mat].name = strdup("mat0001");

    id = MATERIAL_MAX;

}

struct material_st *mtr_get_std_material(int material)
{
    return &(std_material[material]);
};

struct material_st *mtr_new_material(int num)
{
    struct material_st *tmp;

    tmp = (struct material_st *)malloc(sizeof(struct material_st) * num);
    if (tmp == NULL) {
	perror("Cannot allocate memory for std_material.\n");
	exit(EXIT_FAILURE);
    }

    copy_material(black_mat, tmp);
    tmp->id = id++;
    tmp->name = NULL;
    return tmp;
}

void mtr_delete_material(struct material_st *m)
{
    free(m);
}

void mtr_set_texcoords(struct material_st *m, GLfloat ox, GLfloat oy,
		       GLfloat sx, GLfloat sy)
{

    //m->matblk.dummy_1[0] = 1.0;
    //m->matblk.dummy_1[1] = 0.0;
    m->matblk.texorigin[0] = ox;
    m->matblk.texorigin[1] = oy;
    //m->matblk.texorigin[0] = 0.0;
    //m->matblk.texorigin[1] = 0.0;
    m->matblk.texsize[0] = sx;
    m->matblk.texsize[1] = sy;
    //m->matblk.texsize[0] = 1.0;
    //m->matblk.texsize[1] = 0.0;
}

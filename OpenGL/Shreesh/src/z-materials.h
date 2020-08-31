#ifndef Z_MATERIALS_H_INCLUDED
#define Z_MATERIALS_H_INCLUDED

enum material_enum {
    MATERIAL_NONE, MATERIAL_WHITE, MATERIAL_BLACK,
    MATERIAL_RED, MATERIAL_GREEN, MATERIAL_BLUE,
    MATERIAL_YELLOW, MATERIAL_MAGENTA, MATERIAL_CYAN,
    MATERIAL_1000, MATERIAL_0100, MATERIAL_0010, MATERIAL_0001,
    MATERIAL_MAX
};

enum color_en {
    COLOR_NONE,
    COLOR_WHITE, COLOR_BLACK,
    COLOR_RED, COLOR_GREEN, COLOR_BLUE,
    COLOR_1000, COLOR_0100, COLOR_0010, COLOR_0001,
    COLOR_YELLOW, COLOR_MAGENTA, COLOR_CYAN,
    COLOR_ORANGE, COLOR_PINK, COLOR_LEMON_YELLOW,
    COLOR_LEMON_GREEN, COLOR_PURPLE, COLOR_SEABLUE,

    COLOR_DARKRED, COLOR_DARKGREEN, COLOR_DARKBLUE,
    COLOR_DARKYELLOW, COLOR_DARKMAGENTA, COLOR_DARKCYAN,

    COLOR_GRAY,

    COLOR_LIGHTRED, COLOR_LIGHTGREEN, COLOR_LIGHTBLUE,
    COLOR_LIGHTYELLOW, COLOR_LIGHTMAGENTA, COLOR_LIGHTCYAN,

    COLOR_MAX
};

enum color_type_en {
    COLOR_TYPE_NONE,
    COLOR_TYPE_SIMPLE,
    COLOR_TYPE_TEXTURE,
    COLOR_TYPE_TEXTURE_COMPLEX,
    COLOR_TYPE_TEXTURE_TEXTURE,
    COLOR_TYPE_TEXTURE_TEXTURE_COMPLEX,
    COLOR_TYPE_MAX
};

struct material_st {
    int id;
    char *name;
    struct matblk_st {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess;
	GLfloat _pad1;
	GLfloat texorigin[2];
	GLfloat texsize[2];
    } matblk;

    struct texture_st *tex;

    int matblk_offset;
    int matblk_size;
};

extern struct material_st *mtr_get_std_material(int);
extern void mtr_set_matblk_offset(struct material_st *, int);
extern void mtr_set_matblk_size(struct material_st *, int);
extern void mtr_get_std_color(int, GLfloat[]);

extern struct material_st *mtr_new_material(int);
extern void mtr_delete_material(struct material_st *);
extern void mtr_set_texcoords(struct material_st *, GLfloat, GLfloat, GLfloat,
			      GLfloat);

void mtr_init(void);

#endif

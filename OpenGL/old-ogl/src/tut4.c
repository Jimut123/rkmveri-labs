#include <stdio.h>
#include <GL/glew.h>
#include <math.h>

#include "z-main.h"
#include "z-shader.h"
#include "z-pvm.h"
#include "z-png.h"
#include "z-models.h"
#include "z-materials.h"
#include "z-camera.h"
#include "z-world.h"
#include "z-mat.h"
#include "z-light.h"

#include "debug.h"

#define MAXLIGHTS 4

static GLuint plain_progid = 0;
static GLuint texture_progid = 0;

static GLuint position_loc = -1;
static GLuint normal_loc = -1;
static GLuint tc_loc = -1;

static GLuint vao[2] = { 0, 0 };

static struct dlist_hdr *list_objects = NULL;
static struct dlist_hdr *list_models = NULL;
static struct dlist_hdr *list_materials = NULL;

static struct object_st *cube1 = NULL;
static struct object_st *cube2 = NULL;
static struct object_st *cube3 = NULL;
static struct object_st *cube4 = NULL;
static struct object_st *checker = NULL;
static struct object_st *light_obj[MAXLIGHTS];

static struct scene_st *sc = NULL;
static struct light_st *lights = NULL;

GLuint ubo_model = 0;
GLuint ubo_scene = 0;
GLuint ubo_material = 0;
GLuint ubo_light = 0;

GLint modelblk_sz = 0;
GLint sceneblk_sz = 0;
GLint materialblk_sz = 0;
GLint lightblk_sz = 0;

GLint modelblk_bpoint = 0;
GLint sceneblk_bpoint = 0;
GLint matblk_bpoint = 0;
GLint lightblk_bpoint = 0;

GLint UniformBufferOffset = 0;

void setshaders(void)
{
    GLuint shader[3];

    shader[0] =
	opengl_createshader(GL_VERTEX_SHADER, "shaders/tut4-plain.vert");
    shader[1] =
	opengl_createshader(GL_FRAGMENT_SHADER, "shaders/tut4-plain.frag");
    shader[2] =
	opengl_createshader(GL_FRAGMENT_SHADER, "shaders/tut4-texture.frag");
    shader[3] = 0;

    GLuint plain_shlist[] = { 0, 1, -1 };

    plain_progid = opengl_createprogram(shader, plain_shlist);

    GLuint texture_shlist[] = { 0, 2, -1 };

    texture_progid = opengl_createprogram(shader, texture_shlist);
}

#define BUFFER_OFFSET(off) ((void *)(NULL+off))

int checkattrlocs(int progid, int *loc, char **name)
{
    int okay = 1;
    int i = 0;
    while (loc[i] >= 0) {
	int lc = glGetAttribLocation(progid, name[i]);

	DBG_TRACE(0, "Attribute Loc: %d %s expect(%d)", lc, name[i], loc[i]);

	if ((lc != -1) && (lc != loc[i])) {
	    okay = 0;
	    break;
	}
	i++;
    };

    if (!okay) {
	perror
	    ("Attribute locations do not match in shaders and application.");
    }
    return okay;
}

void setvaos(void)
{
    GLuint vbo = 0;

    GLint MaxVertexAttribs = 0;

    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &MaxVertexAttribs);

    DBG_TRACE(0, "Max vertex attribs: %d", MaxVertexAttribs);

    int locs[] = { 0, 1, 2, -1 };
    char *attrs[] = { "vposition", "vtcoord", "vnormal", NULL };

    checkattrlocs(plain_progid, locs, attrs);
    checkattrlocs(texture_progid, locs, attrs);

    position_loc = 0;
    tc_loc = 1;
    normal_loc = 2;

    glGenVertexArrays(1, vao);

    glBindVertexArray(vao[0]);

    // Generate 1 buffer, put the resulting identifier in vbid
    glGenBuffers(1, &vbo);
    // The following commands will talk about our 'vbid' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    struct dlist_st *mdl = NULL;
    GLint vcount = 0;

    for (mdl = list_models->first; mdl != NULL; mdl = mdl->next) {
	vcount += mdl_get_vcount(mdl->data);

    }

    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER,
		 sizeof(GLfloat) * (4 + 2 + 3) * vcount, NULL,
		 GL_STATIC_DRAW);

    GLint offset = 0;
    GLint cnt = 0;
    GLfloat *data = NULL;

    if (position_loc >= 0)
	glVertexAttribPointer(position_loc, 4, GL_FLOAT, GL_FALSE, 0,
			      BUFFER_OFFSET(offset));

    GLint num = 0;
    for (mdl = list_models->first; mdl != NULL; mdl = mdl->next) {
	cnt = mdl_get_vcount(mdl->data);
	data = mdl_get_vertices(mdl->data);

	mdl_set_vbo_offset(mdl->data, num);
	DBG_TRACE(0, "Vcount: %d", mdl_get_vcount(mdl->data));
	DBG_TRACE(0, "Voffset: %d", offset);

	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(GLfloat) * 4 * cnt,
			data);

	offset += sizeof(GLfloat) * 4 * cnt;
	num += cnt;
    }

    if (tc_loc >= 0)
	glVertexAttribPointer(tc_loc, 2, GL_FLOAT, GL_FALSE, 0,
			      BUFFER_OFFSET(offset));

    for (mdl = list_models->first; mdl != NULL; mdl = mdl->next) {
	cnt = mdl_get_vcount(mdl->data);
	data = mdl_get_tcoords(mdl->data);

	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(GLfloat) * 2 * cnt,
			data);

	offset += sizeof(GLfloat) * 2 * cnt;
    }

    if (normal_loc >= 0)
	glVertexAttribPointer(normal_loc, 3, GL_FLOAT, GL_FALSE, 0,
			      BUFFER_OFFSET(offset));

    for (mdl = list_models->first; mdl != NULL; mdl = mdl->next) {
	cnt = mdl_get_vcount(mdl->data);
	data = mdl_get_normals(mdl->data);

	glBufferSubData(GL_ARRAY_BUFFER, offset,
			sizeof(GLfloat) * 3 * cnt, data);

	offset += sizeof(GLfloat) * 3 * cnt;
    }

    if (position_loc >= 0)
	glEnableVertexAttribArray(position_loc);
    if (tc_loc >= 0)
	glEnableVertexAttribArray(tc_loc);
    if (normal_loc >= 0)
	glEnableVertexAttribArray(normal_loc);

    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindVertexArray(0);
}

void setuniforms_modelblk(void)
{
    // Models specific
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_model);

    modelblk_sz = sizeof(struct modelblk_st);

    GLint realblk_sz = modelblk_sz;

    if (modelblk_sz % UniformBufferOffset != 0) {
	realblk_sz =
	    modelblk_sz + UniformBufferOffset -
	    modelblk_sz % UniformBufferOffset;
    }

    int count = list_objects->size;
    glBufferData(GL_UNIFORM_BUFFER, realblk_sz * count, NULL,
		 GL_DYNAMIC_DRAW);

    int modelblk_offset = 0;
    struct dlist_st *ol = NULL;
    for (ol = list_objects->first; ol != NULL; ol = ol->next) {
	struct object_st *obj = ol->data;

	calculate_model_mat4(obj);
	calculate_normal_mat4(obj);

	if (modelblk_offset % UniformBufferOffset != 0) {
	    modelblk_offset +=
		UniformBufferOffset - modelblk_offset % UniformBufferOffset;
	}
	obj_set_modelblk_offset(obj, modelblk_offset);
	obj_set_modelblk_size(obj, modelblk_sz);

	DBG_TRACE(0, "modelblk_offset: %d %d %d", modelblk_offset,
		  modelblk_sz, sizeof(obj->modelblk));

	glBufferSubData(GL_UNIFORM_BUFFER, modelblk_offset, modelblk_sz,
			&(obj->modelblk));
	modelblk_offset += realblk_sz;

    }

    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    GLuint bindex = 0;
    GLuint bpoint = 0;

    bpoint = modelblk_bpoint = 0;

    bindex = glGetUniformBlockIndex(plain_progid, "ModelBlock");
    glUniformBlockBinding(plain_progid, bindex, bpoint);

    bindex = glGetUniformBlockIndex(texture_progid, "ModelBlock");
    glUniformBlockBinding(texture_progid, bindex, bpoint);

}

void setuniforms_sceneblk(void)
{
    // Camera specific
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_scene);

    calculate_view_mat4(sc);
    calculate_proj_mat4(sc);

    sceneblk_sz = sizeof(sc->sceneblk);
    GLint realblk_sz = sceneblk_sz;
    if (sceneblk_sz % UniformBufferOffset != 0) {
	realblk_sz =
	    sceneblk_sz + UniformBufferOffset -
	    sceneblk_sz % UniformBufferOffset;
    }
    GLint sz = realblk_sz;

    glBufferData(GL_UNIFORM_BUFFER, sz, NULL, GL_DYNAMIC_DRAW);

    GLint sceneblk_offset = 0;

    sc->sceneblk_size = sceneblk_sz;
    sc->sceneblk_offset = sceneblk_offset;

    print_mat4("View Mat4", sc->sceneblk.viewmat);
    print_mat4("Projection Mat4", sc->sceneblk.projmat);

    glBufferSubData(GL_UNIFORM_BUFFER, sceneblk_offset, sceneblk_sz,
		    &(sc->sceneblk));

    sceneblk_offset += realblk_sz;

    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    GLuint bindex = 0;
    GLuint bpoint = 0;

    bpoint = sceneblk_bpoint = 1;

    bindex = glGetUniformBlockIndex(plain_progid, "SceneBlock");
    glUniformBlockBinding(plain_progid, bindex, bpoint);

    bindex = glGetUniformBlockIndex(texture_progid, "SceneBlock");
    glUniformBlockBinding(texture_progid, bindex, bpoint);

}

void setuniforms_materialsblk(void)
{
    // Materials specific
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_material);

    struct dlist_st *ml = NULL;

    materialblk_sz = sizeof(struct matblk_st);
    GLint realblk_sz = materialblk_sz;
    if (materialblk_sz % UniformBufferOffset != 0) {
	realblk_sz =
	    materialblk_sz + UniformBufferOffset -
	    materialblk_sz % UniformBufferOffset;
    }

    GLint sz = 0;

    for (ml = list_materials->first; ml != NULL; ml = ml->next) {
	sz += realblk_sz;
    }
    glBufferData(GL_UNIFORM_BUFFER, sz, NULL, GL_DYNAMIC_DRAW);

    int matblk_offset = 0;

    for (ml = list_materials->first; ml != NULL; ml = ml->next) {
	struct material_st *mat;

	mat = (struct material_st *)ml->data;

	if (matblk_offset % UniformBufferOffset != 0) {
	    matblk_offset +=
		UniformBufferOffset - matblk_offset % UniformBufferOffset;
	}
	mtr_set_matblk_offset(mat, matblk_offset);
	mtr_set_matblk_size(mat, materialblk_sz);

	glBufferSubData(GL_UNIFORM_BUFFER, matblk_offset, materialblk_sz,
			&(mat->matblk));
	matblk_offset += realblk_sz;
    }

    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    GLuint bindex = 0;
    GLuint bpoint = 0;

    bpoint = matblk_bpoint = 2;
    bindex = glGetUniformBlockIndex(plain_progid, "MaterialBlock");
    glUniformBlockBinding(plain_progid, bindex, bpoint);

    bindex = glGetUniformBlockIndex(texture_progid, "MaterialBlock");
    glUniformBlockBinding(texture_progid, bindex, bpoint);

}

void setuniforms_lightblk(void)
{
    // Lighting specific
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_light);

    lightblk_sz = sizeof(struct lightblk_st);
    GLint realblk_sz = lightblk_sz;
    if (lightblk_sz % UniformBufferOffset != 0) {
	realblk_sz =
	    lightblk_sz + UniformBufferOffset -
	    lightblk_sz % UniformBufferOffset;
    }
    GLint sz = realblk_sz;
    glBufferData(GL_UNIFORM_BUFFER, sz, NULL, GL_DYNAMIC_DRAW);

    int lightblk_offset = 0;

    struct lightblk_st *lblk = &(lights->lightblk);
    print_vec3("Amb", lblk->ambience);
    for (int i = 0; i < MAXLIGHTS; i++) {
	print_vec3("Lt_pos", lblk->pos[i]);
    }
    for (int i = 0; i < MAXLIGHTS; i++) {
	print_vec3("Lt_em", lblk->emission[i]);
    }
    printf("N:%d\n", lblk->num);

    DBG_TRACE(0, "Lightblk_st: %d,%d", lightblk_offset, lightblk_sz);

    light_set_lightblk_offset(lights, lightblk_offset);
    light_set_lightblk_size(lights, lightblk_sz);

    glBufferSubData(GL_UNIFORM_BUFFER, lightblk_offset, lightblk_sz,
		    &(lights->lightblk));
    lightblk_offset += realblk_sz;

    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    GLuint bindex = 0;
    GLuint bpoint = 0;

    bpoint = lightblk_bpoint = 3;
    bindex = glGetUniformBlockIndex(plain_progid, "LightBlock");
    glUniformBlockBinding(plain_progid, bindex, bpoint);

    bindex = glGetUniformBlockIndex(texture_progid, "LightBlock");
    glUniformBlockBinding(texture_progid, bindex, bpoint);

}

void setuniforms(void)
{
    GLuint ubo[4];

    glGenBuffers(4, ubo);

    ubo_model = ubo[0];
    ubo_scene = ubo[1];
    ubo_material = ubo[2];
    ubo_light = ubo[3];

    glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &UniformBufferOffset);

    DBG_TRACE(0, "Align: %d", UniformBufferOffset);

    // Models specific
    setuniforms_modelblk();

    // Camera specific
    setuniforms_sceneblk();

    // Materials specific
    setuniforms_materialsblk();

    // Lighting specific
    setuniforms_lightblk();
}

void settextures(void)
{
    GLuint tid[2];

    glGenTextures(2, tid);

    GLuint tid_base = tid[0];
    GLuint tid_text = tid[1];

    struct image_st image_txt;
    struct image_st image_grass;
    int width = 0;
    int height = 0;
    int num_mipmaps = 8;
    void *gpixels, *tpixels;

    png_read_file("textures/grass2.png", &image_grass);
    png_read_file("textures/abcd1234.png", &image_txt);

    width = image_grass.width;
    height = image_grass.height;
    gpixels = image_grass.pixels;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tid_base);

    glTexStorage2D(GL_TEXTURE_2D, num_mipmaps, GL_RGBA8, width, height);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_BGRA,
		    GL_UNSIGNED_BYTE, gpixels);
    glGenerateMipmap(GL_TEXTURE_2D);	//Generate num_mipmaps number of mipmaps here.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		    GL_LINEAR_MIPMAP_LINEAR);

    width = image_txt.width;
    height = image_txt.height;
    tpixels = image_txt.pixels;

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tid_text);

    glTexStorage2D(GL_TEXTURE_2D, num_mipmaps, GL_RGBA8, width, height);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_BGRA,
		    GL_UNSIGNED_BYTE, tpixels);
    glGenerateMipmap(GL_TEXTURE_2D);	//Generate num_mipmaps number of mipmaps here.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		    GL_LINEAR_MIPMAP_LINEAR);

    glActiveTexture(GL_TEXTURE0);

    DBG_TRACE(0, "Setting Textures");
    glUseProgram(texture_progid);

    GLuint baseloc = glGetUniformLocation(texture_progid, "basetex");
    GLuint textloc = glGetUniformLocation(texture_progid, "texttex");

    DBG_TRACE(0, "Texlocs %d %d\n", baseloc, textloc);

    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, tid_base);

    //glActiveTexture(GL_TEXTURE1);
    //glBindTexture(GL_TEXTURE_2D, tid_text);

    glUniform1i(baseloc, 0);
    glUniform1i(textloc, 1);

    png_free_image(&image_grass);
    png_free_image(&image_txt);
}

void objects_init(void)
{
    dl_search_and_insert(list_models, mdl_get_std_model(MODEL_CUBE));

    dl_search_and_insert(list_materials, mtr_get_std_material(MATERIAL_RED));
    dl_search_and_insert(list_materials,
			 mtr_get_std_material(MATERIAL_YELLOW));
    dl_search_and_insert(list_materials,
			 mtr_get_std_material(MATERIAL_WHITE));
    dl_search_and_insert(list_materials, mtr_get_std_material(MATERIAL_CYAN));
    dl_search_and_insert(list_materials, mtr_get_std_material(MATERIAL_NONE));

    cube1 = obj_create_object("red cube", mdl_get_std_model(MODEL_CUBE),
			      mtr_get_std_material(MATERIAL_RED)
	);

    dl_search_and_insert(list_objects, cube1);

    cube2 = obj_create_object("yellow cube", mdl_get_std_model(MODEL_CUBE),
			      mtr_get_std_material(MATERIAL_YELLOW)
	);
    dl_search_and_insert(list_objects, cube2);

    cube3 = obj_create_object("white cube", mdl_get_std_model(MODEL_CUBE),
			      mtr_get_std_material(MATERIAL_WHITE)
	);
    dl_search_and_insert(list_objects, cube3);

    struct material_st *bgrass = mtr_new_material(1);
    mtr_set_texcoords(bgrass, 0.5, 0.0, 0.5, 1.0);

    dl_search_and_insert(list_materials, bgrass);

    cube4 = obj_create_object("texture cube", mdl_get_std_model(MODEL_CUBE),
			      bgrass);
    dl_search_and_insert(list_objects, cube4);

    obj_abs_translate(cube1, 0.0f, 0.0f, 0.0f);
    obj_abs_scale(cube1, 0.5f, 0.5f, 0.5f);
    obj_abs_rotate(cube1, 1.0f, 1.0f, 1.0f, degtorad(0.0f));

    obj_abs_translate(cube2, -1.0f, 0.0f, 0.0f);
    obj_abs_scale(cube2, 0.5f, 0.5f, 0.5f);
    obj_abs_rotate(cube2, 1.0f, 1.0f, 1.0f, degtorad(0.0f));

    obj_abs_translate(cube3, 0.0f, -1.0f, 0.0f);
    obj_abs_scale(cube3, 0.5f, 0.5f, 0.5f);
    obj_abs_rotate(cube3, 1.0f, 1.0f, 1.0f, degtorad(0.0f));

    obj_abs_translate(cube4, -1.0f, -1.0f, 0.0f);
    obj_abs_scale(cube4, 0.5f, 0.5f, 0.5f);
    obj_abs_rotate(cube4, 1.0f, 1.0f, 1.0f, degtorad(0.0f));

    struct material_st *ggrass = mtr_new_material(1);
    mtr_set_texcoords(ggrass, 0.0, 0.0, 0.5, 1.0);

    checker = obj_create_object("checker",
				mdl_create_square_model(16, 16, 0.0, 0.0, 4.0,
							4.0), ggrass);

    dl_search_and_insert(list_models, checker->model);
    dl_search_and_insert(list_materials, ggrass);
    dl_search_and_insert(list_objects, checker);

    DBG_TRACE(0, "Texture coords: %f %f %f %f",
	      bgrass->matblk.texorigin[0],
	      bgrass->matblk.texorigin[1],
	      bgrass->matblk.texsize[0], bgrass->matblk.texsize[1]);

    obj_abs_translate(checker, -32.0f, -32.0f, 0.0f);
    obj_abs_scale(checker, 64.0f, 64.0f, 64.0f);
    obj_abs_rotate(checker, 1.0f, 1.0f, 1.0f, degtorad(0.0f));

    DBG_TRACE(0, "VCount: %d", checker->model->vcount);
    for (int i = 0; i < checker->model->vcount; i++)
	DBG_TRACE(0, "V[%d] = %f %f %f %f\n", i,
		  checker->model->vertices[4 * i + 0],
		  checker->model->vertices[4 * i + 1],
		  checker->model->vertices[4 * i + 2],
		  checker->model->vertices[4 * i + 3]);

    dl_search_and_insert(list_models, mdl_get_std_model(MODEL_POINT));
    for (int i = 0; i < lights->lightblk.num; i++) {
	light_obj[i] = obj_create_object("light obj",
					 mdl_get_std_model(MODEL_POINT),
					 mtr_get_std_material
					 (MATERIAL_WHITE));
	dl_search_and_insert(list_objects, light_obj[i]);

	obj_abs_translate(light_obj[i],
			  lights->lightblk.pos[i][0],
			  lights->lightblk.pos[i][1],
			  lights->lightblk.pos[i][2] - 0.01);
	obj_abs_scale(light_obj[i], 1.0, 1.0, 1.0);
	obj_abs_rotate(light_obj[i], 1.0f, 1.0f, 1.0f, degtorad(0.0f));
    }

}

void main_init(void)
{

    list_objects = dl_create();
    list_models = dl_create();
    list_materials = dl_create();

    world_init(1024.0f, 1024.0f, 1024.0f);
    mdl_init();
    mtr_init();

    sc = camera_create_scene();
    camera_init(sc);

    lights = light_create_light();
    light_init(lights);
    objects_init();

    setshaders();
    setvaos();
    setuniforms();
    settextures();

    glBindBufferRange(GL_UNIFORM_BUFFER, sceneblk_bpoint, ubo_scene, 0,
		      sceneblk_sz);
    glBindBufferRange(GL_UNIFORM_BUFFER, lightblk_bpoint, ubo_light, 0,
		      lightblk_sz);

    DBG_TRACE(0, "Model %d %d", checker->model->vbo_offset,
	      checker->model->vcount);
    DBG_TRACE(0, "Model %d %d", light_obj[0]->model->vbo_offset,
	      light_obj[0]->model->vcount);
}

void main_draw(void)
{

    // Draw the triangle 1 !
    glBindVertexArray(vao[0]);

    //glDrawArrays(GL_TRIANGLES, 0, 6);
    //glDrawArrays(GL_TRIANGLES, 6, 6);
    //glDrawArrays(GL_TRIANGLES, 12, 6);
    //glDrawArrays(GL_TRIANGLES, 18, 6);
    //glDrawArrays(GL_TRIANGLES, 24, 6);
    //glDrawArrays(GL_TRIANGLES, 30, 6);

    /*
       struct dlist_st *ol = NULL;
       for (ol = get_object_list(); ol != NULL; ol = ol->next) {
       s_truct object_st * obj = ol->data;
       glBindBufferRange(GL_UNIFORM_BUFFER, 0, ubo_model,obj->modelblk_offset,modelblk_sz);
       glDrawArrays(GL_TRIANGLES, obj->offset, 36);
       }
     */
    struct object_st *obj = NULL;
    struct model_st *model = NULL;
    struct material_st *material = NULL;

    glUseProgram(plain_progid);

    obj = cube1;
    model = obj->model;
    glBindBufferRange(GL_UNIFORM_BUFFER, modelblk_bpoint, ubo_model,
		      obj->modelblk_offset, modelblk_sz);
    material = obj->material;
    glBindBufferRange(GL_UNIFORM_BUFFER, matblk_bpoint, ubo_material,
		      material->matblk_offset, materialblk_sz);
    glDrawArrays(model->draw_mode, model->vbo_offset, model->vcount);

    for (int i = 0; i < lights->lightblk.num; i++) {
	obj = light_obj[i];
	model = obj->model;
	material = obj->material;
	glBindBufferRange(GL_UNIFORM_BUFFER, modelblk_bpoint, ubo_model,
			  obj->modelblk_offset, modelblk_sz);
	glBindBufferRange(GL_UNIFORM_BUFFER, matblk_bpoint, ubo_material,
			  material->matblk_offset, materialblk_sz);
	glDrawArrays(model->draw_mode, model->vbo_offset, model->vcount);
    }

    obj = cube2;
    model = obj->model;
    glBindBufferRange(GL_UNIFORM_BUFFER, modelblk_bpoint, ubo_model,
		      obj->modelblk_offset, modelblk_sz);
    material = obj->material;
    glBindBufferRange(GL_UNIFORM_BUFFER, matblk_bpoint, ubo_material,
		      material->matblk_offset, materialblk_sz);
    glDrawArrays(model->draw_mode, model->vbo_offset, model->vcount);

    obj = cube3;
    model = obj->model;
    glBindBufferRange(GL_UNIFORM_BUFFER, modelblk_bpoint, ubo_model,
		      obj->modelblk_offset, modelblk_sz);
    material = obj->material;
    glBindBufferRange(GL_UNIFORM_BUFFER, matblk_bpoint, ubo_material,
		      material->matblk_offset, materialblk_sz);
    glDrawArrays(model->draw_mode, model->vbo_offset, model->vcount);

    glUseProgram(texture_progid);

    obj = cube4;
    model = obj->model;
    glBindBufferRange(GL_UNIFORM_BUFFER, modelblk_bpoint, ubo_model,
		      obj->modelblk_offset, modelblk_sz);
    material = obj->material;
    glBindBufferRange(GL_UNIFORM_BUFFER, matblk_bpoint, ubo_material,
		      material->matblk_offset, materialblk_sz);
    glDrawArrays(model->draw_mode, model->vbo_offset, model->vcount);

    obj = checker;
    model = obj->model;
    glBindBufferRange(GL_UNIFORM_BUFFER, modelblk_bpoint, ubo_model,
		      obj->modelblk_offset, modelblk_sz);
    material = obj->material;
    glBindBufferRange(GL_UNIFORM_BUFFER, matblk_bpoint, ubo_material,
		      material->matblk_offset, materialblk_sz);
    glDrawArrays(model->draw_mode, model->vbo_offset, model->vcount);

    glBindVertexArray(0);
}

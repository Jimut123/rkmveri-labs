#include <stdio.h>
#include <GL/glew.h>
#include <math.h>

#include "z-main.h"
#include "z-shader.h"
#include "z-mat.h"
#include "z-pvm.h"
#include "z-png.h"

#include "debug.h"

static GLuint progid = 0;
static GLuint position_loc = -1;
static GLuint normal_loc = -1;
static GLuint texcoord_loc = -1;
static GLuint vao[2] = { 0, 0 };

// Data for a cube

int verticeCount = 36;

GLfloat vertices[] = {
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

    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,

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

GLfloat normals[] = {
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

GLfloat texcoords[] = {
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

void setshaders(void)
{
    GLuint shader[3];

    shader[0] = opengl_createshader(GL_VERTEX_SHADER, "shaders/tut3.vert");
    shader[1] = opengl_createshader(GL_FRAGMENT_SHADER, "shaders/tut3.frag");
    shader[2] = 0;

    GLuint shlist[] = { 0, 1, -1 };

    progid = opengl_createprogram(shader, shlist);
}

void setvaos(void)
{
    GLuint vbo = 0;

    //vposition_loc = 0;
    position_loc = glGetAttribLocation(progid, "position");
    texcoord_loc = glGetAttribLocation(progid, "texcoord");
    normal_loc = glGetAttribLocation(progid, "normal");

    DBG_TRACE(0, "Locs: %d %d %d", position_loc, texcoord_loc, normal_loc);

    glGenVertexArrays(1, vao);

    glBindVertexArray(vao[0]);

    // Generate 1 buffer, put the resulting identifier in vbid
    glGenBuffers(1, &vbo);
    // The following commands will talk about our 'vbid' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER,
		 sizeof(vertices) + sizeof(normals) + sizeof(texcoords),
		 NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBufferSubData(GL_ARRAY_BUFFER,
		    sizeof(vertices), sizeof(texcoords), texcoords);
    glBufferSubData(GL_ARRAY_BUFFER,
		    sizeof(vertices) + sizeof(texcoords), sizeof(normals),
		    normals);

    glVertexAttribPointer(position_loc, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glVertexAttribPointer(texcoord_loc, 2, GL_FLOAT, GL_FALSE, 0,
			  (void *)(sizeof(vertices)));
    glVertexAttribPointer(normal_loc, 3, GL_FLOAT, GL_FALSE, 0,
			  (void *)(sizeof(vertices) + sizeof(texcoords)));

    if (position_loc >= 0)
	glEnableVertexAttribArray(position_loc);
    if (texcoord_loc >= 0)
	glEnableVertexAttribArray(texcoord_loc);
    if (normal_loc >= 0)
	glEnableVertexAttribArray(normal_loc);

    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindVertexArray(0);
}

GLfloat model_mat4[4][4];
GLfloat view_mat4[4][4];
GLfloat proj_mat4[4][4];

GLfloat color_vec[4];
GLfloat ambient_vec[4];
GLfloat diffuse_vec[4];
GLfloat specular_vec[4];
GLfloat shininess_float = 0.0f;

GLfloat light_color_vec[4] = { 1.0f, 1.0f, 1.0f };
GLfloat light_pos_vec[4] = { 0.0f, 2.0f, 0.0f };

GLuint ubo_model = 0;
GLuint ubo_scene = 0;
GLuint ubo_material = 0;
GLuint ubo_light = 0;

void setuniforms(void)
{
    GLuint ubo[4];

    glGenBuffers(4, ubo);

    ubo_model = ubo[0];
    ubo_scene = ubo[1];
    ubo_material = ubo[2];
    ubo_light = ubo[3];

    glBindBuffer(GL_UNIFORM_BUFFER, ubo_model);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(model_mat4), NULL,
		 GL_DYNAMIC_DRAW);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(model_mat4), model_mat4);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBuffer(GL_UNIFORM_BUFFER, ubo_scene);
    glBufferData(GL_UNIFORM_BUFFER,
		 sizeof(view_mat4) + sizeof(proj_mat4), NULL,
		 GL_DYNAMIC_DRAW);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(view_mat4), view_mat4);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(view_mat4),
		    sizeof(proj_mat4), proj_mat4);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBuffer(GL_UNIFORM_BUFFER, ubo_material);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(color_vec) + sizeof(ambient_vec)
		 + sizeof(diffuse_vec) + sizeof(specular_vec) +
		 sizeof(shininess_float), NULL, GL_DYNAMIC_DRAW);

    int off = 0;
    glBufferSubData(GL_UNIFORM_BUFFER, off, sizeof(color_vec), color_vec);
    off += sizeof(color_vec);
    glBufferSubData(GL_UNIFORM_BUFFER, off, sizeof(ambient_vec), ambient_vec);
    off += sizeof(ambient_vec);
    glBufferSubData(GL_UNIFORM_BUFFER, off, sizeof(diffuse_vec), diffuse_vec);
    off += sizeof(diffuse_vec);
    glBufferSubData(GL_UNIFORM_BUFFER, off, sizeof(specular_vec),
		    specular_vec);
    off += sizeof(specular_vec);
    glBufferSubData(GL_UNIFORM_BUFFER, off, sizeof(shininess_float),
		    &shininess_float);
    off += sizeof(shininess_float);

    glBindBuffer(GL_UNIFORM_BUFFER, ubo_light);
    glBufferData(GL_UNIFORM_BUFFER,
		 sizeof(light_pos_vec) + sizeof(light_color_vec),
		 NULL, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(light_pos_vec), 0,
		    light_pos_vec);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(light_color_vec),
		    sizeof(light_pos_vec), light_color_vec);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    GLuint bindex;

    bindex = glGetUniformBlockIndex(progid, "ModelBlock");
    glUniformBlockBinding(progid, bindex, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo_model);

    bindex = glGetUniformBlockIndex(progid, "SceneBlock");
    glUniformBlockBinding(progid, bindex, 1);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, ubo_scene);

    bindex = glGetUniformBlockIndex(progid, "MaterialBlock");
    glUniformBlockBinding(progid, bindex, 2);
    glBindBufferBase(GL_UNIFORM_BUFFER, 2, ubo_material);

    bindex = glGetUniformBlockIndex(progid, "LightBlock");
    glUniformBlockBinding(progid, bindex, 3);
    glBindBufferBase(GL_UNIFORM_BUFFER, 3, ubo_light);
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

    png_read_file("textures/grass.png", &image_txt);
    png_read_file("textures/abcd1234.png", &image_grass);

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

    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, tid_base);

    //glActiveTexture(GL_TEXTURE1);
    //glBindTexture(GL_TEXTURE_2D, tid_text);

    glActiveTexture(GL_TEXTURE0);

    glUseProgram(progid);

    GLuint baseloc = glGetUniformLocation(progid, "basetex");
    GLuint textloc = glGetUniformLocation(progid, "texttex");

    DBG_TRACE(0, "Texlocs %d %d\n", baseloc, textloc);

    glUniform1i(baseloc, 0);
    glUniform1i(textloc, 1);

    png_free_image(&image_grass);
    png_free_image(&image_txt);
}

static GLfloat model_translate[3] = { 0.0f, 0.0f, 0.0f };
static GLfloat model_scale[3] = { 0.66f, 0.66f, 0.66f };
static GLfloat model_rotate_axis[3] = { 0.0f, 0.0f, 0.0f };

static GLfloat model_rotate_angle = 0.0f * M_PI / 180.0f;

static GLfloat camera_position[3] = { 1.0f, 1.0f, 1.0f };
static GLfloat camera_target[3] = { 0.0f, 0.0f, 0.0f };
static GLfloat camera_up[3] = { 0.0f, 1.0f, 0.0f };

static GLfloat fovy = 90.0f * M_PI / 180.0f;
static GLfloat aspect = 4.0f / 3.0f;
static GLfloat znear = 0.1;
static GLfloat zfar = 100.0;

void main_init(void)
{
    setshaders();

    setvaos();

    pvm_calculate_model_mat4(model_translate, model_scale,
			     model_rotate_axis, model_rotate_angle,
			     model_mat4);
    print_mat4("Model", model_mat4);

    pvm_calculate_view_mat4(camera_position, camera_target, camera_up,
			    view_mat4);
    print_mat4("View", view_mat4);

    pvm_calculate_proj_mat4(fovy, aspect, znear, zfar, proj_mat4);
    print_mat4("Proj", proj_mat4);

    setuniforms();

    DBG_TRACE(0, "Setting textures");

    settextures();
}

void main_draw(void)
{
    glUseProgram(progid);

    // Draw the triangle 1 !
    glBindVertexArray(vao[0]);

    //glDrawArrays(GL_TRIANGLES, 0, 6);
    //glDrawArrays(GL_TRIANGLES, 12, 6);
    //glDrawArrays(GL_TRIANGLES, 24, 6);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
}

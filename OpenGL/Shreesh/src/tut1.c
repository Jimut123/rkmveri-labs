#include <stdio.h>
#include <GL/glew.h>

#include "z-main.h"
#include "z-shader.h"

static GLuint progid = 0;
static GLuint vposition_loc = -1;
static GLuint vao[2] = { 0, 0 };

// An array of 3 vectors which represents 3 vertices

static const GLfloat vbo1_data[] = {
    -0.5f, 0.0f, 0.0f,
    0.5f, 0.0f, 0.0f,
    0.0f, 0.5f, 0.0f,
};

static const GLfloat vbo2_data[] = {
    -0.5f, 0.0f, 0.0f,
    0.0f, -0.5f, 0.0f,
    0.5f, 0.0f, 0.0f,
};

void main_init(void)
{
    GLuint shader[3];
    GLuint vbo = 0;

    shader[0] = opengl_createshader(GL_VERTEX_SHADER, "shaders/tut1.vert");
    shader[1] = opengl_createshader(GL_FRAGMENT_SHADER, "shaders/tut1.frag");
    shader[2] = 0;

    GLuint shlist[] = { 0, 1, -1 };

    progid = opengl_createprogram(shader, shlist);

    vposition_loc = glGetAttribLocation(progid, "vposition");
    //vposition_loc = 0;

    glGenVertexArrays(2, vao);

    glBindVertexArray(vao[0]);

    // Generate 1 buffer, put the resulting identifier in vbid
    glGenBuffers(1, &vbo);
    // The following commands will talk about our 'vbid' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vbo1_data), vbo1_data,
		 GL_STATIC_DRAW);

    glVertexAttribPointer(vposition_loc,	// attribute location
			  3,	// size
			  GL_FLOAT,	// type
			  GL_FALSE,	// normalized?
			  0,	// stride
			  (void *)0	// array buffer offset
	);
    glEnableVertexAttribArray(vposition_loc);

    glBindVertexArray(vao[1]);

    // Generate 1 buffer, put the resulting identifier in vbid
    glGenBuffers(1, &vbo);
    // The following commands will talk about our 'vbid' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vbo2_data), vbo2_data,
		 GL_STATIC_DRAW);

    glVertexAttribPointer(vposition_loc,	// attribute location
			  3,	// size
			  GL_FLOAT,	// type
			  GL_FALSE,	// normalized?
			  0,	// stride
			  (void *)0	// array buffer offset
	);
    glEnableVertexAttribArray(vposition_loc);

    glBindVertexArray(0);

}

void main_draw(void)
{
    glUseProgram(progid);

    // Draw the triangle 1 !
    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);	// Starting from vertex 0; 3 vertices total -> 1 triangle

    // Draw the triangle 2 !
    glBindVertexArray(vao[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);	// Starting from vertex 0; 3 vertices total -> 1 triangle
    glBindVertexArray(0);
}

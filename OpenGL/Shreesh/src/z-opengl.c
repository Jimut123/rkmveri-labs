#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include <GL/glew.h>

#include "z-opengl.h"
#include "z-main.h"

int opengl_init(void)
{
    // Initialize GLEW
    glewExperimental = true;	// Needed in core profile
    if (glewInit() != GLEW_OK) {
	fprintf(stderr, "Failed to initialize GLEW\n");
	return -1;
    }
    // get version info
    const GLubyte *renderer = glGetString(GL_RENDERER);	// get renderer string
    const GLubyte *version = glGetString(GL_VERSION);	// version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    glClearColor(0.0f, 0.0f, 0.25f, 0.0f);	// Blue Background
    glClearDepth(1.0f);		// Depth Buffer Setup

    glEnable(GL_DEPTH_TEST);	// Enables Depth Testing
    glDepthFunc(GL_LESS);	// The Type Of Depth Test To Do

    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPointSize(4);
}

int opengl_draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    main_draw();
}

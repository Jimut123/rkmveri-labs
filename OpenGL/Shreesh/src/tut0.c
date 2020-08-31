#include <stdlib.h>
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLuint shader[2];
GLuint program_id;

GLuint vao;
GLuint vbo;
GLuint color_loc;

static const GLfloat vbo_data[] = {
    -0.5f, 0.0f, 0.1f,
    0.5f, 0.0f, 0.1f,
    0.0f, 0.5f, 0.1f,
    -0.5f, 0.0f, 0.0f,
    +0.0, 0.5f, 0.0f,
    0.0f, -0.5f, 0.0f
};

GLfloat color1[4] = { 0.0, 0.5, 0.0, 0.4 };
GLfloat color2[4] = { 0.5, 0.0, 0.5, 0.0 };

// The GLFW window with OpenGL context
static GLFWwindow *window = NULL;

void error_callback(int error, const char *description)
{
    fputs(description, stderr);
}

void glfw_stuff(void)
{

    if (!glfwInit()) {
	fprintf(stderr, "Video initialization failed (GLFW)\n");
	exit(EXIT_FAILURE);
    }

    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_SAMPLES, 4);	// 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	// We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);	// To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	//We don't want the old OpenGL
    glfwWindowHint(GLFW_DEPTH_BITS, 32);

    window = glfwCreateWindow(800, 600, "Tutorial 0", NULL, NULL);

    if (window == NULL) {
	fprintf(stderr, "Failed to open GLFW window.\n");
	glfwTerminate();
	exit(1);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
}

void opengl_stuff(void)
{
    // Initialize GLEW
    glewExperimental = 1;	// Needed in core profile
    if (glewInit() != GLEW_OK) {
	fprintf(stderr, "Failed to initialize GLEW\n");
	exit(1);
    }
    // get version info
    const GLubyte *renderer = glGetString(GL_RENDERER);	// get renderer string
    const GLubyte *version = glGetString(GL_VERSION);	// version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// Blue Background
    glClearDepth(1.0f);		// Depth Buffer Setup

    glEnable(GL_DEPTH_TEST);	// Enables Depth Testing
    glDepthFunc(GL_LESS);	// The Type Of Depth Test To Do

    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

char *readfile(const char *fn)
{
    char *source = NULL;
    FILE *fp = fopen(fn, "r");
    if (fp != NULL) {
	/* Go to the end of the file. */
	if (fseek(fp, 0L, SEEK_END) == 0) {
	    /* Get the size of the file. */
	    long bufsize = ftell(fp);
	    if (bufsize == -1) {
		/* Error */
		return NULL;
	    }

	    /* Allocate our buffer to that size. */
	    source = malloc(sizeof(char) * (bufsize + 1));
	    if (source == NULL) {
		/* Error */
		return NULL;
	    }

	    /* Go back to the start of the file. */
	    if (fseek(fp, 0L, SEEK_SET) != 0) {
		/* Error */
		free(source);
		return NULL;
	    }

	    /* Read the entire file into memory. */
	    size_t newLen = fread(source, sizeof(char), bufsize, fp);
	    if (newLen == 0) {
		fputs("Error reading file", stderr);
		free(source);
		return NULL;
	    } else {
		source[newLen++] = '\0';	/* Just to be safe. */
	    }
	}
	fclose(fp);
    }

    return source;
}

GLuint compile_shader(GLenum type, const char *shaderfile)
{
    GLuint shader;
    GLint compiled;

    printf("Creating shader\n");

    // Create the shader object
    shader = glCreateShader(type);

    if (shader == 0) {
	fprintf(stderr, "Cannot create shader.\n");
	return 0;
    }

    GLchar *shaderbuf = readfile(shaderfile);

    // The shader source code itself is loaded to the shader object using glShaderSource.
    // The shader is then compiled using the glCompileShader function.

    // Load the shader source
    glShaderSource(shader, 1, (const GLchar const **)&shaderbuf, NULL);

    // Compile the shader
    glCompileShader(shader);

    // After compiling the shader, the status of the compile is
    // determined and any errors that were generated are printed out.

    // Check the compile status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (!compiled) {
	GLint infoLen = 0;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

	if (infoLen > 0) {
	    char *infoLog = malloc(sizeof(char) * infoLen);

	    glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
	    fprintf(stderr, "Error compiling shader:\n%s\n", infoLog);

	    free(infoLog);
	}

	glDeleteShader(shader);
	return 0;
    }

    free(shaderbuf);
    return shader;
}

GLuint create_program()
{
    printf("Creating program\n");

    // Create the program object
    GLuint progid = glCreateProgram();

    if (progid == 0)
	return 0;

    glAttachShader(progid, shader[0]);
    glAttachShader(progid, shader[1]);

    // Once the shaders have been attached, the next step the sample application does is to
    // set the location for the vertex shader attribute vPosition:

    // Finally, we are ready to link the program and check for errors:

    // Link the program
    glLinkProgram(progid);

    int linked;

    // Check the link status
    glGetProgramiv(progid, GL_LINK_STATUS, &linked);

    if (!linked) {
	GLint infoLen = 0;

	glGetProgramiv(progid, GL_INFO_LOG_LENGTH, &infoLen);

	if (infoLen > 0) {
	    char *infoLog = malloc(sizeof(char) * infoLen);

	    glGetProgramInfoLog(progid, infoLen, NULL, infoLog);
	    fprintf(stderr, "Error linking program:\n%s\n", infoLog);

	    free(infoLog);
	}

	glDeleteProgram(progid);
	return 0;
    }

    glDetachShader(progid, shader[0]);
    glDetachShader(progid, shader[1]);

    return progid;
}

void shader_stuff(void)
{
    GLuint vbo = 0;

    shader[0] = compile_shader(GL_VERTEX_SHADER, "shaders/tut0.vert");
    shader[1] = compile_shader(GL_FRAGMENT_SHADER, "shaders/tut0.frag");

    program_id = create_program();

}

void buffer_stuff(void)
{
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    // Generate 1 buffer, put the resulting identifier in vbid
    glGenBuffers(1, &vbo);
    // The following commands will talk about our 'vbid' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vbo_data), vbo_data, GL_STATIC_DRAW);

    glVertexAttribPointer(0,	// attribute location
			  3,	// size
			  GL_FLOAT,	// type
			  GL_FALSE,	// normalized?
			  0,	// stride
			  (void *)0	// array buffer offset
	);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}



void uniform_stuff(void)
{

    color_loc = glGetUniformLocation(program_id, "color");

    //printf("Color loc : %d \n", color_loc);

    glUseProgram(program_id);
}

void opengl_draw_loop(void)
{

    // Ensure we can capture the keys and mouse button being pressed and released before polling
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);

    do {
	// Clear the screen. It's not mentioned before Tutorial 02,
	// but it can cause flickering, so it's there nonetheless.
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw something
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program_id);

	// Draw the triangle 1 !
	glBindVertexArray(vao);
        glUniform4fv(color_loc, 1, color1);
	glDrawArrays(GL_TRIANGLES, 0, 3);	// Starting from vertex 0; 3 vertices total -> 1 triangle

	glDepthMask(0);
        glUniform4fv(color_loc, 1, color2);
	glDrawArrays(GL_TRIANGLES, 3, 3);	// Starting from vertex 0; 3 vertices total -> 1 triangle
	glDepthMask(1);

	// Swap buffers
	glfwSwapBuffers(window);
	glfwPollEvents();
    }				// Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
	   glfwWindowShouldClose(window) == 0);
}

int main(int argc, char **argv)
{
    glfw_stuff();
    opengl_stuff();
    shader_stuff();

    buffer_stuff();
    uniform_stuff();

    opengl_draw_loop();
}

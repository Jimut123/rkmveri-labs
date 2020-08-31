#include <stdlib.h>
#include <stdio.h>

#include <GL/glew.h>

#include "z-shader.h"

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

GLuint opengl_createshader(GLenum type, const char *shaderfile)
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

void deleteshader(GLuint shader)
{
    glDeleteShader(shader);
}

/*
 * Probably locations locs, and names are not needed.
 */

GLuint opengl_createprogram(GLuint * shaders, GLuint * shader_list)
{
    printf("Creating program\n");

    // Create the program object
    GLuint progid = glCreateProgram();

    if (progid == 0)
	return 0;

    for (int i = 0; shader_list[i] != -1; i++) {
	glAttachShader(progid, shaders[shader_list[i]]);
    }

    // Once the shaders have been attached, the next step the sample application does is to
    // set the location for the vertex shader attribute vPosition:

    // Bind variables to specific locations
//      for(int i = 0; names[i]!=NULL; i++)
//         glBindAttribLocation(progid, locs[i], names[i]);

    // In Chapter 6, “Vertex Attributes, Vertex Arrays, and Buffer Objects,” we go
    // into more detail on binding attributes. For now, note that the call to glBindAttribLocation binds the v
    // Position attribute declared in the vertex shader to location 0.
    // Later, when we specify the vertex data, this location is used to specify the position.

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

    for (int i = 0; shader_list[i] != -1; i++) {
	glDetachShader(progid, shaders[shader_list[i]]);
    }

    return progid;
}

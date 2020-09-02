#include <stdlib.h>
#include <stdio.h>

#include <GLFW/glfw3.h>

#include "z-glfw.h"
#include "z-opengl.h"

void error_callback(int error, const char *description)
{
    fputs(description, stderr);
}

void window_close_callback(GLFWwindow * window)
{
    // glfwSetWindowShouldClose(window, GL_FALSE);
}

void window_size_callback(GLFWwindow * window, int width, int height)
{
}

void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
    // glViewport(0, 0, width, height);
}

void window_pos_callback(GLFWwindow * window, int xpos, int ypos)
{
}

void window_iconify_callback(GLFWwindow * window, int iconified)
{
    if (iconified) {
	// The window was iconified
    } else {
	// The window was restored
    }
}

void window_focus_callback(GLFWwindow * window, int focused)
{
    if (focused) {
	// The window gained input focus
    } else {
	// The window lost input focus
    }
}

void window_refresh_callback(GLFWwindow * window)
{
    // draw_editor_ui(window);
    // glfwSwapBuffers(window);
}

void monitor_callback(GLFWmonitor * monitor, int event)
{
}

void key_callback(GLFWwindow * window, int key, int scancode, int action,
		  int mods)
{
}

void character_callback(GLFWwindow * window, unsigned int codepoint)
{
}

void charmods_callback(GLFWwindow * window, unsigned int codepoint, int mods)
{
}

static void cursor_position_callback(GLFWwindow * window, double xpos,
				     double ypos)
{
}

void cursor_enter_callback(GLFWwindow * window, int entered)
{
    if (entered) {
	// The cursor entered the client area of the window
    } else {
	// The cursor left the client area of the window
    }
}

void mouse_button_callback(GLFWwindow * window, int button, int action,
			   int mods)
{
}

void scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
}

void drop_callback(GLFWwindow * window, int count, const char **paths)
{
    int i;
    for (i = 0; i < count; i++) {
	// handle_dropped_file(paths[i]);
    }
}

// The GLFW window with OpenGL context
static GLFWwindow *window = NULL;

int glfw_init(int width, int height, int fullscreen)
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

    GLFWmonitor *pmonitor = glfwGetPrimaryMonitor();

    if (fullscreen) {
	int count = 0;
	const GLFWvidmode *pvidmodes = glfwGetVideoModes(pmonitor, &count);

	for (int i = 0; i < count; i++) {
	    printf
		("No:%d, Width %d, Height %d, RGB:(%d:%d:%d), Rate:%dHz\n",
		 i, pvidmodes[i].width, pvidmodes[i].height,
		 pvidmodes[i].redBits, pvidmodes[i].greenBits,
		 pvidmodes[i].blueBits, pvidmodes[i].refreshRate);
	}

	int pwidth = pvidmodes[count - 1].width;
	int pheight = pvidmodes[count - 1].height;
	int predbits = pvidmodes[count - 1].redBits;
	int pgreenbits = pvidmodes[count - 1].greenBits;
	int pbluebits = pvidmodes[count - 1].blueBits;
	int prefreshrate = pvidmodes[count - 1].refreshRate;

	if (width == 0)
	    width = pwidth;
	else
	    width = (width < 640 ? 640 : width);

	if (height == 0)
	    height = pheight;
	else
	    height = (height < 360 ? 360 : height);

	window = glfwCreateWindow(width, height, "Opengl Tutorials", pmonitor, NULL);

	const GLFWvidmode *pvidmode = glfwGetVideoMode(pmonitor);
	printf("Current Width %d, Height %d, RGB:(%d:%d:%d), Rate:%dHz\n",
	       pvidmode->width,
	       pvidmode->height,
	       pvidmode->redBits,
	       pvidmode->greenBits, pvidmode->blueBits,
	       pvidmode->refreshRate);

    } else {
	if (width == 0)
	    width = 640;
	width = (width < 640 ? 640 : width);
	if (height == 0)
	    height = 480;
	height = (height < 360 ? 360 : height);
	window = glfwCreateWindow(width, height, "Opengl Tutorials", NULL, NULL);

	int w, h;
	glfwGetWindowSize(window, &w, &h);
	printf("Current Width %d, Height %d\n", w, h);
    }

    if (window == NULL) {
	fprintf(stderr, "Failed to open GLFW window.\n");
	glfwTerminate();
	return -1;
    }

    glfwSetWindowCloseCallback(window, window_close_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetWindowPosCallback(window, window_pos_callback);
    glfwSetWindowIconifyCallback(window, window_iconify_callback);
    glfwSetWindowFocusCallback(window, window_focus_callback);
    glfwSetWindowRefreshCallback(window, window_refresh_callback);
    glfwSetMonitorCallback(monitor_callback);

    glfwSetKeyCallback(window, key_callback);
    glfwSetCharCallback(window, character_callback);
    glfwSetCharModsCallback(window, charmods_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetCursorEnterCallback(window, cursor_enter_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetDropCallback(window, drop_callback);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

}

int glfw_finish()
{
    glfwTerminate();
}

void glfw_loop()
{
    // Ensure we can capture the keys and mouse button being pressed and released before polling
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);

    do {
	// Clear the screen. It's not mentioned before Tutorial 02,
	// but it can cause flickering, so it's there nonetheless.
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw something
	opengl_draw();

	// Swap buffers
	glfwSwapBuffers(window);
	glfwPollEvents();
    }				// Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
	   glfwWindowShouldClose(window) == 0);
}

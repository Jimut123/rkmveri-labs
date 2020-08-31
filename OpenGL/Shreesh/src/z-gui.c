#include <stdbool.h>
#include <stdlib.h>

#include "z-gui.h"
#include "z-glfw.h"
#include "z-opengl.h"

#include "z-main.h"

int gui_init(int width, int height, int fullscreen)
{
    glfw_init(width, height, fullscreen);
    opengl_init();
    main_init();
}

int gui_finish(void)
{
    glfw_finish();
}

void gui_loop(void)
{
    glfw_loop();
}

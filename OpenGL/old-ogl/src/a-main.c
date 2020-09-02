#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "a-defs.h"
#include <assert.h>

#include "debug.h"

#include "z-gui.h"
#include "z-options.h"
#include "z-util.h"

int main(int argc, char **argv)
{
    struct options_st opt = { 0, 0, 0, 0, NULL, 1 };

#ifdef DEBUG
    dbg_init();
#endif
    process_options(argc, argv, &opt);

    setverbosity(opt.verbose);

#ifdef DEBUG
    dbg_setdebug(opt.debug);

    char *subsys[] = { "default", "gui", "opengl", "world", NULL };

    dbg_msetsubsysnames(subsys);
    if (opt.mdebug != NULL)
	dbg_parsearg(opt.mdebug);
#endif

    gui_init(opt.width, opt.height, opt.fullscreen);
    gui_loop();
    gui_finish();
}

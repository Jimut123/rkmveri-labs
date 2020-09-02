LDADD = ../lib/libcommon.a  -lGL -lGLEW -lglfw  -lpng -lm
AM_CPPFLAGS = -DDEBUG -I$(srcdir)/../lib
AM_CFLAGS = 

COMMON_FILES = a-defs.h \
	../lib/debug.h \
	z-gui.h z-glfw.h z-options.h z-util.h z-list.h\
	z-gui.c z-glfw.c z-options.c z-util.c z-list.c\
	z-png.h z-opengl.h z-shader.h z-pvm.h z-mat.h\
	z-png.c z-opengl.c z-shader.c z-pvm.c z-mat.c\
	z-camera.h z-models.h z-materials.h z-world.h z-light.h\
	z-camera.c z-models.c z-materials.c z-world.c z-light.c\
	a-main.c \
	z-main.h 

bin_PROGRAMS = tut0 tut1 tut2 tut3 tut4

tut0_SOURCES = tut0.c

tut4_SOURCES = $(COMMON_FILES) \
	tut4.c

tut3_SOURCES = $(COMMON_FILES) \
	tut3.c

tut2_SOURCES = $(COMMON_FILES) \
	tut2.c

tut1_SOURCES = $(COMMON_FILES) \
	tut1.c


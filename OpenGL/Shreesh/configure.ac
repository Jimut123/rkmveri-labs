#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([autoworld], [0.0], [sarvottamananda@gmail.com])

AC_CONFIG_AUX_DIR(config)

AM_INIT_AUTOMAKE([foreign])

AC_CONFIG_SRCDIR([src/a-main.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CC_STDC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB

# Checks for libraries.
PKG_CHECK_MODULES([GL], [gl])
PKG_CHECK_MODULES([GLFW], [glfw3])
PKG_CHECK_MODULES([GLEW], [glew])
PKG_CHECK_MODULES([FREETYPE], [freetype2])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC

AC_CONFIG_FILES([Makefile src/Makefile lib/Makefile])
AC_OUTPUT

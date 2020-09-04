# oglcs : OpenGL Code Snippets

This project contains beginner level OpenGL code snippets. The purpose is to learn OpenGL through
practical programming. 

The code snippets use OpenGL 4.0+

## Compiling snippets in Linux

To compile all the code snippets in the directory run the following

$ meson build
$ meson compile -C build

The executables are created as ${projectdir}/build/src/*/*
Run individual execuatable for each snippet.

## Running all snippets

To run all the snippets from the directory do the following too.

$ meson test -C build


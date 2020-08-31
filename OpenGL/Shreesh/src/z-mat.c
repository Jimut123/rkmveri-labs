#include <stdio.h>
#include <math.h>
#include <GL/glew.h>

#include "z-mat.h"

void print_vec3(char *name, GLfloat vec[3])
{
    printf("%s : [ ", name);
    for (int i = 0; i < 3; i++) {
	printf("%7.5f ", vec[i]);
    }
    printf("]\n");
}

void print_vec4(char *name, GLfloat vec[4])
{
    printf("%s : [ ", name);
    for (int i = 0; i < 4; i++) {
	printf("%7.5f ", vec[i]);
    }
    printf("]\n");
}

void print_mat4(char *name, GLfloat mat[4][4])
{
    printf("%s :\n", name);
    for (int i = 0; i < 4; i++) {
	printf("[ ");
	for (int j = 0; j < 4; j++)
	    printf("%7.5f ", mat[j][i]);
	printf("]\n");
    }
}

void set_identity_mat4(GLfloat mat[][4])
{
    for (int j = 0; j < 4; j++) {
	for (int i = 0; i < 4; i++) {
	    mat[j][i] = 0.0;
	}
	mat[j][j] = 1.0;
    }
}

void unit_vec3(GLfloat v[])
{
    v[0] = 1.0f;
    v[1] = 1.0f;
    v[2] = 1.0f;
}

void unit_vec4(GLfloat v[])
{
    v[0] = 1.0f;
    v[1] = 1.0f;
    v[2] = 1.0f;
    v[3] = 1.0f;
}

void zero_vec2(GLfloat v[])
{
    v[0] = 0.0f;
    v[1] = 0.0f;
}

void zero_vec3(GLfloat v[])
{
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
}

void zero_vec4(GLfloat v[])
{
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 0.0f;
}

void set_vec2(GLfloat v0, GLfloat v1, GLfloat v[])
{
    v[0] = v0;
    v[1] = v1;
}

void set_vec3(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v[])
{
    v[0] = v0;
    v[1] = v1;
    v[2] = v2;
}

void set_vec4(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v[])
{
    v[0] = v0;
    v[1] = v1;
    v[2] = v2;
    v[3] = v3;
}

void copy_vec2(GLfloat v[2], GLfloat res[])
{
    res[0] = v[0];
    res[1] = v[1];
}

void copy_vec3(GLfloat v[3], GLfloat res[])
{
    res[0] = v[0];
    res[1] = v[1];
    res[2] = v[2];
}

void copy_vec4(GLfloat v[4], GLfloat res[])
{
    res[0] = v[0];
    res[1] = v[1];
    res[2] = v[2];
    res[3] = v[3];
}

void copy_mat4(GLfloat a[4][4], GLfloat res[][4])
{
    for (int j = 0; j < 4; j++) {
	for (int i = 0; i < 4; i++) {
	    res[j][i] = a[j][i];
	}
    }
}

void transpose_mat4(GLfloat a[4][4], GLfloat res[][4])
{
    GLfloat tmp[4][4];

    for (int j = 0; j < 4; j++) {
	for (int i = 0; i < 4; i++) {
	    tmp[j][i] = a[i][j];
	}
    }
    copy_mat4(tmp, res);
}

void add_mat4(GLfloat a[4][4], GLfloat b[4][4], GLfloat res[][4])
{
    for (int j = 0; j < 4; j++) {
	for (int i = 0; i < 4; i++) {
	    res[j][i] = a[j][i] + b[j][i];
	}
    }
}

void sub_vec3(GLfloat v1[3], GLfloat v2[3], GLfloat res[])
{
    res[0] = v1[0] - v2[0];
    res[1] = v1[1] - v2[1];
    res[2] = v1[2] - v2[2];
}

void add_vec3(GLfloat v1[3], GLfloat v2[3], GLfloat res[])
{
    res[0] = v1[0] + v2[0];
    res[1] = v1[1] + v2[1];
    res[2] = v1[2] + v2[2];
}

void mult_mat4(GLfloat a[4][4], GLfloat b[4][4], GLfloat res[][4])
{
    GLfloat tmp[4][4];

    for (int j = 0; j < 4; j++) {
	for (int i = 0; i < 4; i++) {
	    GLfloat sum = 0;

	    for (int k = 0; k < 4; k++) {
		sum += a[k][i] * b[j][k];
	    }
	    tmp[j][i] = sum;
	}
    }
    copy_mat4(tmp, res);
}

void normalize_vec3(GLfloat v[])
{
    GLfloat len = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

    if (len != 0.0f) {
	v[0] = v[0] / len;
	v[1] = v[1] / len;
	v[2] = v[2] / len;
    } else {
	v[0] = 1.0;
	v[1] = v[2] = 0.0;
    }
}

void cross_vec3(GLfloat v1[], GLfloat v2[], GLfloat res[])
{
    res[0] = v1[1] * v2[2] - v1[2] * v2[1];
    res[1] = v1[2] * v2[0] - v1[0] * v2[2];
    res[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

GLfloat dot_vec3(GLfloat v1[], GLfloat v2[])
{
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

void inverse_mat3(GLfloat m[3][3], GLfloat res[][3])
{
    // computes the inverse of a matrix m

    GLfloat m00 = (m[1][1] * m[2][2] - m[2][1] * m[1][2]);
    GLfloat m10 = (-m[1][0] * m[2][2] + m[1][2] * m[2][0]);
    GLfloat m20 = (m[1][0] * m[2][1] - m[1][1] * m[2][0]);

    GLfloat det = m[0][0] * m00 + m[0][1] * m10 + m[0][2] * m20;

    GLfloat invdet = 1 / det;

    res[0][0] = m00 * invdet;
    res[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) * invdet;
    res[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * invdet;
    res[1][0] = m10 * invdet;
    res[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * invdet;
    res[1][2] = (m[1][0] * m[0][2] - m[0][0] * m[1][2]) * invdet;
    res[2][0] = m20 * invdet;
    res[2][1] = (m[2][0] * m[0][1] - m[0][0] * m[2][1]) * invdet;
    res[2][2] = (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * invdet;
}

void inverse_mat4(GLfloat a[4][4], GLfloat res[][4])
{
    GLfloat s0 = a[0][0] * a[1][1] - a[1][0] * a[0][1];
    GLfloat s1 = a[0][0] * a[1][2] - a[1][0] * a[0][2];
    GLfloat s2 = a[0][0] * a[1][3] - a[1][0] * a[0][3];
    GLfloat s3 = a[0][1] * a[1][2] - a[1][1] * a[0][2];
    GLfloat s4 = a[0][1] * a[1][3] - a[1][1] * a[0][3];
    GLfloat s5 = a[0][2] * a[1][3] - a[1][2] * a[0][3];

    GLfloat c5 = a[2][2] * a[3][3] - a[3][2] * a[2][3];
    GLfloat c4 = a[2][1] * a[3][3] - a[3][1] * a[2][3];
    GLfloat c3 = a[2][1] * a[3][2] - a[3][1] * a[2][2];
    GLfloat c2 = a[2][0] * a[3][3] - a[3][0] * a[2][3];
    GLfloat c1 = a[2][0] * a[3][2] - a[3][0] * a[2][2];
    GLfloat c0 = a[2][0] * a[3][1] - a[3][0] * a[2][1];

    // Should check for 0 determinant
    GLfloat invdet =
	1.0 / (s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0);

    res[0][0] = (a[1][1] * c5 - a[1][2] * c4 + a[1][3] * c3) * invdet;
    res[0][1] = (-a[0][1] * c5 + a[0][2] * c4 - a[0][3] * c3) * invdet;
    res[0][2] = (a[3][1] * s5 - a[3][2] * s4 + a[3][3] * s3) * invdet;
    res[0][3] = (-a[2][1] * s5 + a[2][2] * s4 - a[2][3] * s3) * invdet;

    res[1][0] = (-a[1][0] * c5 + a[1][2] * c2 - a[1][3] * c1) * invdet;
    res[1][1] = (a[0][0] * c5 - a[0][2] * c2 + a[0][3] * c1) * invdet;
    res[1][2] = (-a[3][0] * s5 + a[3][2] * s2 - a[3][3] * s1) * invdet;
    res[1][3] = (a[2][0] * s5 - a[2][2] * s2 + a[2][3] * s1) * invdet;

    res[2][0] = (a[1][0] * c4 - a[1][1] * c2 + a[1][3] * c0) * invdet;
    res[2][1] = (-a[0][0] * c4 + a[0][1] * c2 - a[0][3] * c0) * invdet;
    res[2][2] = (a[3][0] * s4 - a[3][1] * s2 + a[3][3] * s0) * invdet;
    res[2][3] = (-a[2][0] * s4 + a[2][1] * s2 - a[2][3] * s0) * invdet;

    res[3][0] = (-a[1][0] * c3 + a[1][1] * c1 - a[1][2] * c0) * invdet;
    res[3][1] = (a[0][0] * c3 - a[0][1] * c1 + a[0][2] * c0) * invdet;
    res[3][2] = (-a[3][0] * s3 + a[3][1] * s1 - a[3][2] * s0) * invdet;
    res[3][3] = (a[2][0] * s3 - a[2][1] * s1 + a[2][2] * s0) * invdet;

}

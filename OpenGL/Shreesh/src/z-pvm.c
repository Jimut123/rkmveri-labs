#include <stdio.h>
#include <math.h>
#include <GL/glew.h>

#include "z-pvm.h"
#include "z-mat.h"

GLfloat degtorad(GLfloat deg)
{
    return deg * M_PI / 180.0f;
}

GLfloat radtodeg(GLfloat rad)
{
    return rad * 180.0f / M_PI;
}

void set_scale_mat4(GLfloat mat[][4], GLfloat v[3])
{
    set_identity_mat4(mat);
    for (int i = 0; i < 3; i++)
	mat[i][i] = v[i];
}

void set_translate_mat4(GLfloat mat[][4], GLfloat v[3])
{
    set_identity_mat4(mat);
    for (int i = 0; i < 3; i++)
	mat[3][i] = v[i];
}

void set_rotate_mat4(GLfloat mat[][4], GLfloat v[3], GLfloat alpha)
{
    GLfloat c = cosf(alpha);
    GLfloat s = sinf(alpha);
    GLfloat t = 1 - c;

    normalize_vec3(v);
    GLfloat x = v[0];
    GLfloat y = v[1];
    GLfloat z = v[2];

    /*
     *     | (tx² + c)  (txy - sz) (txz + sy) |
     * M = | (txy + sz) (ty² + c)  (tyz - sx) |
     *     | (txz - sy) (tyz + sx) (tz² + c)  |
     */

    mat[0][0] = t * x * x + c;
    mat[1][0] = t * x * y - s * z;
    mat[2][0] = t * x * z + s * y;

    mat[0][1] = t * y * x + s * z;
    mat[1][1] = t * y * y + c;
    mat[2][1] = t * y * z - s * x;

    mat[0][2] = t * z * x - s * y;
    mat[1][2] = t * z * y + s * x;
    mat[2][2] = t * z * z + c;

    mat[3][0] = mat[3][1] = mat[3][2] = 0;
    mat[0][3] = mat[1][3] = mat[2][3] = 0;
    mat[3][3] = 1.0;

}

void pvm_calculate_model_mat4(GLfloat tr[3],
			      GLfloat sc[3],
			      GLfloat rot[3], GLfloat rot_ang,
			      GLfloat res[][4])
{
    GLfloat scale[4][4];
    GLfloat translate[4][4];
    GLfloat rotate[4][4];

    set_scale_mat4(scale, sc);
    set_translate_mat4(translate, tr);
    set_rotate_mat4(rotate, rot, rot_ang);

    GLfloat tmp[4][4];

    mult_mat4(rotate, scale, tmp);
    mult_mat4(translate, tmp, res);
}

void pvm_calculate_view_mat4(GLfloat cpos[3],
			     GLfloat ctgt[3], GLfloat up[3], GLfloat res[][4])
{
    GLfloat zaxis[3];
    GLfloat yaxis[3];
    GLfloat xaxis[3];

    sub_vec3(cpos, ctgt, zaxis);
    normalize_vec3(zaxis);

    cross_vec3(up, zaxis, xaxis);
    normalize_vec3(xaxis);

    cross_vec3(zaxis, xaxis, yaxis);
    // Not needed
    // normalize_vec3(yaxis);

    //print_vec3("zaxis",zaxis);
    //print_vec3("xaxis",xaxis);
    //print_vec3("yaxis",yaxis);

    res[0][0] = xaxis[0];
    res[1][0] = xaxis[1];
    res[2][0] = xaxis[2];

    res[0][1] = yaxis[0];
    res[1][1] = yaxis[1];
    res[2][1] = yaxis[2];

    res[0][2] = zaxis[0];
    res[1][2] = zaxis[1];
    res[2][2] = zaxis[2];

    res[3][0] = -dot_vec3(xaxis, cpos);
    res[3][1] = -dot_vec3(yaxis, cpos);
    res[3][2] = -dot_vec3(zaxis, cpos);

    res[0][3] = 0;
    res[1][3] = 0;
    res[2][3] = 0;

    res[3][3] = 1;

}

void pvm_calculate_proj_mat4(GLfloat fovy,
			     GLfloat a, GLfloat n, GLfloat f,
			     GLfloat res[][4])
{
    set_identity_mat4(res);

    GLfloat e = 1 / tanf(fovy / 2.0f);

    res[0][0] = e / a;
    res[1][1] = e;
    res[2][2] = -(f + n) / (f - n);
    res[3][3] = 0;
    res[3][2] = -2 * f * n / (f - n);
    res[2][3] = -1.0;
}

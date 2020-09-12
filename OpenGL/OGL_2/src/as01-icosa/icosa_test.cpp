#include <iostream>
#include <cstdlib>
#include <iostream>
#include <cmath>




int main()
{
	// constants
    const float PI = 3.1415926f;
    const float H_ANGLE = PI / 180 * 72;    // 72 degree = 360 / 5
    const float V_ANGLE = atanf(1.0f / 2);  // elevation = 26.565 degree

    float vertices_gen[12 * 3];    // array of 12 vertices (x,y,z)
    int i1, i2;                             // indices
    float z, xy;                            // coords
    float hAngle1 = -PI / 2 - H_ANGLE / 2;  // start from -126 deg at 1st row
    float hAngle2 = -PI / 2;                // start from -90 deg at 2nd row

    const float radius = 0.5f;

    // the first top vertex at (0, 0, r)
    vertices_gen[0] = 0;
    vertices_gen[1] = 0;
    vertices_gen[2] = radius;

    // compute 10 vertices at 1st and 2nd rows
    for(int i = 1; i <= 5; ++i)
    {
        i1 = i * 3;         // index for 1st row
        i2 = (i + 5) * 3;   // index for 2nd row

        z  = radius * sinf(V_ANGLE);            // elevaton
        xy = radius * cosf(V_ANGLE);            // length on XY plane

        vertices_gen[i1] = xy * cosf(hAngle1);      // x
        vertices_gen[i2] = xy * cosf(hAngle2);
        vertices_gen[i1 + 1] = xy * sinf(hAngle1);  // y
        vertices_gen[i2 + 1] = xy * sinf(hAngle2);
        vertices_gen[i1 + 2] = z;                   // z
        vertices_gen[i2 + 2] = -z;

        // next horizontal angles
        hAngle1 += H_ANGLE;
        hAngle2 += H_ANGLE;
    }

    // the last bottom vertex at (0, 0, -r)
    i1 = 11 * 3;
    vertices_gen[i1] = 0;
    vertices_gen[i1 + 1] = 0;
    vertices_gen[i1 + 2] = -radius;

    const int len = sizeof(vertices_gen)/sizeof(vertices_gen[0]);
    float vertices[len * 2];      // get the vertices and colors
    int counter = 0;
    for(int i = 0; i < len; i+=3 )
    {
        vertices[counter] = vertices_gen[i];
        vertices[counter+1] = vertices_gen[i+1];
        vertices[counter+2] = vertices_gen[i+2];

        vertices[counter+3] = 0.0f;
        vertices[counter+4] = 1.0f;
        vertices[counter+5] = 1.0f;

        counter += 6;

        //std::cout<<" x1  = "<<vertices_gen[i]<<" x2 = "<<vertices_gen[i+1]<<" x3 = "<<vertices_gen[i+3]<<std::endl;
        std::cout<<"("<<vertices_gen[i]<<","<<vertices_gen[i+1]<<","<<vertices_gen[i+3]<<")"<<std::endl;
    }

}

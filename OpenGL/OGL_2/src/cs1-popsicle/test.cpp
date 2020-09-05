#include <iostream>
#include <cmath>

int main()
{
    /*
        int total_count = 0;
    for(float theta = 0; theta <= 360; theta+=5)
    {
        total_count += 1;
    }

    GLfloat vertices[73*6];
    float x, x_coord, y_coord, sin_x, cos_x,radius = 0.5f;
    int counter = 0; 
    vertices[counter] = 0.0f;
    vertices[counter+1] = 0.0f;
    vertices[counter+2] = 0.0f;
    vertices[counter+3] = 1.0f;
    vertices[counter+4] = 0.5f;
    vertices[counter+5] = 0.5f;
    
    for(int theta = 0; theta <= 360; theta+=5)
    {
        x = theta*3.14159/180;
        sin_x = sin(x);
        cos_x = cos(x);
        x_coord = radius * cos_x;
        y_coord = radius * sin_x;
        //printf("x coord = %3.5f y coord = %3.5f ",x_coord,y_coord);
        std::cout<<"x coord = "<<x_coord<<" y coord = "<<y_coord<<std::endl;
        vertices[counter] = x_coord;
        vertices[counter+1] = y_coord;
        vertices[counter+2] = 0.0f;
        vertices[counter+3] = 1.0f;
        vertices[counter+4] = 0.5f;
        vertices[counter+5] = 0.5f;
        if(theta == 10)
        {
            // Then we need to copy the previous vertices
            vertices[counter] = vertices[counter-6];
            vertices[counter+1] = vertices[counter-5];
            vertices[counter+2] = vertices[counter-4];
            vertices[counter+3] = vertices[counter-3];
            vertices[counter+4] = vertices[counter-2];
            vertices[counter+5] = vertices[counter-1];

            vertices[counter+6] = 0.0f;
            vertices[counter+7] = 0.0f;
            vertices[counter+8] = 0.0f;
            vertices[counter+9] = 1.0f;
            vertices[counter+10] = 0.5f;
            vertices[counter+11] = 0.5f;

            counter += 12;

        }
        counter += 6;
    }

    */
    float vertices[73*6];
    float x, x_coord, y_coord, sin_x, cos_x;
    int counter = 0;
    float radius = 0.5f;
    vertices[counter] = 0.0f;
    vertices[counter+1] = 0.0f;
    vertices[counter+2] = 0.0f;
    vertices[counter+3] = 1.0f;
    vertices[counter+4] = 0.5f;
    vertices[counter+5] = 0.5f;
    
    for(int theta = 0; theta <= 360; theta+=5)
    {
        x = (float)theta*3.14159/180;
        sin_x = sin(x);
        cos_x = cos(x);
        std::cout<<"sin(x) = "<<sin_x<<" cos_x = "<<cos_x<<std::endl;
        x_coord = (float)radius * cos_x;
        y_coord = (float)radius * sin_x;
        //printf("x coord = %3.5f y coord = %3.5f ",x_coord,y_coord);
        std::cout<<"x coord = "<<x_coord<<" y coord = "<<y_coord<<std::endl;
        vertices[counter] = x_coord;
        vertices[counter+1] = y_coord;
        vertices[counter+2] = 0.0f;
        vertices[counter+3] = 1.0f;
        vertices[counter+4] = 0.5f;
        vertices[counter+5] = 0.5f;
        if(theta == 10)
        {
            // Then we need to copy the previous vertices
            vertices[counter] = vertices[counter-6];
            vertices[counter+1] = vertices[counter-5];
            vertices[counter+2] = vertices[counter-4];
            vertices[counter+3] = vertices[counter-3];
            vertices[counter+4] = vertices[counter-2];
            vertices[counter+5] = vertices[counter-1];

            vertices[counter+6] = 0.0f;
            vertices[counter+7] = 0.0f;
            vertices[counter+8] = 0.0f;
            vertices[counter+9] = 1.0f;
            vertices[counter+10] = 0.5f;
            vertices[counter+11] = 0.5f;

            counter += 12;

        }
        counter += 6;
    }
    return EXIT_SUCCESS;
}
#include <iostream>
#include <cmath>

int main()
{
    int total_count = 0;

    for(float theta = 0; theta <= 360; theta+=5)
    {
        total_count += 1;
    }
    printf("Total count = %d",total_count);

    float result, x = 270*3.14159/180;
    result = sin(x);
    printf("result = %f",result);
    return EXIT_SUCCESS;
}
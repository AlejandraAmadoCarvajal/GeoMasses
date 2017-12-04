#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

int main()
{
    /*Funciones de lectura */
    FILE *ptr_file;
    char buf[1000];
    ptr_file = fopen("RadialVelocities.dat", "r");

    if (!ptr_file)
        return 1;

    while (fgets(buf, 1000, ptr_file)!=NULL)
        printf("%s",buf);

    fclose(ptr_file);
    return 0;
}


#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#define LENGTH 300
#define BB 0.2497
#define BD 5.16
#define AD 0.3105
#define AH 64.3
#define MBSEARCH 10.0
#define MDSEARCH 4.0
#define MHSEARCH 4.0

float modelo_chi2(float *X, float *F, float Mb, float Md, float Mh){
    float likelihood = 0;
    for(int i = 0; i < LENGTH; i++){
        float model = pow(Mb,0.5)*X[i]/pow(pow(X[i],2)+pow(BB,2),0.75) + (pow(Md,0.5)*X[i]/pow( pow(X[i],2)+pow(BD + AD,2) ,0.75)) + (pow(Mh,0.5)/pow(pow(X[i],2)+pow(AH,2),0.25));
        /*Chi cuadrado*/
        likelihood += pow(pow(model - F[i],2), 0.5);
    }
    return likelihood;
};
/*Tomado de https://stackoverflow.com/questions/13408990/how-to-generate-random-float-number-in-c*/
float float_rand( float min, float max )
{
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    /*return min + scale * ( max - min );      [> [min, max] <]*/
    return (max - min) - scale*2.0*(max - min);
}

int main(){
    srand(time(NULL));
    /*Declaracion de constantes */
    float Mb;
    float Md;
    float Mh;
    /*Declaracion de constantes, con valores iniciales*/
    float init_Mb = 3000;
    float init_Md = 2000;
    float init_Mh = 1000;
    /*Estructuras de datos */
    float *Radii = malloc(LENGTH*sizeof(float));
    float *Velocidades = malloc(LENGTH*sizeof(float));
    /*Procedimientos para la lectura del archivo*/
    FILE *file_id = fopen("RadialVelocities.dat", "r");
    char buff[1000];
    int foo = fscanf(file_id, "%s %s\n", buff, buff);
    for (int i = 0; i < LENGTH; i++){
        fscanf(file_id, "%f %f\n", &Radii[i], &Velocidades[i]);
    }
    fclose(file_id);
    /*Inicialización de la caminata aleatoria*/
    float likelihood_init = modelo_chi2(Radii, Velocidades, init_Mb, init_Md, init_Mh);
    /*Procedimientos para la escritura de archivos*/
    FILE *file_out = fopen("datos.dat", "w");
    fprintf(file_out, "%f, %f, %f, %f\n", init_Mb, init_Md, init_Mh, likelihood_init);
    for(int i = 0; i < 50000; i++){
    /*Cuadro de busqueda */
        Mb = float_rand(init_Mb - MBSEARCH, init_Mb + MBSEARCH);
        Md = float_rand(init_Md - MDSEARCH, init_Md + MDSEARCH); 
        Mh = float_rand(init_Mh - MHSEARCH, init_Mh + MHSEARCH); 
        Mb += init_Mb;
        Md += init_Md;
        Mh += init_Mh;
        float likelihood_post = modelo_chi2(Radii, Velocidades, Mb, Md, Mh);
        float condition = likelihood_post/likelihood_init;
        if(condition<1){
            likelihood_init = likelihood_post;
            init_Mb = Mb;
            init_Md = Md;
            init_Mh = Mh;
        }
        /*Impresion a file*/
        fprintf(file_out, "%f,%f,%f,%f\n", init_Mb, init_Md, init_Mh, likelihood_init);
    }
    printf("\nSimulacion finalizada ultimos valores, \nMb \t %f, \t Md \t %f, \t Mh %f\n", init_Mb, init_Md, init_Mh);
    return 0;
}



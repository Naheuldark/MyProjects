#include "pgm.h"
#include "filtres.h"
#include <math.h>
#include <time.h>

double** filtre_estim() {
    double** filtre =  alloue_image_double(3, 3);
    filtre[0][0] = 0;
    filtre[0][1] = -1;
    filtre[0][2] = 0;

    filtre[1][0] = -1;
    filtre[1][1] = 5;
    filtre[1][2] = -1;
    
    filtre[2][0] = 0;
    filtre[2][1] = -1;
    filtre[2][2] = 0;
    return filtre;
}

double** convolution2D(double** I, int nl, int nc, int W, double** filtre) {
    double **R = alloue_image_double(nl,nc);
    for (int x = 0; x < nl; ++x) {
        for (int y = 0; y < nc; ++y) {
            R[x][y] = 0;

            for (int i = -W; i <= W ; i++) {
                for (int j = -W; j <= W ; j++) {
                    R[x][y] += I[(x+i+nl)%nl][(y+j+nc)%nc] * filtre[i+W][j+W];
                }
            }
        }       
    }
    return R;
}

double estimation_bruit(double **in, int nl, int nc, int t, double p) {
    double** filtre = filtre_estim();
    double** im_filtree = convolution2D(in, nl, nc, 1, filtre);
    
    double varH[200] = {0};
    double moyenne = 0;
    double moyenne_carre = 0;
    double variance = 0;

    for (int i = t ; i <= nl - t - 1; i++) {
        for (int j = t ; j <= nc - t - 1; j++) {

            moyenne = 0;
            moyenne_carre = 0;
            for (int kx = -t ; kx <= t ; kx++) {
                for (int ky = -t ; ky <= t ; ky++) {
                    moyenne += in[i+kx][j+ky];
                    moyenne_carre += in[i+kx][j+ky] * in[i+kx][j+ky];
                }
            }

            moyenne /= (2*t+1)*(2*t+1);
            moyenne_carre /= (2*t+1)*(2*t+1);

            variance = moyenne_carre - moyenne*moyenne;
            if (variance < 199)
                varH[(int)variance]++;
        }

    }

    double nb_pixels = 0;
    int i = 0;
    while (nb_pixels < (p*nl*nc)/100) {
        nb_pixels += varH[i++];
    }  

    return 1.13 * i;

}


int main (int ac, char **av) 
{  
    int nl, nc;
    unsigned char **in = NULL, **out = NULL, **ref = NULL;
    double **im1 = NULL, **im2 = NULL;

    char strings_in[3][50] = {"../in/formes1pets10.pgm", "../in/formes2bb30.pgm", "../in/globulesbb50.pgm"};
    char strings_short[3][50] = {"formes1pets10.pgm", "formes2bb30.pgm", "globulesbb50.pgm"};
    char strings_references[3][50] = {"../in/formes1.pgm", "../in/formes2.pgm", "../in/globules.pgm"};
    char noms_filtres [4][50] = {"Filtre Médian", "Filtre Adaptatif Récursif", "Filtre Bilatéral", "Filtre NL-Means"};
    char strings_out[4][3][50] = {{"../out/tp2/formes1_median.pgm", "../out/tp2/formes2_median.pgm", "../out/tp2/globules_median.pgm"},
                                  {"../out/tp2/formes1_recursif.pgm", "../out/tp2/formes2_recursif.pgm", "../out/tp2/globules_recursif.pgm"},
                                  {"../out/tp2/formes1_bilat.pgm", "../out/tp2/formes2_bilat.pgm", "../out/tp2/globules_bilat.pgm"},
                                  {"../out/tp2/formes1_nlmeans.pgm", "../out/tp2/formes2_nlmeans.pgm", "../out/tp2/globules_nlmeans.pgm"}};
    
    for (int image = 0; image < 3; image++) {

        printf("############# IMAGE ETUDIEE : %s #############\n\n", strings_short[image]);

        in = lectureimagepgm(strings_in[image], &nl, &nc);
        ref = lectureimagepgm(strings_references[image], &nl, &nc);
        im1 = imuchar2double(in, nl, nc);
            if (in == NULL)  { 
                puts("Lecture image impossible"); 
                exit(1); 
            }


        for (int filtre = 0; filtre < 4; filtre++) {

            printf("RESULTATS POUR %s\n\n", noms_filtres[filtre]);

            clock_t debut, fin;
            debut = clock();

            switch (filtre)
            {
            case 0:
                im2 = filtremedian(im1, nl, nc, 5);
                break;
            case 1:
                im2 = filtreadaptatif(im1, nl, nc, 20);
                break;
            case 2:
                im2 = filtrebilateral(im1, nl, nc, 10, 15);
                break;
            case 3:
                im2 = filtreMNL(im1, nl, nc, 7, 2, 40);
                break;
            }

            fin  = clock();
            printf("Temps d'exectution du filtre :                    %f\n", ((double)(fin - debut))/ CLOCKS_PER_SEC);
            printf("Estimation du bruit :                             %f\n", estimation_bruit(im2, nl, nc, 10, 50));

            out = imdouble2uchar(im2, nl, nc);
            ecritureimagepgm(strings_out[filtre][image],
                             crop(out, 0, 0, nl, nc),
                             nl, nc);

            printf("PSNR entre l'image référence et l'image filtrée : %f\n\n\n", psnr(out, ref, nl, nc));


        }

    }

}


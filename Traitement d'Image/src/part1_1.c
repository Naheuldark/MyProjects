#include "pgm.h"
#include <math.h>

/* 
	Application du filtre gaussien en utilisant la FFT
	S'utilise sous la forme  "exemple tangram.pgm res.pgm"
 */

double FTGauss2D(double sigma, double u, double v) {
    return exp(-2*pow(M_PI*sigma,2)*(pow(u,2)+pow(v,2)));
}

double PSNR(unsigned char** im1, unsigned char** im2, int nl, int nc) {
    double res = 0;
    for (int i = 0; i < nl; ++i)
        for (int j = 0; j < nc; ++j)
            res += pow(im1[i][j] - im2[i][j],2);

    res = (pow(255,2)*nl*nc)/res;
    return 10*log10(res);
}

unsigned char** filter(unsigned char** in, int nl, int nc, double sigma) {
    int oldnl = nl;
    int oldnc = nc;
    double **im0, **im1, **im2, **im2_shift, 
           **im3, **im3_shift, **im4, **im4_shift, 
           **im5, **im5_shift, **im6, **im7;

    im0 = padimucforfft(in, &nl, &nc);

    im1 = alloue_image_double(nl, nc);
    im2 = alloue_image_double(nl, nc);
    im2_shift = alloue_image_double(nl, nc);
    im3 = alloue_image_double(nl, nc);
    im3_shift = alloue_image_double(nl, nc);
    im4 = alloue_image_double(nl, nc);
    im4_shift = alloue_image_double(nl, nc);
    im5 = alloue_image_double(nl, nc);
    im5_shift = alloue_image_double(nl, nc);
    im6 = alloue_image_double(nl, nc);
    im7 = alloue_image_double(nl, nc);

    fft(im0, im1, im2, im3, nl, nc);
    fftshift(im2, im3, im2_shift, im3_shift, nl, nc);

    for (int i = 0; i < nl; ++i)
        for (int j = 0; j < nc; ++j) {
            im4[i][j] = im2_shift[i][j] * FTGauss2D(sigma, (i-nl/2.0)/nl, (j-nc/2.0)/nc);
            im5[i][j] = im3_shift[i][j] * FTGauss2D(sigma, (i-nl/2.0)/nl, (j-nc/2.0)/nc);
        }

    fftshift(im4, im5, im4_shift, im5_shift, nl, nc);
    ifft(im4_shift, im5_shift, im6, im7, nl, nc);

    return imdouble2uchar(im6, nl, nc);
}

int main (int ac, char **av) 
{  
    // av[1] contient le nom de l'image, av[2] le nom du resultat
    int nl, nc;
    unsigned char **in = NULL, **out = NULL;
  
    if (ac < 3) {
        printf("Usage : %s entree sortie \n",av[0]); 
        exit(1); 
    }

	// Lecture d'une image pgm dont le nom est passe sur la ligne de commande
    in = lectureimagepgm(av[1], &nl, &nc);
    if (in == NULL)  { 
        puts("Lecture image impossible"); 
        exit(1); 
    }

    printf("PSNR de %s : \n", av[1]);

    out = filter(in, nl, nc, 0.5);
    ecritureimagepgm(strcat(av[2],"s=0.5"),
                     crop(out, 0, 0, nl, nc),
                     nl, nc);
    printf("%f\n", PSNR(in, out, nl, nc));

    out = filter(in, nl, nc, 1);
    ecritureimagepgm(strcat(av[2],"s=1"),
                     crop(out, 0, 0, nl, nc),
                     nl, nc);
    printf("%f\n", PSNR(in, out, nl, nc));

    out = filter(in, nl, nc, 5);
    ecritureimagepgm(strcat(av[2],"s=5"),
                     crop(out, 0, 0, nl, nc),
                     nl, nc);
    printf("%f\n", PSNR(in, out, nl, nc));

    out = filter(in, nl, nc, 10);
    ecritureimagepgm(strcat(av[2],"s=10"),
                     crop(out, 0, 0, nl, nc),
                     nl, nc);
    printf("%f\n", PSNR(in, out, nl, nc));

    
    
}


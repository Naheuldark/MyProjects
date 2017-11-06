#include "pgm.h"
#include <math.h>
#include <time.h>

double FTGauss2D(double sigma, double u, double v) {
    return exp(-2*pow(M_PI*sigma,2)*(pow(u,2)+pow(v,2)));
}


double eqm(unsigned char **im1, unsigned char **im2,  int nl, int nc) 
{ 
    int i,j;
    double x;

    for (x=i=0; i<nl; i++) 
        for (j=0; j<nc; j++) 
            x+=((int)im1[i][j]-im2[i][j])*((int)im1[i][j]-im2[i][j]);
    return x / (nl*nc);
}

double psnr(unsigned char **im1, unsigned char **im2,  int nl, int nc) 
{ 
    double x;
    if ( (x=eqm(im1,im2,nl,nc)) == 0 ) 
        return INFINITY;
    return ( 10. * log10(255*255/x)) ;
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

double Gauss1D(double sigma, double i) {
    return exp(-i*i/(2*sigma*sigma));
}


//Calcul du masque gaussien
double* masque_gaussien(int n, double sigma, int W) {
	double* R = calloc(2*W+1, sizeof(double));
	double denom = 0;
	for (int i = -n ; i <= n ; ++i) {
		denom += Gauss1D(sigma, i); 
	}
	for (int k = -W ; k <= W ; ++k) {
		R[k+W] = Gauss1D(sigma, k)/denom;
	}
	return R;
}

double** convolution1DX(double** I, int nl, int nc, int W, double* filtre_x) {
	double **R = alloue_image_double(nl,nc);
	for (int x = 0; x < nl; ++x) {
		for (int y = 0; y < nc; ++y) {
			R[x][y] = 0;
			for (int i = -W; i <= W ; i++) {
				R[x][y] += I[(x+i+nl)%nl][y] * filtre_x[i+W];
			}
		}		
	}
	return R;
}

double** convolution1DY(double** I, int nl, int nc, int W, double* filtre_y) {
	double **R = alloue_image_double(nl,nc);
	for (int x = 0; x < nl; ++x) {
		for (int y = 0; y < nc; ++y) {
			R[x][y] = 0;
			for (int j = -W; j <= W ; j++)
				R[x][y] += I[x][(y+j+nc)%nc] * filtre_y[j+W];
		}	
	}
	return R;
}

int main (int ac, char **av) 
{
	int nl, nc;
    unsigned char **in = NULL, **out = NULL;
    double** i1; double **i2; double **i3;
  
    if (ac != 2) {
        printf("Usage : %s entree\n",av[0]); 
        exit(1); 
    }

	// Lecture d'une image pgm dont le nom est passe sur la ligne de commande
    in = lectureimagepgm(av[1], &nl, &nc);
    if (in == NULL)  { 
        puts("Lecture image impossible"); 
        exit(1); 
    }

    i1 = imuchar2double(in, nl, nc); 
    double* tab_sigma = calloc(4, sizeof(double));
    tab_sigma[0] = 0.5;
    tab_sigma[1] = 1.0;
    tab_sigma[2] = 5.0;
    tab_sigma[3] = 10.0;

   //############ QUESTION 1.2 ############### 

   //  for (int sigma = 0; sigma < 4 ; ++sigma) {
   //      unsigned char** fft =  filter(in, nl, nc, tab_sigma[sigma]);
   //  	for (int W = 0 ; W < 70 ; ++W) {
   //  		double* filtre_x = masque_gaussien(nl, tab_sigma[sigma], W);
			// double* filtre_y = masque_gaussien(nc, tab_sigma[sigma], W);
   //  		i2 = convolution1DX(i1, nl, nc, W, filtre_x);
   //  		i3 = convolution1DY(i2, nl, nc, W, filtre_y);
   //  		out = imdouble2uchar(i3, nl, nc);
   //  		printf("PSNR pour sigma = %f ; W = %d : %f\n", tab_sigma[sigma], W, psnr(fft, out, nl, nc));
   //  	}
   //  	printf("\n");
   //  }


    //############ QUESTION 1.3 ###############

    clock_t debut, fin;
    double cpu_time_used;
    // for (int sigma = 0; sigma < 4 ; ++sigma) {
    //     int W = (10 * tab_sigma[sigma] - 1)/2; //formule retenue en question 1.2, adaptée à W = (L-1)/2

    //     printf("Sigma = %f\n", tab_sigma[sigma]);
    //     printf("W = %d\n", W);

    //     //Calcul temps masque
    //     debut = clock();
    //     double* filtre_x = masque_gaussien(nl, tab_sigma[sigma], W);
    //     double* filtre_y = masque_gaussien(nc, tab_sigma[sigma], W);
    //     i2 = convolution1DX(i1, nl, nc, W, filtre_x);
    //     i3 = convolution1DY(i2, nl, nc, W, filtre_y);
    //     out = imdouble2uchar(i3, nl, nc);
    //     fin = clock();
    //     printf("Duree pour masque : W = %d, temps = %f s\n", W, ((double)fin-debut)/CLOCKS_PER_SEC);

    //     //Calcul temps fft
    //     debut = clock();
    //     unsigned char** fft =  filter(in, nl, nc, tab_sigma[sigma]);
    //     fin = clock();
    //     printf("Duree pour fft : %f s\n\n", ((double)fin-debut)/CLOCKS_PER_SEC);
    // }

    float temps_masque;
    float temps_fft; 
     double sigma = 1.0;
    while (1) {
        int W = (10 * sigma - 1)/2; //formule retenue en question 1.2, adaptée à W = (L-1)/2

        //Calcul temps masque
        debut = clock();
        double* filtre_x = masque_gaussien(nl, sigma, W);
        double* filtre_y = masque_gaussien(nc, sigma, W);
        i2 = convolution1DX(i1, nl, nc, W, filtre_x);
        i3 = convolution1DY(i2, nl, nc, W, filtre_y);
        out = imdouble2uchar(i3, nl, nc);
        fin = clock();
        temps_masque = ((double)fin-debut)/CLOCKS_PER_SEC;

        //Calcul temps fft
        debut = clock();
        unsigned char** fft =  filter(in, nl, nc, sigma);
        fin = clock();
        temps_fft = ((double)fin-debut)/CLOCKS_PER_SEC;

        if(temps_fft < temps_masque)
            break;

        sigma += 0.1;
    }
    printf ("Sigma critique = %f\n", sigma);




}

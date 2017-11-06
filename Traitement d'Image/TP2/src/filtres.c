#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>
#include "filtres.h"
#include "pgm.h"

double **filtremedian(double **in, int nl, int nc, int n){
	
	double **R = alloue_image_double(nl,nc);
	int med;
	int somme;
	for (int i = n ; i <= nl - n - 1; i++) {

		//Calcul de l'histogramme initial
		double H[256] = {0};
		for (int kx = -n ; kx <= n ; kx++) {
			for (int ky = -n ; ky <= n ; ky++) {
				H[(int)in[i+kx][n+ky]]++;
			}
		}

		//Médianne du premier point de la ligne
		med = 0;
		somme = 0;
		while (somme < 2*n*(n+1)) {
			somme += H[med++];
		}
		R[i][n] = med-1;

		//Calcul pour tous les i,j de la ligne
		for (int j = n ; j <= nc - n - 1; j++) {

			//Mise à jour de l'histogramme :

			//Suppression des anciennes valeurs
			for (int kx = -n ; kx <= n ; kx++) {
				H[(int)in[i+kx][j-n]]--;
			}
			//Ajout des nouvelles valeurs
			for (int kx = -n ; kx <= n ; kx++) {
				H[(int)in[i+kx][j+n]]++;
			}

			//Médianne au point i,j
			med = 0;
			somme = 0;
			while (somme < 2*n*(n+1)) {
				somme += H[med++];
			}
			R[i][j]=med-1;

		}


	}
	return R;
}

double wt_xy(double st_xplus1_y, double st_xmoins1_y, double st_x_yplus1, double st_x_ymoins1, double k) {
	return exp(-(((st_xplus1_y-st_xmoins1_y)*(st_xplus1_y-st_xmoins1_y) + (st_x_yplus1-st_x_ymoins1)*(st_x_yplus1-st_x_ymoins1))/(2*k*k)));
}

double **filtreadaptatif(double **in, int nl, int nc, double k) {

	int which = 1; //boolean
	double **R1 = in;
	double **R2 = in;

	//main loop
	for (int iter = 0; iter < 100; iter++) {
		for (int x = 0; x<nl; x++) {
			for (int y = 0; y<nc; y++) {
				double num = 0;
				double denom = 0;
				double w = 0;
				for (int i = -1; i<=1; i++) {
					for (int j = -1; j<=1; j++) {
						if (which) {
							w = wt_xy(R1[(x+1+i+nl)%nl][(y+j+nc)%nc], R1[(x-1+i+nl)%nl][(y+j+nc)%nc], R1[(x+i+nl)%nl][(y+1+j+nc)%nc], R1[(x+i+nl)%nl][(y-1+j+nc)%nc], k);
							num += w*R1[(x+i+nl)%nl][(y+j+nc)%nc];
							denom += w;
						} else {
							w = wt_xy(R2[(x+1+i+nl)%nl][(y+j+nc)%nc], R2[(x-1+i+nl)%nl][(y+j+nc)%nc], R2[(x+i+nl)%nl][(y+1+j+nc)%nc], R2[(x+i+nl)%nl][(y-1+j+nc)%nc], k);
							num += w*R2[(x+i+nl)%nl][(y+j+nc)%nc];
							denom += w;
						}
					}
				}
				if (which) 
					R2[x][y] = num/denom;
				else 
					R1[x][y] = num/denom;
				which = 1-which;

			}
		}
	}

	if (which)
		return R1;
	else 
		return R2;

}

double ** filtrebilateral(double **in, int nl, int nc, double sigma1, double sigma2) {

	double **R = alloue_image_double(nl, nc);

	for (int x = 0; x<nl; x++) {
		for (int y = 0; y<nc; y++) {

			double num = 0;
			double denom = 0;

			for (int i = - 3*(int)sigma1; i <= 3*(int)sigma1; i++) {
				for (int j = -3 * (int)sigma1; j <= 3*(int)sigma1; j++) {
					double id = i;
					double jd = j;

					double facteur_exp = exp(-(id*id + jd*jd)/(2.0*sigma1*sigma1)) * exp(-((in[(x+i+nl)%nl][(y+j+nc)%nc] - in[x][y])*(in[(x+i+nl)%nl][(y+j+nc)%nc] - in[x][y]))/(2.0*sigma2*sigma2));
					num += facteur_exp * in[(x+i+nl)%nl][(y+j+nc)%nc];
					denom += facteur_exp;
				}
			}


			R[x][y] = num/denom;
		}
	}

	return R;
}

double **filtreMNL(double **in, int nl, int nc, int t, int r, double sigma) {
	double **R = alloue_image_double(nl, nc);
	double wpq;
	double num;
	double denom;
	double dist_pq;

	//Image
	for (int x = 0; x<nl; x++) {
		for (int y = 0; y<nc; y++) {
			num = 0;
			denom = 0;

			//Région
			for (int xr = x-t; xr < x+t; xr++) {
				for (int yr = y-t; yr < y+t; yr++) {
					dist_pq = 0;

					//Patch
					for (int i = -r; i < r; i++) {
						for (int j = -r; j < r; j++) {

							dist_pq += in[(xr+i+nl)%nl][(yr+j+nc)%nc]*in[(xr+i+nl)%nl][(yr+j+nc)%nc];
							dist_pq -= in[(x+i+nl)%nl][(y+j+nc)%nc]*in[(x+i+nl)%nl][(y+j+nc)%nc];

						}
					}

					wpq = exp(-dist_pq/(2*sigma*sigma*(2*t+1)*(2*t+1)));
					num += wpq * in[(xr+nl)%nl][(yr+nc)%nc];
					denom += wpq;

				}
			}

			R[x][y] = num/denom;
			
		}
	}
	return R;
}
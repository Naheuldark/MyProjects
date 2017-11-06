#include "pgm.h"
#include <math.h>

double** transpose(double** M1) {
	int tmp;
	double **M2 = M1;
	for (int i = 0; i < 3; i++)
     	for (int j = 0; j < i; j++) {
          tmp = M2[i][j];
          M2[i][j] = M2[j][i];
          M2[j][i] = tmp;
        }
    return M2;
}

double** computeGradx(unsigned char** in, int nl, int nc, double** M1) {
	double** Gx = alloue_image_double(nl,nc);
	double** in_double = imuchar2double(in,nl,nc);

	for (int i = 0; i < nl; ++i) {
		for (int j = 0; j < nc; ++j) {
			Gx[i][j] = M1[0][0]*in_double[(i-1+nl)%nl][(j-1+nc)%nc] + 
					   M1[0][1]*in_double[(i-1+nl)%nl][j] +
					   M1[0][2]*in_double[(i-1+nl)%nl][(j+1+nc)%nc] +
					   M1[1][0]*in_double[i][(j-1+nc)%nc] +
					   M1[1][1]*in_double[i][j] +
					   M1[1][2]*in_double[i][(j+1+nc)%nc] +
					   M1[2][0]*in_double[(i+1+nl)%nl][(j-1+nc)%nc] +
					   M1[2][1]*in_double[(i+1+nl)%nl][j] +
					   M1[2][2]*in_double[(i+1+nl)%nl][(j+1+nc)%nc];
		}
	}
	return Gx;
}

double** computeGrady(unsigned char** in, int nl, int nc, double** M1) {
	double** Gy = alloue_image_double(nl,nc);
	double** M2 = alloue_image_double(3,3);
	double** in_double = imuchar2double(in, nl, nc);
	M2 = transpose(M1);

	for (int i = 0; i < nl; ++i) {
		for (int j = 0; j < nc; ++j) {
			Gy[i][j] = M2[0][0]*in_double[(i-1+nl)%nl][(j-1+nc)%nc] + 
					   M2[0][1]*in_double[(i-1+nl)%nl][j] +
					   M2[0][2]*in_double[(i-1+nl)%nl][(j+1+nc)%nc] +
					   M2[1][0]*in_double[i][(j-1+nc)%nc] +
					   M2[1][1]*in_double[i][j] +
					   M2[1][2]*in_double[i][(j+1+nc)%nc] +
					   M2[2][0]*in_double[(i+1+nl)%nl][(j-1+nc)%nc] +
					   M2[2][1]*in_double[(i+1+nl)%nl][j] +
					   M2[2][2]*in_double[(i+1+nl)%nl][(j+1+nc)%nc];
		}
	}
	return Gy;
}

double** computeModG(unsigned char** in, int nl, int nc, double** M1) {
	double** modG = alloue_image_double(nl, nc);
	double** Gx = computeGradx(in, nl, nc, M1);
	double** Gy = computeGrady(in, nl, nc, M1);
	for (int i = 0; i < nl; ++i) {
		for (int j = 0; j < nc; ++j) {
			modG[i][j] = sqrt(pow(Gx[i][j],2)+pow(Gy[i][j],2));
		}
	}
	return modG;
}

int main (int ac, char **av) 
{
	int nl, nc;
    unsigned char **in = NULL, **out = NULL;
  
    if (ac < 3) {
        printf("Usage : %s entree sortie \n",av[0]); 
        exit(1); 
    }

	in = lectureimagepgm(av[1], &nl, &nc);
    if (in == NULL)  { 
        puts("Lecture image impossible"); 
        exit(1); 
    }

    double** M1 = alloue_image_double(3,3);
    
    // PREWITT GRADIENT
    M1[0][0] = -1;
    M1[0][1] = 0;
    M1[0][2] = 1;
    M1[1][0] = -1;
    M1[1][1] = 0;
    M1[1][2] = 1;
    M1[2][0] = -1;
    M1[2][1] = 0;
    M1[2][2] = 1;

    // SOBEL GRADIENT
    // M1[0][0] = -1;
    // M1[0][1] = 0;
    // M1[0][2] = 1;
    // M1[1][0] = -2;
    // M1[1][1] = 0;
    // M1[1][2] = 2;
    // M1[2][0] = -1;
    // M1[2][1] = 0;
    // M1[2][2] = 1;

    double** modGrad = computeModG(in, nl, nc, M1);

    double seuil = 0;

    for (int i = 0; i < nl; ++i) {
    	for (int j = 0; j < nc; ++j) {
    		if (modGrad[i][j] > seuil-1000)
    			seuil = modGrad[i][j];
    		else
    			modGrad[i][j] = 0;
    	}
    }

    out = imdouble2uchar(modGrad, nl, nc);
    ecritureimagepgm(av[2],out,nl,nc);
}

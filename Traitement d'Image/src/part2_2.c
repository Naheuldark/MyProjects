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

double** computeLapx(unsigned char** in, int nl, int nc, double** M1) {
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

double** computeLapy(unsigned char** in, int nl, int nc, double** M1) {
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

double** computeLOG(unsigned char** in, int nl, int nc, double** M1) {
	double** LOG = alloue_image_double(nl, nc);
	double** Lx = computeLapx(in, nl, nc, M1);
	double** Ly = computeLapy(in, nl, nc, M1);
	for (int i = 0; i < nl; ++i) {
		for (int j = 0; j < nc; ++j) {
			LOG[i][j] = sqrt(pow(Lx[i][j],2)+pow(Ly[i][j],2));
		}
	}
	return LOG;
}



double FTGauss2D(double sigma, double u, double v) {
    return exp(-2*pow(M_PI*sigma,2)*(pow(u,2)+pow(v,2)));
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


unsigned char** computeDOG(unsigned char** in, int nl, int nc) {
    double** DOG = alloue_image_double(nl, nc);
	double** H1 = imuchar2double(filter(in, nl, nc, 3.2),nl,nc);
	double** H2 = imuchar2double(filter(in, nl, nc, 2),nl,nc);

	for (int i = 0; i < nl; ++i) {
		for (int j = 0; j < nc; ++j) {
			DOG[i][j] = (int)(H1[i][j] - H2[i][j] + 256)%256;
			fprintf(stderr, "%d\n", (int)(H1[i][j] - H2[i][j] + 256)%256);
		}
	}

	return imdouble2uchar(DOG,nl,nc);
}



int main (int ac, char **av) 
{
	int nl, nc;
    unsigned char **in = NULL, **filtered_in = NULL, **out = NULL;
  
    if (ac < 3) {
        printf("Usage : %s entree sortie \n",av[0]); 
        exit(1); 
    }

	in = lectureimagepgm(av[1], &nl, &nc);
    if (in == NULL)  { 
        puts("Lecture image impossible"); 
        exit(1); 
    }

    /*
     * LAPLACIAN OF GAUSSIAN
     */

    double** M1 = alloue_image_double(3,3);
    
    // LAPLACIAN 1
    M1[0][0] = 0;
    M1[0][1] = 1;
    M1[0][2] = 0;
    M1[1][0] = 1;
    M1[1][1] = -4;
    M1[1][2] = 1;
    M1[2][0] = 0;
    M1[2][1] = 1;
    M1[2][2] = 0;

    // LAPLACIAN 2
    M1[0][0] = 1;
    M1[0][1] = 1;
    M1[0][2] = 1;
    M1[1][0] = 1;
    M1[1][1] = -8;
    M1[1][2] = 1;
    M1[2][0] = 1;
    M1[2][1] = 1;
    M1[2][2] = 1;

    // LAPLACIAN 3
    M1[0][0] = 1;
    M1[0][1] = 2;
    M1[0][2] = 1;
    M1[1][0] = 2;
    M1[1][1] = -4;
    M1[1][2] = 2;
    M1[2][0] = 1;
    M1[2][1] = 2;
    M1[2][2] = 1;
	
	filtered_in = filter(in, nl, nc, 0.5);
    char* tmp_name = av[2];
    tmp_name = strcat(tmp_name, "_TMP");

    ecritureimagepgm(tmp_name,
                     crop(filtered_in, 0, 0, nl, nc),
                     nl, nc);
	
	in = lectureimagepgm(tmp_name, &nl, &nc);
    double** LOG = computeLOG(in, nl, nc, M1);

    double seuil = 0;

    for (int i = 0; i < nl; ++i) {
    	for (int j = 0; j < nc; ++j) {
    		if (LOG[i][j] > seuil-1000)
    			seuil = LOG[i][j];
    		else
    			LOG[i][j] = 0;
    	}
    }

    ecritureimagepgm(av[2],
                     crop(imdouble2uchar(LOG,nl,nc), 0, 0, nl, nc),
                     nl, nc);


  	/*
  	 * DIFFERENCE OF GAUSSIAN
  	 */

  	out = computeDOG(in,nl,nc);

  	ecritureimagepgm(av[2],
  	    			 crop(out,0,0,nl,nc),
  	 				 nl,nc);
}

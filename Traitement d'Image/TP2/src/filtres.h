#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

double **filtremedian(double **in, int nl, int nc, int W);
double **filtreadaptatif(double **in, int nl, int nc, double k);
double **filtrebilateral(double **in, int nl, int nc, double sigma1, double sigma2);
double **filtreMNL(double **in, int nl, int nc, int t, int r, double sigma);


// fonctions auxilliaires
double wt_xy(double st_xplus1_y, double st_xmoins1_y, double st_x_yplus1, double st_x_ymoins1, double k);
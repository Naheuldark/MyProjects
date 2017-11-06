#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <complex>
#include "fft.h"

GenericVector< std::complex<double> > fft(GenericVector< std::complex <double> > x) {
    int n = x.size();
    if (n <= 1)
        return x;
    GenericVector< std::complex<double> > even(n/2);
    GenericVector< std::complex<double> > odd(n/2);
    for (int k = 0; k < n; k++) {
        if (k%2 == 0)
            even(k/2) = x(k);
        else 
            odd(k/2) = x(k); 
    }

    even = fft(even);
    odd = fft(odd);

    std::complex<double> t;
    for (int k = 0; k < n/2; k++) {
        t = odd(k) * exp(-std::complex<double>(0,1)*-std::complex<double>(2,0)*-std::complex<double>(M_PI,0)*std::complex<double>(k,0)/std::complex<double>(n,0));
        x(k) = even(k) + t;
        x(k+n/2) = even(k) - t;
    }
    return x;
}

GenericVector< std::complex<double> > ifft(GenericVector< std::complex <double> > x) {
    int n = x.size();
    if (n <= 1)
        return x;
    for (int k = 0; k < n; k++) {
        x(k) = conj(x(k));
    }
    x = fft(x);
    for (int k = 0; k < n; k++) {
        x(k) = conj(x(k))/std::complex<double>(n,0);
    }
    return x;
}

GenericVector< std::complex<double> > fft_vector (GenericVector< std::complex<double> > v) {
    int n = sqrt(v.size());
    GenericVector< std::complex<double> > retour(n*n);
    GenericVector< std::complex<double> > v_comp(n);

    //1eres ffts 1d sur les lignes
    for (int k = 0; k < n; k++) {
        for (int l = 0; l < n; l++) {
            v_comp(l) = v(n*k+l);
        }
        v_comp = fft(v_comp);
        for (int l = 0; l < n; l++) {
            retour(n*k+l) = v_comp(l);
        }
    }

    //2emes ffts 1d sur les colonnes
    for (int l = 0; l < n; l++) {
        for (int k = 0; k < n; k++) {
            v_comp(k) = retour(n*k+l);
        }
        v_comp = fft(v_comp);
        for (int k = 0; k < n; k++) {
            retour(n*k+l) = v_comp(k);
        }
    }

    return retour;
}

GenericVector< std::complex<double> > ifft_vector (GenericVector< std::complex<double> > v) {
    int n = sqrt(v.size());
    GenericVector< std::complex<double> > retour(n*n);
    GenericVector< std::complex<double> > v_comp(n);

    //1eres ffts 1d sur les lignes
    for (int k = 0; k < n; k++) {
        for (int l = 0; l < n; l++) {
            v_comp(l) = v(n*k+l);

        }
        v_comp = ifft(v_comp);
        for (int l = 0; l < n; l++) {
            retour(n*k+l) = v_comp(l);
        }
    }

    //2emes ffts 1d sur les colonnes
    for (int l = 0; l < n; l++) {
        for (int k = 0; k < n; k++) {
            v_comp(k) = retour(n*k+l);
        }
        v_comp = ifft(v_comp);
        for (int k = 0; k < n; k++) {
            retour(n*k+l) = v_comp(k);
        }
    }

    return retour;
}


Dvector ifft_vector_double (GenericVector< std::complex<double> >  v) {
    int n = sqrt(v.size());
    Dvector retour(n*n);
    GenericVector< std::complex<double> > temp(n*n);
    GenericVector< std::complex<double> > v_comp(n);

    //1eres ffts 1d sur les lignes
    for (int k = 0; k < n; k++) {
        for (int l = 0; l < n; l++) {
            v_comp(l) = v(n*k+l);
        }
        v_comp = ifft(v_comp);
        for (int l = 0; l < n; l++) {
            temp(n*k+l) = v_comp(l);
        }
    }

    //2emes ffts 1d sur les colonnes
    for (int l = 0; l < n; l++) {
        for (int k = 0; k < n; k++) {
            v_comp(k) = temp(n*k+l);
        }
        v_comp = ifft(v_comp);
        for (int k = 0; k < n; k++) {
            retour(n*((k+n/2)%n)+(l+n/2)%n) = real(v_comp(k)); //avec le fft shift

        }
    }

    return retour;

}
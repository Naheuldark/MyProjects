#ifndef FFT_HPP
#define FFT_HPP

#include <iostream>
#include <assert.h>
#include "Dvector.h"
#include "GenericVector.h"

GenericVector< std::complex<double> > fft(GenericVector< std::complex <double> > x);
GenericVector< std::complex<double> > ifft(GenericVector< std::complex <double> > x);
GenericVector< std::complex<double> > fft_vector (GenericVector< std::complex <double> > v);
GenericVector< std::complex <double> > ifft_vector (GenericVector< std::complex <double> > v);
Dvector ifft_vector_double (GenericVector< std::complex <double> >  v);

#endif
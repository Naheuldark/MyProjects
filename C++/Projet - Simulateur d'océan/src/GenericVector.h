#ifndef GENERICVECTOR_HPP
#define GENERICVECTOR_HPP

#include <assert.h>
#include <iostream>
#include <istream>
#include <ostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstring>
#include <complex>

template <typename T> class GenericVector
{
    public:
        ~GenericVector() {
            delete [] val;
        }


        GenericVector() {
            val = NULL;
            taille = 0;
        }

        GenericVector(int n) {
            val = new T[n];
            taille = n;
        }

        GenericVector(int n, T init){
            val = new T[n];
            taille = n;
            for (int i = 0; i < n; ++i)
            {
                val[i] = init;
            }
        }


        GenericVector(GenericVector<T> const& vec) {
            taille = vec.size();
            if (taille == 0) return;
            val = new T[taille];
            for (int i = 0; i < taille; ++i)
            {
                val[i] = vec(i);
            }
        }

        T* getVal() const {
            return val;
        }

        void display(std::ostream& str) {
            for (int i = 0; i < taille; i++)
                {
                    str << std::setprecision(2) << val[i] << '\n';
                }
        }

        int size() const {
            return taille;
        }

        T& operator () (int i) const {
            assert(i >= 0);
            assert(i < taille);
            return val[i];
        }

        T& operator () (int i) {
            assert(i >= 0);
            assert(i < taille);
            return val[i];
        }


        GenericVector<T>& operator += (const GenericVector<T> &Q) {
            assert(taille == Q.size());
            GenericVector<T> &P = *this;
            for (int i = 0; i < taille; ++i)
                P(i) += Q(i);
            return P;
        }

        GenericVector<T>& operator -= (const GenericVector<T> &Q) {
            assert(taille == Q.size());
            GenericVector<T> &P = *this;
            for (int i = 0; i < taille; ++i)
                P(i) -= Q(i);
            return P;
        }

        GenericVector<T>& operator *= (const GenericVector<T> &Q) {
            assert(taille == Q.size());
            GenericVector<T> &P = *this;
            for (int i = 0; i < taille; ++i)
                P(i) *= Q(i);
            return P;
        }

        GenericVector<T>& operator /= (const GenericVector<T> &Q) {
            assert(taille == Q.size());
            GenericVector<T> &P = *this;
            for (int i = 0; i < taille; ++i) {
                assert(Q(i)!=0);
                P(i) /= Q(i);
            }
            return P;
        }

        GenericVector<T>& operator += (const T &k) {
            GenericVector<T> &P = *this;
            for (int i = 0; i < taille; ++i)
                P(i) += k;
            return P;
        }
        GenericVector<T>& operator -= (const T &k) {
            GenericVector<T> &P = *this;
            for (int i = 0; i < taille; ++i)
                P(i) -= k;
            return P;
        }
        GenericVector<T>& operator *= (const T &k) {
            GenericVector<T> &P = *this;
            for (int i = 0; i < taille; ++i)
                P(i) *= k;
            return P;
        }
        GenericVector<T>& operator /= (const T &k) {
            assert(k!=0);
            GenericVector<T> &P = *this;
            for (int i = 0; i < taille; ++i)
                P(i) /= k;
            return P;
        }
        bool operator == (const GenericVector<T> &Q) {
            if (taille != Q.size()) {
                return false;
            } else {
                for (int i = 0; i < taille; ++i)
                    if (val[i] != Q(i))
                        return false;
            }
            return true;
        }

        bool operator != (const GenericVector<T> &Q) {
            return !(*this == Q);
        }

        GenericVector<T>& operator = (const GenericVector<T> &P) {
            if (taille != 0)
                delete [] val;
            taille = P.size();
            val = new T[taille];
            std::memcpy(val, P.getVal(), taille * sizeof(T));
            return *this;
        }

        void resize(int newSize, T* newVal) {
            if (newSize <= taille)
                return;

            assert(sizeof(newVal)/sizeof(T) == newSize - taille);

            double* v = new T[newSize];
            std::memcpy(v, val, taille * sizeof(T));
            delete [] val;
            for (int i = taille; i < newSize; ++i)
                v[i] = newVal[i-taille];
            val = v;
            taille = newSize;
        }



    private:
		T* val;
		int taille;	


};

template <typename T>
GenericVector<T> operator + (const GenericVector<T> &P, const T &k) {
    GenericVector<T> R(P);
    for (int i = 0; i < P.size(); ++i) 
        R(i) += k;
    return R;
}

template <typename T>
GenericVector<T> operator - (const GenericVector<T> &P, const T &k) {
    GenericVector<T> R(P);
    for (int i = 0; i < P.size(); ++i) 
        R(i) -= k;
    return R;
}
template <typename T>
GenericVector<T> operator * (const GenericVector<T> &P, const T &k) {
    GenericVector<T> R(P);
    for (int i = 0; i < P.size(); ++i) 
        R(i) *= k;
    return R;
}

template <typename T>
GenericVector<T> operator / (const GenericVector<T> &P, const T &k) {
    GenericVector<T> R(P);
    asser(k!=0);
    for (int i = 0; i < P.size(); ++i) 
        R(i) /= k;
    return R;
}

template <typename T>
GenericVector<T> operator + (const GenericVector<T> &P, const GenericVector<T> &Q) {
    GenericVector<T> R(P);
        R += Q;
        return R;
}

template <typename T>
GenericVector<T> operator - (const GenericVector<T> &P, const GenericVector<T> &Q) {
    GenericVector<T> R(P);
    R -= Q;
    return R;
}

template <typename T>
GenericVector<T> operator - (const GenericVector<T> &P) {
    GenericVector<T> R(P);
    for (int i = 0; i < P.size(); ++i) 
        R(i) *= (-1.0);
    return R;
}

template <typename T>
std::ostream& operator << (std::ostream &s, const GenericVector<T> &P) {
    s << "Dvector : ";
    for (int i = 0; i < P.size(); ++i)
        s << P(i) << " ";
    s << std::endl;
    return s;
}

template <typename T>
std::istream& operator >> (std::istream &s, const GenericVector<T> &P) {
    for (int i = 0; i < P.size(); ++i)
        s >> P(i);
    return s;
}




#endif

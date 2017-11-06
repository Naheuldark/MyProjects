function [ K ] = courbure( k, t, matrice_pi, matrice_mi )

    b0 = [matrice_pi(1,k),matrice_pi(2,k)];
    b1 = b0 + 1/3 .* [matrice_mi(1,k),matrice_mi(2,k)];
    b3 = [matrice_pi(1,k+1),matrice_pi(2,k+1)];
    b2 = b0 - 1/3 .* [matrice_mi(1,k+1),matrice_mi(2,k+1)];
    
    Pprime = -3.*b0.*(1-t).^2 + 3.*b1.*(1-t).*(1-3*t) + 3.*b2.*t.*(2-3*t) + 3.*b3.*t.^2;
    Psec = 6.*b0.*(1-t) + 3.*b1.*(6*t-4) + 3.*b2.*(2-6*t) + 6.*b3.*t;
    
    M = [Pprime' Psec'];
    K = det(M) / norm(Pprime);
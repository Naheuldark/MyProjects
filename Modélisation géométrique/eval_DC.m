function [Bezier_curve_points]= eval_DC(matrice,resolution)
    n = size(matrice,2);
    temps = 1:resolution;
    copy = matrice;
    for tps = temps
        copy = matrice;
        t = tps./resolution;
        for k = 1:n-1
            for i = 1:n-k
                copy(1,i) = (1-t).*copy(1,i) + t.*copy(1,i+1);
                copy(2,i) = (1-t).*copy(2,i) + t.*copy(2,i+1);
            end
        end
        Bezier_curve_points(1,tps) = copy(1,1);
        Bezier_curve_points(2,tps) = copy(2,1);
    end
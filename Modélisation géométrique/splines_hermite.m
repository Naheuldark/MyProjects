
function [] = splines_hermite()

resolution = 50;       % precision de chaque morceau de courbe de Bezier
K = 0;                 % variable d'etat
L = 0;
c=0;                   % paramètre des tension
matrice_pi = 0;        % ensemble des points p_i
matrice_mi = 0;        % ensemble des tangeantes m_i version cardinal splines
matrice_pol = 0;       % ensemble des points de controle de tous les polygones reunis
                       % chaque polygone est forme des indices entre 3k-2 et
                       % 3k+1, pour k dans [1,n-1]
matrice_mic = 0;       % matrice tridimensionelle des tangeantes m_i quand c varie
matrice_c = 0:0.2:1    % 6 valeurs de c entre 0 et 1

while K~=3 % arreter
   K = menu('Que voulez-vous faire ?',...
            'Test avec affichage polygone + courbure',...
            'Dessin',...
            'ARRETER');
   
   if K == 1 % TEST
      matrice_pi = 0; 
      matrice_mi = 0;
      matrice_pol = 0;
      figure
      clf                  % affichage d'une fenetre vide
      hold on              % tous les plot seront executes sur cette meme fenetre
      axis([0 10 0 10])    % les axes sont definitivement fixes
      %axis off
      matrice_pi=0;
      for i = 1:1000         % on limite le nombre de points a 1000
          [X,Y] = ginput(1);  % prise en compte d'un clic de souris
          if isempty(X)       % si on appuie sur <ENTER>
             break
          end 
          matrice_pi(1,i) = X;
          matrice_pi(2,i) = Y;
          plot(matrice_pi(1,i),matrice_pi(2,i),'o') % affichage du point p_i
      end
      
      % Calcul des tangentes cardinal splines
      matrice_mi(1,1) = 0;
      matrice_mi(2,1) = 0;
      % on calcule d'abord mi de Catmull-Rom
      for j = 2:size(matrice_pi, 2) - 1
          matrice_mi(1,j) = matrice_pi(1,j+1) - matrice_pi(1,j);
          matrice_mi(2,j) = matrice_pi(2,j+1) - matrice_pi(2,j);
      end
      
      % On entre la première tangente à la souris
      [X,Y] = ginput(1);
      matrice_mi (1,1) = X - matrice_pi(1,1);
      matrice_mi (2,1) = Y - matrice_pi(2,1);  
      
      % On entre la dernière tangente à la souris
      [X,Y] = ginput(1);
      m = size(matrice_mi, 2);
      matrice_mi(1,m+1) = X - matrice_pi(1,m+1);
      matrice_mi(2,m+1) = Y - matrice_pi(2,m+1);
      
      %Choix du paramètre de tension
      prompt = {'c :'};
      dlg_title = 'Paramètre de tension'; 
      answer = inputdlg(prompt,dlg_title);
      c=str2num(answer{:});
    
      %on multiplie par 1-c
      matrice_mi = (1-c)*matrice_mi;
     
      % creation polygones de controle :
      for  j = 1:size(matrice_pi,2) - 1          
          matrice_pol(1,3*j-2) = matrice_pi(1,j);
          matrice_pol(2,3*j-2) = matrice_pi(2,j);
          
          matrice_pol(1,3*j-1) = matrice_pi(1,j) + matrice_mi(1,j)./3;
          matrice_pol(2,3*j-1) = matrice_pi(2,j) + matrice_mi(2,j)./3;
          
          matrice_pol(1,3*j) = matrice_pi(1,j+1) - matrice_mi(1,j+1)./3;
          matrice_pol(2,3*j) = matrice_pi(2,j+1) - matrice_mi(2,j+1)./3;
      end

      %ajout dernier point
      matrice_pol(1,3*size(matrice_pi,2)-2) = matrice_pi(1,size(matrice_pi,2));
      matrice_pol(2,3*size(matrice_pi,2)-2) = matrice_pi(2,size(matrice_pi,2));
      
      %Affichage du polygone de controle
      plot(matrice_pol(1,:),matrice_pol(2,:),'b')
      
      %Calcul de la courbe polygone par polygone
      for j = 1:size(matrice_pi,2) - 1 
          Bezier_curve_points = eval_DC(matrice_pol(:,3*j-2:3*j+1),resolution);
          plot(Bezier_curve_points(1,:),Bezier_curve_points(2,:),'r'); % affichage courbe    
      end
      
      figure
      clf                  
      hold on              
      for k = 1:size(matrice_pi,2)-1
          i = 1;
          for t = 1:resolution
              K(i) = courbure(k,t/resolution,matrice_pi,matrice_mi);
              i = i+1;
          end
          plot((k-1)*resolution+1:k*resolution, K,'b')
      end
   end
   
if K == 2 % DESSIN
      c=0.5;
      clf                  % affichage d'une fenetre vide
      hold on              % tous les plot seront executes sur cette meme fenetre     
      while L ~= 2 
          L = menu('Soyez créatifs !', ...
               'Ajouter courbe',...
               'ARRETER');  
        if L == 1
        matrice_pi = 0; 
        matrice_mi = 0;
        matrice_pol = 0;
        
        %Choix de la couleur
        prompt = {'Couleur :'};
        dlg_title = 'Choix de la couleur'; 
        %b blue g green r red c cyan m magenta y yellow k black
        answer = inputdlg(prompt,dlg_title);
        couleur = answer{:};
        
        axis([0 10 0 10])    % les axes sont definitivement fixes
        axis off
        matrice_pi=0;
        for i = 1:1000         % on limite le nombre de points a 1000
            [X,Y] = ginput(1);  % prise en compte d'un clic de souris
            if isempty(X)       % si on appuie sur <ENTER>
                break
            end 
            matrice_pi(1,i) = X;
            matrice_pi(2,i) = Y;
            plot(matrice_pi(1,i),matrice_pi(2,i),'.','MarkerEdgeColor',couleur) % affichage du point p_i
        end
        
        % on calcule d'abord mi de Catmull-Rom
        for j = 1:size(matrice_pi, 2) - 1
            matrice_mi(1,j) = matrice_pi(1,j+1) - matrice_pi(1,j);
            matrice_mi(2,j) = matrice_pi(2,j+1) - matrice_pi(2,j);
        end  

        % On calcule la dernière tangente à la souris
        m = size(matrice_mi, 2);
        matrice_mi(1,m+1) = matrice_pi(1,m) - matrice_pi(1,m+1);
        matrice_mi(2,m+1) = matrice_pi(2,m) - matrice_pi(2,m+1);
        
        %on multiplie par 1-c
        matrice_mi = (1-c)*matrice_mi;

        % creation polygones de controle :
        for  j = 1:size(matrice_pi,2) - 1          
            matrice_pol(1,3*j-2) = matrice_pi(1,j);
            matrice_pol(2,3*j-2) = matrice_pi(2,j);

            matrice_pol(1,3*j-1) = matrice_pi(1,j) + matrice_mi(1,j)./3;
            matrice_pol(2,3*j-1) = matrice_pi(2,j) + matrice_mi(2,j)./3;

            matrice_pol(1,3*j) = matrice_pi(1,j+1) - matrice_mi(1,j+1)./3;
            matrice_pol(2,3*j) = matrice_pi(2,j+1) - matrice_mi(2,j+1)./3;
        end

        %ajout dernier point
        matrice_pol(1,3*size(matrice_pi,2)-2) = matrice_pi(1,size(matrice_pi,2));
        matrice_pol(2,3*size(matrice_pi,2)-2) = matrice_pi(2,size(matrice_pi,2));

        %Calcul de la courbe polygone par polygone
        for j = 1:size(matrice_pi,2) - 1 
            Bezier_curve_points = eval_DC(matrice_pol(:,3*j-2:3*j+1),resolution);
            plot(Bezier_curve_points(1,:),Bezier_curve_points(2,:),couleur); % affichage courbe    
        end
      end
      end
   end
   
end
close
close

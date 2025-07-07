function [Theta] = normal_equation(FeaturesMatrix, Y, tol, iter)
  %obtinerea numarului de linii si coloane
  [n, m] = size(FeaturesMatrix);
  %initializarea vectorului Theta
  Theta = zeros(m + 1, 1);
  %calcularea matricei sistemului și vectorului termenilor liberi pornind de la
  %th = (FeaturesMatrix' * FeaturesMatrix)^(-1)*FeaturesMatrix' * Y;
  A = FeaturesMatrix' * FeaturesMatrix;
  b = FeaturesMatrix' * Y;
  %verificare daca matricea A este pozitiv definită
  [A_lin, ~] = size(A);
  verif_poz_def = 1;
  for i = 1:A_lin
    if det(A(1:i, 1:i)) <= 0
      verif_poz_def = 0;
      break;
    endif
  endfor
  %iesirea din functie daca nu e pozitiv definita
  if verif_poz_def == 0
    return;
  endif
  %initializarea vectorului x0
  x0 = zeros(m, 1);
  %determinarea rezidualului initial
  r = b - A * x0;
  %initializarea primului vector
  v = r;
  %determinarea valorii patratice a tolerantei
  tol_squared = tol^2;
  %pasii pentru algoritmul gradientului conjugat
  Theta = x0;
  k = 1;
  while (k <= iter) && (r' * r > tol_squared)
    %calcularea lui tk
    tk = (r' * r) / (v' * A * v);
    %actualizarea solutiei
    Theta = Theta + tk * v;
    %actualizarea rezidualului
    rk = r - tk * A * v;
    %calcularea lui sk
    sk = (rk' * rk) / (r' * r);
    %actualizarea vectorului conjugat
    v = rk + sk * v;
    %actualizarea pentru rezidualului
    r = rk;
    %incrementarea contorului
    k = k + 1;
  endwhile
  %actualizarea lui Theta cu solutia finala
  aux = Theta(1:m);
  Theta = zeros(m + 1, 1);
  Theta(2:m + 1) = aux;
endfunction

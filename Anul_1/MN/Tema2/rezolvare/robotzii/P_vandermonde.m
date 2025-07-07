function y_interp = P_vandermonde (coef, x_interp)
  %determinarea numarului de coeficienti
  len_coef = length(coef);
  %determinarea numarului de puncte
  n = length(x_interp);
  %initializarea vectorului y_interp
  y_interp = zeros(n, 1);
  %adaugarea coeficientilor liberi in y
  y_interp(:) = coef(1);
  for i = 1:n
    for j = 2:len_coef
      %adaugarea urmatorului termen in suma
      y_interp(i) = y_interp(i) + coef(j) * (x_interp(i) ^ (j - 1));
    endfor
  endfor
end
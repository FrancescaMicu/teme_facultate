function coef = vandermonde(x, y)
  %determinarea numarului de puncte din x
  n = length(x);
  %initializarea matricii Vandermonde
  V = zeros(n, n);
  for i = 1:n
    for j = 2:n
      %calcularea elementelor matricei
      V(i, j) = x(i) ^ (j - 1);
    endfor
  endfor
  %actualizarea primei coloane cu 1
  for i = 1:n
    V(i, 1) = 1;
  endfor
  %calcularea vectorului de coeficienti
  coef = V \ y;
end
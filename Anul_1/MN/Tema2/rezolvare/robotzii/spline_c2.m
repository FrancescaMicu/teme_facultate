function coef = spline_c2(x, y)
  %determinarea numarului de intervale
  n = length(x) - 1;
  %initializarea matricei de coeficienti
  A = zeros(4 * n, 4 * n);
  %initializarea vectorului de termeni liberi
  b = zeros(4 * n, 1);
  %completarea matricei si a vectorilor pentru ecuatile si(xi) = yi
  for i = 1:n
    A(i, 4 * (i - 1) + 1) = 1;
    b(i) = y(i);
  endfor
  %completarea matricei si a vectorilor pentru ecuatile s_n-1(xn) = yn
  b(n + 1) = y(n + 1);
  for i = 1:4
    A(n + 1, 4 * (n - 1) + i) = (x(n + 1) - x(n)) ^ (i - 1);
  endfor
  %completarea matricei si a vectorilor pentru ecuatile si(x_i+1) = s_i+1(x_i+1)
  for i = 1:n - 1
    for j = 1:4
      A(n + 1 + i, 4 * (i - 1) + j) = (x(i + 1) - x(i)) ^ (j - 1);
    endfor
    b(n + 1 + i, 1) = 0;
    A(n + 1 + i, 4 * i + 1) = -1;
  endfor
  %completarea matricei si a vectorilor pentru ecuatile si'(x_i+1) = s_i+1'(x_i+1)
  for i = 1:n - 1
    for j = 1:3
      A(2 * n + i, 4 * (i - 1) + j + 1) = j * ((x(i + 1) - x(i)) ^ (j - 1));
    endfor
    b(2 * n + i, 1) = 0;
    A(2 * n + i, 4 * i + 2) = -1;
  endfor
  %completarea matricei si a vectorilor pentru ecuatile si''(x_i+1) = s_i+1''(x_i+1)
  for i = 1:n-1
    for j = 1:2
      A(3 * n + i - 1, 4*(i - 1) + 3 + j - 1) = 2 * (3 ^ (j - 1)) * ((x(i + 1) - x(i)) ^ (j - 1));
    endfor
    A(3 * n + i - 1, 4*i + 3) = -2;
    b(3 * n + i - 1, 1) = 0;
  endfor
  %completarea matricei si a vectorilor pentru ecuatile s0''(x0) = 0
  A(4 * n - 1, 3) = 2;
  b(4 * n - 1, 1) = 0;
  %completarea matricei si a vectorilor pentru ecuatile s_n-1''(x_n) = 0
   b(4 * n, 1) = 0;
   for i = 1:2
     A(4 * n, 4 * (n - 1) + 3 + i - 1) = 2 * (3 ^ (i - 1)) * ((x(n + 1) - x(n)) ^ (i - 1));
   endfor
  %rezolvarea sistemului
  coef = A \ b;
end
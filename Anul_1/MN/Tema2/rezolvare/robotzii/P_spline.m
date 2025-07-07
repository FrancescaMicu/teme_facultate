function y_interp = P_spline (coef, x, x_interp)
  %determinarea numarului de intervale
  n = length(x) - 1;
  %determinarea numarului de puncte
  nr_pct = length(x_interp);
  %initializarea vectorului coloana
  y_interp = zeros(nr_pct, 1);
  for i = 1:nr_pct
    %cautarea primului punct din interval
    for j = 1:n
      if x_interp(i) >= x(j) && x_interp(i) <= x(j + 1)
        ai = coef(4 * (j - 1) + 1);
        bi = coef(4 * (j - 1) + 2);
        ci = coef(4 * (j - 1) + 3);
        di = coef(4 * (j - 1) + 4);
        xi = x_interp(i) - x(j);
        %calcularea polinomului
        y_interp(i) = ai + bi * xi + ci * (xi ^ 2) + di * (xi ^ 3);
        %iesire din bucla de cautare
        j = n + 1;
      endif
    endfor
  endfor
end
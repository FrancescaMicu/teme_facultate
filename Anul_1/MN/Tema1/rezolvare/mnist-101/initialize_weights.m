function [matrix] = initialize_weights(L_prev, L_next)
  %calcularea valorii epsilon
  eps_0 = sqrt(6) / sqrt(L_prev + L_next);
  %obtinerea in matrix de valori aleatorii din intervalul (-eps_0,eps_0)
  matrix = -eps_0 + 2 *eps_0 * rand(L_next, L_prev + 1);
endfunction

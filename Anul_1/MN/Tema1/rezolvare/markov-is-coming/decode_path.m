function [decoded_path] = decode_path (path, lines, cols)
  %lungimea vectorului path
  n = length(path);
  %verificare daca se ajunge la starea de win
  if path(n) == lines*cols + 1
    %se elimina starea win din vector
    path = path(1:n-1);
  endif
  n = n - 1;
  %initializarea vectorului de decodificare
  decoded_path = zeros(n,2);
  for i = 1:n
    codif = path(i);
    %obtinerea liniei si coloanei elementului respectiv
    decoded_path(i, 1) = floor((codif - 1) / cols) + 1;
    decoded_path(i, 2) = (codif - 1 - (decoded_path(i, 1) - 1) * cols) + 1;
  endfor
endfunction

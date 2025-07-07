function [Labyrinth] = parse_labyrinth(file_path)
  %deschiderea fisierului
  fisier = fopen(file_path, "rt");
  if fisier == -1
    return;
  endif
  %citirea numarului de linii si coloane
  lin_col = fscanf(fisier, '%d', 2);
  n = lin_col(1);
  m = lin_col(2);
  Labyrinth = zeros(n, m);
  %citirea elementelor din matrice
  for i = 1:n
    linie = fscanf(fisier, '%d', m);
    for j = 1:m
      Labyrinth(i, j) = linie(j);
    endfor
  endfor
  %inchidere fisier
  fclose(fisier);
end


function mat = read_mat(path)
  %deschiderea fisierului pentru citire
  fisier = fopen(path, "rt");
  %citirea primei linii (header-ul)
  linie = fgetl(fisier);
  %determinarea numarului de coloane
  elemente = strsplit(linie, ",");
  nr_col = length(elemente) - 1;
  %inițializarea matricei
  nr_lin = 0;
  mat = zeros(nr_lin, nr_col);
  %citirea urmatoarei linii
  linie = fgetl(fisier);
  while linie != -1
    nr_lin++;
    %impartirea elementelor din linie
    elemente = strsplit(linie, ",");
    %transformarea din sir de caractere in numere
    transf = str2double(elemente(2:nr_col + 1));
    %adugam linia la matrice
    mat(nr_lin, :) = transf;
    %citirea urmatoarei linii
    linie = fgetl(fisier);
  endwhile
  %inchiderea fisierului
  fclose(fisier);
end
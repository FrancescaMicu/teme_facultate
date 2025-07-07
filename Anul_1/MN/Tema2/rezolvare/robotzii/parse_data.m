function [x, y] = parse_data(filename)
  %deschiderea fisierului
  fisier = fopen(filename, 'r');
  %citirea numarului de coloane n
  linie = fgetl(fisier);
  n = str2num(linie);
  %initializarea vectorilor
  x = zeros(n + 1, 1);
  y = zeros(n + 1, 1);
  %citirea liniei cu valorile lui x
  linie = fgetl(fisier);
  x = str2num(linie)';
  %citirea liniei cu valorile lui y
  linie = fgetl(fisier);
  y = str2num(linie)';
  %inchiderea fisierului
  fclose(fisier);
end
function [Y, InitialMatrix] = parse_csv_file(file_path)
  %deschiderea fisierului
  fisier = fopen(file_path, 'rt');
  if fisier == -1
    return;
  endif
  %citirea primei linii
  antete_lin = fgets(fisier);
  %separarea antetelor
  antete = strsplit(antete_lin, ',');
  %citirea dtelor din csv
  nr_ant = length(antete);
  format = repmat('%s ', 1, nr_ant);
  info = textscan(fisier, format, 'Delimiter', ',');
  %numarul de campuri
  nr_camp = length(info{1});
  %initializarea vextorului si a matricei
  Y = zeros(nr_camp, 1);
  InitialMatrix = cell(nr_camp, nr_ant - 1);
  %prelucrarea datelor pentru vectorul Y
  for i = 1:nr_camp
    Y(i) = str2double(info{1}{i});
  endfor
  %prelucrarea datelor pentru matrice
  for j = 2:nr_ant
    for i = 1:nr_camp
      %converteste cuvantul la numar
      nr = str2double(info{j}{i});
      %verificare daca a reusit conversia
      if isnumeric(nr) && nr == nr
        InitialMatrix{i, j-1} = nr;
      else
        InitialMatrix{i, j-1} = info{j}{i};
      endif
    endfor
  endfor
  %inchiderea fisierului
  fclose(fisier);
endfunction

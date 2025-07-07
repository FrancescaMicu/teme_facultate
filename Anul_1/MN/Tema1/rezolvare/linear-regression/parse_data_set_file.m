function [Y, InitialMatrix] = parse_data_set_file(file_path)
  fisier = fopen(file_path, "rt");
  if fisier == -1
    return;
  endif
  %citirea numarului de linii si coloane
  lin_col = fscanf(fisier, '%d', 2);
  m = lin_col(1);
  n = lin_col(2);
  %initializarea vectorului si a matricei
  Y = zeros(m, 1);
  %eliminarea caracterului newline ramas
  fgetl(fisier);
  InitialMatrix = cell(m, n - 1);
  for i = 1:m
    linie = fgets(fisier);
    %eliminarea caracterului newline ramas
    linie = strtrim(linie);
    %impartirea in cuvinte
    cuv = strsplit(linie);
    %repararea cuvintelor din ultima coloana
    nr_cuv = length(cuv);
    %repararea cuvintelor din ultima coloana
    while nr_cuv > 1
      if strcmp(cuv{nr_cuv}, 'furnished') && nr_cuv > 1
        %verificare daca expresia era semi-furnised
        if strcmp(cuv{nr_cuv-1}, 'semi-')
          cuv{nr_cuv-1} = 'semi-furnished';
          cuv(nr_cuv) = [];
        %verificare daca expresia era unfurnised
        elseif strcmp(cuv{nr_cuv-1}, 'un')
          cuv{nr_cuv-1} = 'unfurnished';
          cuv(nr_cuv) = [];
        endif
      endif
      nr_cuv = nr_cuv - 1;
    endwhile
    %transformarea primului element in numar
    Y(i) = str2double(cuv{1});
    for j = 1:n
      %converteste cuvantul la numar
      nr = str2double(cuv{j + 1});
      %verificare daca a reusit conversia
      if isnumeric(nr) && nr == nr
        InitialMatrix{i, j} = nr;
      else
        InitialMatrix{i, j} = cuv{j + 1};
      endif
    endfor
  endfor
   %inchiderea fisierului
  fclose(fisier);
endfunction

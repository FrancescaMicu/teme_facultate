function [FeatureMatrix] = prepare_for_regression(InitialMatrix)
  %determinarea dimensiunlor matricei initiale
  [n, m] = size(InitialMatrix);
  %initializarea matricei de iesire
  FeatureMatrix = zeros(n, m + 1);
  for i = 1:n
    idx_col = 1;
    for j = 1:m
      cuv = InitialMatrix{i, j};
      %verificare daca cuvantul e deja numar
      if isnumeric(cuv)
        FeatureMatrix(i, idx_col) = cuv;
      %verificare daca e sir de caractere
      else
        %verificare daca e de tip yes/no
        if strcmp(cuv, 'yes')
          FeatureMatrix(i, idx_col) = 1;
        elseif strcmp(cuv, 'no')
          FeatureMatrix(i, idx_col) = 0;
        %Verificare daca e tip de mobilier
        elseif strcmp(cuv, 'furnished')
          FeatureMatrix(i, idx_col) = 0;
          FeatureMatrix(i, idx_col + 1) = 0;
          idx_col = idx_col + 1;
        elseif strcmp(cuv, 'unfurnished')
          FeatureMatrix(i, idx_col) = 0;
          FeatureMatrix(i, idx_col + 1) = 1;
          idx_col = idx_col + 1;
        elseif strcmp(cuv, 'semi-furnished')
          FeatureMatrix(i, idx_col) = 1;
          FeatureMatrix(i, idx_col + 1) = 0;
          idx_col = idx_col + 1;
        endif
      endif
      idx_col = idx_col + 1;
    endfor
  endfor
endfunction

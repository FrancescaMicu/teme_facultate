function [X, y] = load_dataset(path)
  %incarcarea informatilor in variabila info
  info = load(path);
  %verificarea reusitei operatiei anterioare
  if isstruct(info)
    %initializarea si atribuirea matricei si vectorului
    X = info.X;
    y = info.y;
  else
    return;
  endif
endfunction

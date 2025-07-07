function [path] = heuristic_greedy(start_position, probabilities, Adj)
  %determinarea nr de linii/coloane ale matricei de adiacenta
  [n, n] = size(Adj);
  %initializarea vectorului path
  path = zeros(n, 1);
  path(1) = start_position;
  nr_path = 1;
  %initializarea vectorului de vizitare
  viz = zeros(n, 1);
  viz(start_position) = 1;
  while nr_path
    poz = path(nr_path);
    %verificare daca s-a ajuns la starea win
    if poz == n - 1
      path = path(1:nr_path);
      return;
    endif
    %initializarea vectorului de vecini
    neigh = zeros(n, 1);
    nr_neigh = 0;
    %cautarea vecinilor in matricea de adiacenta
    for i = 1:n
      if Adj(poz, i) > 0
        nr_neigh = nr_neigh + 1;
        neigh(nr_neigh) = i;
      endif
    endfor
    %initializarea vectorului de vecini nevizitati
    unviz = zeros(n, 1);
    nr_unviz = 0;
    %cautarea vecinilor nevizitati in vectorul de vecini
    for i = 1:nr_neigh
      if viz(neigh(i)) == 0
        nr_unviz = nr_unviz + 1;
        unviz(nr_unviz) = neigh(i);
      endif
    endfor
    %verificare daca nu exista vecini nevizitati
    if nr_unviz == 0
      nr_path = nr_path - 1;
      continue;
    endif
    %determinarea indexului elementului cu probabilitatea cea mai mare de
    %castig din vectorul de vecini nevizitati
    [~, idx_max] = max(probabilities(unviz(1:nr_unviz)));
    %determinarea valorii vecinului nevizitat cel mai fvorabil
    max_neigh = unviz(idx_max);
    viz(max_neigh) = 1;
    nr_path = nr_path + 1;
    %adaugarea in path a noii valori favorabile
    path(nr_path) = max_neigh;
  endwhile
  %resetarea lui path pentru a avea doar valoriile cautate
  path = path(1:nr_path);
endfunction

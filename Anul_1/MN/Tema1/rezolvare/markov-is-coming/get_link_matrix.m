function [Link] = get_link_matrix(Labyrinth)
  %obtinere matrice de adiacenta
  Adj = get_adjacency_matrix(Labyrinth);
  [n, m] = size(Adj);
  %initializare matrice de legaturi
  Link = sparse(n, m);
  for i = 1:n
    count_legat = 0
    for j = 1:m
      %determinarea numarului de legaturi a fiecarei stari
      if Adj(i,j) == 1
        count_legat++;
      endif
    endfor
    if count_legat > 0
      for j = 1:m
        if Adj(i,j) == 1
          %obtinerea raportului de legaturi pt matricea Link
          Link(i,j) = 1/count_legat;
        endif
      endfor
    endif
  endfor
end



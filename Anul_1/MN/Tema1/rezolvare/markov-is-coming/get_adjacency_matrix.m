function [Adj] = get_adjacency_matrix(Labyrinth)
    %obtinerea nr de linii si coloane ale matricei initiale
    [n, m] = size(Labyrinth);
    %determinarea numarului de linii si coloane pt matricea de adiacenta
    nr_stari = n*m + 2;
    st_win = nr_stari - 1;
    st_lose = nr_stari;
    %initializarea matricei de adiacenta
    Adj = sparse(nr_stari, nr_stari);
    for i = 1:n
        for j = 1:m
            %determinarea indexului corespunzator din matricea de adiacenta
            idx = (i - 1)*m + j;
            %verficare perete nord
            if ~bitand(Labyrinth(i, j), 8)
                %verficare pt starea win
                if i == 1
                    Adj(idx, st_win) = 1;
                else
                    Adj(idx, (i - 2)*m + j) = 1;
                endif
            endif
            %verificare perete sud
            if ~bitand(Labyrinth(i, j), 4)
                %verficare pt starea win
                if i == n
                    Adj(idx, st_win) = 1;
                else
                    Adj(idx, i*m + j) = 1;
                endif
            endif
        endfor
    endfor
    for j = 1:m
        for i = 1:n
          %determinarea indexului corespunzator din matricea de adiacenta
            idx = (i - 1)*m + j;
            %verficare perete est
            if ~bitand(Labyrinth(i, j), 2)
                %verificarea pt starea lose
                if j == m
                    Adj(idx, st_lose) = 1;
                else
                    Adj(idx, (i - 1)*m + j + 1) = 1;
                endif
            endif
            %verficare perete vest
            if ~bitand(Labyrinth(i, j), 1)
                %verficare pt starea lose
                if j == 1
                    Adj(idx, st_lose) = 1;
                else
                    Adj(idx, (i - 1)*m + j - 1) = 1;
                endif
            endif
        end
    endfor
    Adj(st_win, st_win) = 1;
    Adj(st_lose, st_lose) = 1;
endfunction

function reduced_mat = preprocess(mat, min_reviews)
  %initializarea matricei reduced_mat cu matricea initiala
  reduced_mat = mat;
  %obtinerea dimensiunilor matricei
  [n, m] = size(reduced_mat);
  i = 1;
  %parcurgerea pe linii a matricei
  while i <= n
    %determinarea numarului de review-uri bune peentru un client
    nr_review = 0;
    for j = 1:m
      if reduced_mat(i, j) >= 1 && reduced_mat(i, j) <= 10
        nr_review++;
      endif
    endfor
    %verificare daca numarul de review-uri determinate respecta conditia
    if nr_review < min_reviews
      %eliminarea liniei respective in caz negativ
      reduced_mat(i:n - 1, :) = reduced_mat(i + 1:n, :);
      n--;
      i--;
    endif
    i++;
  endwhile
  %redimensionarea matricei
  reduced_mat = reduced_mat(1:n, :);
end
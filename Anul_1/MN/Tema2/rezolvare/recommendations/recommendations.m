function recoms = recommendations(path, liked_theme, num_recoms, min_reviews, num_features)
  %citirea matricei
  mat = read_mat(path);
  % procesarea matricei cu min_reviews
  preprocessed_mat = preprocess(mat, min_reviews);
  %aplicarea factorizarii
  [U E V] = svds(preprocessed_mat, num_features);
  %determinarea nr de linii ale matricei V
  [m, ~] = size(V);
  %initializarea matricei de recomandari
  recoms = zeros(1, m);
  for i = 1: m
    if i != liked_theme
       %determinarea similaritatilor cu liked_theme
       recoms(i) = cosine_similarity(V(liked_theme, :)', V(i, :)');
    endif
  endfor
  %sortarea recomandarilor
  [~, recoms] = sort(recoms, 'descend');
  %obtinerea primelor num_recoms recomandari sortate
  recoms = recoms(1:num_recoms);
end
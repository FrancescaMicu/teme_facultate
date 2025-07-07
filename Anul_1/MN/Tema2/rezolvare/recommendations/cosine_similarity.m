function similarity = cosine_similarity(A, B)
  %determinarea similaritatii pentru cei doi vectori
  similarity = (A' * B)/(norm(A, 2) * norm(B, 2));
end
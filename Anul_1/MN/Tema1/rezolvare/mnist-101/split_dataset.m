function [X_train, y_train, X_test, y_test] = split_dataset(X, y, percent)
  %determinarea numarului de linii/exemple pt matricea X
  [n, ~] = size(X);
  %crearea unui vector de n indexi aleatorii crescatori
  [~, idx] = sort(rand(n, 1));
  %determinarea nr de exemple pt train
  nr_train = round(n * percent);
  %impartirea in train si test pentru matricea x
  X_train = X(idx(1:nr_train), :);
  X_test = X(idx(nr_train + 1:n), :);
  %impartirea in train si test pentru vectorul y
  y_train = y(idx(1:nr_train));
  y_test = y(idx(nr_train + 1:n));
endfunction


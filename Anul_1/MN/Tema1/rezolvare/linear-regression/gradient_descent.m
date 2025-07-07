function [Theta] = gradient_descent(FeatureMatrix, Y, n, m, alpha, iter)
  %initializarea vectorului Theta
  Theta = zeros(n + 1, 1);
  %pasii pentru algoritmul gradientului descendent
  for i = 1:iter
    %determinarea erorilor
    err = FeatureMatrix * Theta(2:n + 1) - Y;
    %determinarea gradientilor
    grad = (1 / m) * (FeatureMatrix' * err);
    %actualizarea vectorului Theta
    Theta(2:n + 1) = Theta(2:n + 1) - alpha * grad;
  endfor
endfunction

function [Error] = lasso_regression_cost_function(Theta, Y, FeatureMatrix, lambda)
  %numarul de linii/exemple a matricei Y
  [n, ~] = size(Y);
  %adaugarea termenului liber in matrice
  FeatureMatrix = [ones(n, 1), FeatureMatrix];
  %calculul regularizarii
  suma = sum((Y - FeatureMatrix * Theta).^2);
  Error = 1 / n * suma + lambda * norm(Theta, 1);
endfunction

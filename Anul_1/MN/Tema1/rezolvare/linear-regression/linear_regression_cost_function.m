function [Error] = linear_regression_cost_function(Theta, Y, FeatureMatrix)
  %numarul de linii/exemple a matricei Y
  [n, ~] = size(Y);
  %adaugarea termenului liber in matrice
  FeatureMatrix = [ones(n, 1), FeatureMatrix];
  %determinarea erorii
  err = Y - FeatureMatrix * Theta;
  suma = sum(err.^2);
  %calcularea erorii/costului final
  Error = (1 / (2 * n)) * suma;
end

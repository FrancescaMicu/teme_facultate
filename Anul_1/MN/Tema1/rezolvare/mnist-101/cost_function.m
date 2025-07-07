function [J, grad] = cost_function(params, X, y, lambda, input_layer_size, hidden_layer_size, output_layer_size)
  %obtinerea numarului de linii/exemple din matricea X
  [n, ~] = size(X);
  %determinarea dimensiunilor pentru theta 1 si 2
  th1_lin = hidden_layer_size;
  th1_col = input_layer_size + 1;
  th2_lin = output_layer_size;
  th2_col = hidden_layer_size + 1;
  %determinarea matricelor theta 1 si 2
  th1 = reshape(params(1:(th1_lin*th1_col)), th1_lin, th1_col);
  th2 = reshape(params((th1_lin*th1_col) + 1:length(params)), th2_lin, th2_col);
  %codificarea claselor pentru iesirea retelei
  matr_y = zeros(n, output_layer_size);
  for i = 1:n
    matr_y(i, y(i)) = 1;
  endfor
  %operatii pentru predictie si forward propagation
  a1 = [ones(n, 1), X];
  z2 = th1 * a1';
  %aplicarea functiei sigmoid
  a2 = sigmoid(z2);
  a2 = [ones(1, n); a2];
  z3 = th2 * a2;
  %aplicarea functiei sigmoid
  a3 = sigmoid(z3);
  %calcularea costului
  J = sum(sum(-matr_y' .* log(a3) - (1 - matr_y') .* log(1 - a3))) / n;
  %calculul regularizarii
  reg = (lambda / (2 * n)) * (sum(sum(th1(:, 2:size(th1, 2)).^2)) + sum(sum(th2(:, 2:size(th2, 2)).^2)));
  J = J + reg;
  %operatii pentru backpropagation
  del3 = a3 - matr_y';
  % Calculul del2 corect dimensional
  der_sigm = a2 .* (1 - a2);
  del2 = th2' * del3 .* der_sigm;
  del2 = del2(2:size(del2, 1), :);
  %operatii pentru calcularea gradientilor
  grad1 = del2 * a1;
  grad2 = del3 * a2';
  %regularizarea gradientilor
  grad1(:, 2:th1_col) = grad1(:, 2:th1_col) + (lambda * th1(:, 2:th1_col));
  grad2(:, 2:th2_col) = grad2(:, 2:th2_col) + (lambda * th2(:, 2:th2_col));
  %normalizarea si vectorizarea gradientilor
  grad1 = grad1 / n;
  grad2 = grad2 / n;
  grad = [grad1(:); grad2(:)];
endfunction

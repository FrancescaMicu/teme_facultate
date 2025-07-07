function [classes] = predict_classes(X, weights, ...
                  input_layer_size, hidden_layer_size, ...
                  output_layer_size)
  %numarul de linii/exemple din matricea X
  [n, ~] = size(X);
  %reconstruirea matricelor de pondere theta1 și theta2 din vectorul weights
  th1_lin = hidden_layer_size;
  th1_col = input_layer_size + 1;
  th2_lin = output_layer_size;
  th2_col = hidden_layer_size + 1;
  %determinarea matricelor theta 1 si 2
  th1 = reshape(weights(1:(th1_lin*th1_col)), th1_lin, th1_col);
  th2 = reshape(weights((th1_lin*th1_col) + 1:length(weights)), th2_lin, th2_col);
  %operatiile pentru forward propagation
  a1 = [ones(n, 1), X];
  z2 = th1 * a1';
  %aplicarea functiei sigmoid
  a2 = sigmoid(z2);
  a2 = [ones(1, n); a2];
  z3 = th2 * a2;
  %aplicarea functiei sigmoid
  a3 = sigmoid(z3);
  %numarul de coloane a vectorului a3
  [~, classes_col] = size(a3);
  %initializarea vectorului classes
  classes = zeros(classes_col, 1);
  for i = 1:classes_col
    %determinarea indexului valorii maxime din fiecare coloana
    [~, classes(i)] = max(a3(:, i));
  endfor
endfunction

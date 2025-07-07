function [x, err, steps] = perform_iterative(G, c, x0, tol, max_steps)
  %determinarea lungimii vectorului c
  n = length(c);
  %initializarea vectorului solutie
  x = zeros(n, 1);
  steps = 1;
  x = x0;
  for p = 1:max_steps
    %calcularea solutiei la pasul i
    x = G*x0 + c;
    %verificarea indeplinirii tolerantei
    if (norm(x - x0) < tol)
      return;
    endif
    steps = steps + 1;
    %calcularea erorii
    err = norm(x - x0);
    x0 = x;
  endfor
endfunction

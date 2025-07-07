function [G, c] = get_Jacobi_parameters (Link)
	%dimensiunea matricei Link
  [n, n] = size(Link);
  %dimensiunea matricei si vectorului de iteratie
  n_new = n - 2;
  %initializarea matricei si vectorului de iteratie
	G = sparse(n_new,n_new);
  c = sparse(n_new, 1);
  %completarea celor doua cu elementele liniile si coloanele specifice
  G = Link(1:n_new, 1:n_new);
  c = Link(1:n_new, n_new + 1);
end

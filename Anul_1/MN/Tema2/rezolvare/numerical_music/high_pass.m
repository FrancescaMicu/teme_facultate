function signal = high_pass(signal, fs, cutoff_freq)
  %determinarea transformatei fourier a semnalului
  sign_ft = fft(signal);
  %crearea vectorului de frecvente
  n = length(signal);
  nr_frecv = floor(n / 2) + 1;
  %initializarea vectorului
  frecv = zeros(1, nr_frecv);
  %calcularea individuala a frecventelor
  for i = 1:nr_frecv
    frecv(i) = (i - 1) * (fs / n);
  endfor
  %calcularea indexului pentru frecventa de taiere
  rezol = fs / n;
  cutoff = round(cutoff_freq / rezol);
  %crearea vectorului de masca
  mask_vect = zeros(n, 1);
  if cutoff >= 0
    %marcarea frecventelor inalte
    mask_vect(cutoff + 1:n - cutoff) = 1;
  endif
  %determinarea semnalului dupa aplicarea mastii
  new_sign = sign_ft .* mask_vect;
  %determinarea semnalului filtrat
  signal = ifft(new_sign);
  %normalizarea semnalului filtrat
  signal = signal / max(abs(signal));
end


function [S, f, t] = spectrogram(signal, fs, window_size)
  %determinarea numarului de ferestre
  nr_wind = floor(length(signal) / window_size);
  %initializarea matricei de spectograma
  S = zeros(window_size, nr_wind);
  %pentru calculul fft cu o rezolutie mai mare
  rezol = 2 * window_size;
  % Pentru fiecare fereastră
  for i = 1:nr_wind
    %determinarea ferestrei respective
    window = signal((i - 1) * window_size + 1: i * window_size);
    %"netezirea" marginilor cu functia hanning
    hann_wind = hanning(window_size);
    nou_wind = zeros(1, window_size);
    for j = 1:window_size
      nou_wind(j) = window(j) * hann_wind(j);
    endfor
    %aplicarea transformatei fourier pe fereastra
    transf = fft(nou_wind, rezol);
    %eliminarea partii conjugata
    transf = transf(1:window_size);
    %actualizarea matricei spectograma
    S(:, i) = abs(transf);
  endfor
  %determinarea vectorului de frecventa
  f = zeros(window_size, 1);
  for i = 1:window_size
    f(i) = fs / rezol * (i - 1);
  endfor
  %determinarea vectorului de timp
  t = zeros(nr_wind, 1);
  for i = 1:nr_wind
    t(i) = window_size / fs * (i - 1);
  endfor
end
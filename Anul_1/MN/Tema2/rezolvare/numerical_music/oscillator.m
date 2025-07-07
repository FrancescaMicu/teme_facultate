function x = oscillator(freq, fs, dur, A, D, S, R)
  %constructia vectorului de timp
  nr_esant = fs * dur;
  timp = 0 : 1/fs : dur;
  timp = timp(1:nr_esant);
  %crearea undei sinusoidala
  sin_w = sin(2 * pi * freq * timp)';
  %determinarea vectorului de attack
  nr_att = floor(A * fs);
  att = linspace(0, 1, nr_att);
  %determinarea vectorului de decay
  nr_dec = floor(D * fs);
  dec = linspace(1, S, nr_dec);
  %determinarea vectorului de release
  nr_rel = floor(R * fs);
  rel = linspace(S, 0, nr_rel);
  %determinarea vectorului de sustain
  nr_sust = length(timp) - nr_att - nr_dec - nr_rel;
  sust = S * ones(1, nr_sust);
  %determinarea vectorului de attack
  %crearea envelope-ului ASDR
  ASDR = [att, dec, sust, rel]';
  %vectorul de unda sinus final
  x = sin_w .* ASDR;
end
function signal = apply_reverb(signal, impulse_response)
  %transformarea impulsului in mono
  impulse_response = stereo_to_mono(impulse_response);
  %calcularea convolutiei dintre semnal si impuls
  signal = fftconv(signal, impulse_response);
  %normalizarea semnalului
  signal = signal / max(abs(signal));
end

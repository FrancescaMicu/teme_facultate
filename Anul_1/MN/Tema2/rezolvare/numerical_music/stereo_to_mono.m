function mono = stereo_to_mono(stereo)
  mono = stereo;
  %transformarea semnalului
  mono = mean(mono, 2);
  %normalizarea vectorului
  mono = mono / max(abs(mono));
end
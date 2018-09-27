#!/usr/bin/python

import alsaaudio, wave
from scipy import signal
import numpy as np
import matplotlib.pyplot as plt



inp = alsaaudio.PCM(alsaaudio.PCM_CAPTURE)
inp.setchannels(1)
inp.setrate(44100)
inp.setformat(alsaaudio.PCM_FORMAT_S16_LE)
inp.setperiodsize(1024)

w = wave.open('test.wav', 'w')
w.setnchannels(1)
w.setsampwidth(2)
w.setframerate(44100)
audio = []
try:
    while True:
        l, data = inp.read()
        a = np.fromstring(data, dtype='int16')
        audio.append(np.abs(a).mean())
        w.writeframes(data)
except KeyboardInterrupt:
    pass
   
frequencyDomainSignal = np.fft.fft(audio)


plt.plot(audio)
plt.show()

raw_input('Press Enter')

# plt.plot(frequencyDomainSignal)
# plt.show()

b,a = signal.butter(5,1000/(44100/2), btype='highpass')

filtered = signal.lfilter(b,a,frequencyDomainSignal)
plt.plot(filtered) # plotting the signal.
plt.title('Highpass Filter')
plt.xlabel('Frequency(Hz)')
plt.ylabel('Amplitude')

exit()
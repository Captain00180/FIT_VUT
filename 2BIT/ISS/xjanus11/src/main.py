from scipy.io import wavfile
import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import lfilter


def cutWav(signal, fs):
    # Second from which the 1 second part will be extracted
    start_sec = 1.6

    # Cut out one second
    start = int(16000 * start_sec)
    return signal[start:start + 16000]


def savePlot(data, fs, name):
    t = np.arange(data.size) / fs

    plt.figure(figsize=(6, 3))
    plt.plot(t, data)
    plt.gca().set_xlabel('$t[s]$')
    plt.tight_layout()
    plt.savefig(name + '.png')
    plt.clf()


# Process the signal and split it into 20ms frames
def task3ProcessSig(signal, fs):
    # "ustredneni"
    signal = signal - np.mean(signal)

    # Normalize
    signal = signal / np.abs(signal).max()

    # Divide into frames
    overlap = int(fs * 0.01)  # Pocet vzoriek, ktore sa medzi ramcami prekryvaju (160)

    framesize = int(fs * 0.02)  # Velkost ramca vo vzorkach (320)

    n_of_frames = int(len(signal) / overlap) - 1        # 99 frames

    frames = np.ndarray((n_of_frames, framesize))
    for k in range(n_of_frames):
        for i in range(framesize):
            frames[k][i] = signal[k * overlap + i]
    return frames


def centerClipping(frames):
    result = np.ndarray((len(frames), len(frames[0])))
    for idx in range(len(frames)):
        thresh = max(abs(frames[idx]))
        for j in range(len(frames[idx])):
            if frames[idx][j] > 0.7 * thresh:
                result[idx][j] = 1
            elif frames[idx][j] < -0.7 * thresh:
                result[idx][j] = -1
            else:
                result[idx][j] = 0
    return result


# Vlastna implementacia autokorelacnej funkcie
def autoCorrelation(signal):
    N = len(signal)
    corr = []
    for m in range(0, N):
        result = 0
        for n in range(m, N):
            result += signal[n] * signal[n - m]
        corr.append(result)
    return corr


# Vlastna implementacia DFT funkcie
def myDFT(signal, N):
    result = []
    for k in range(N):
        cnt = 0
        for n in range(N):
            if n < len(signal):         # Zabezpecuje 'zero padding'
                cnt += signal[n] * np.exp(np.complex(0, -2 * np.pi * k * n / N))
        result.append(cnt)
    return result


# Vlastna implementacia inverznej DFT funkcie
def myIDFT(signal, N):
    result = []
    for k in range(N):
        cnt = 0
        for n in range(N):
            if n < len(signal):
                cnt += signal[n] * np.exp(np.complex(0, 2 * np.pi * k * n / N))
        result.append(cnt / N)
    return result


def logSpec(signal):
    result = 10 * np.log10(np.abs(signal) ** 2 + 1e-20)
    return result


def task4(frames1, frames2):
    plt.clf()
    plt.figure(figsize=[15, 3])
    plt.plot([x / 320 * 0.02 for x in range(len(frames1[frame_idx]))], frames1[frame_idx])
    plt.gca().set_xlabel("t[s]")
    plt.gca().set_title("Ramec")
    plt.tight_layout()
    plt.savefig("task4_frame.pdf")

    # Clipping
    fr1_clip = centerClipping(frames1)
    fr2_clip = centerClipping(frames2)

    plt.clf()
    plt.figure(figsize=[15, 3])
    plt.plot([x / 320 * 0.02 for x in range(len(fr1_clip[frame_idx]))], fr1_clip[frame_idx])
    plt.gca().set_xlabel("t[s]")
    plt.gca().set_title("Ramec s aplikovanym Center Clipping")
    plt.tight_layout()
    plt.savefig("task4_frame_clip.pdf")

    # Autocorrelation

    # Correlated frames
    corr_1 = [autoCorrelation(x)for x in fr1_clip]
    corr_2 = [autoCorrelation(y)for y in fr2_clip]

    plt.clf()
    plt.figure(figsize=[15, 3])
    plt.plot(corr_1[frame_idx])
    plt.gca().set_xlabel("Vzorky")
    plt.gca().set_title("Autokorelacia ramca")
    plt.stem([np.argmax(corr_1[frame_idx][30:]) + 30], [np.max(corr_1[frame_idx][30:])], 'k', markerfmt='ro', label='Lag')
    plt.axvline(x=30, label='Prah', c='k')
    plt.legend()
    plt.tight_layout()
    plt.savefig("task4_frame_corr.pdf")

    # Lags of all frames
    max_corr_1 = [np.argmax(x[30:]) + 30 for x in corr_1]
    max_corr_2 = [np.argmax(x[30:]) + 30 for x in corr_2]

    freq_1 = [16000 / x for x in max_corr_1]
    freq_2 = [16000 / x for x in max_corr_2]

    # print("Stredna hodnota maskoff: ", np.mean(freq_1))
    # print("Stredna hodnota maskon: ", np.mean(freq_2))

    # print("Rozptyl maskoff: ", np.var(freq_1))
    # print("Rozptyl maskon: ", np.var(freq_2))

    plt.clf()
    plt.figure(figsize=[15, 3])
    plt.plot(freq_1, 'b', label='Bez ruska')
    plt.plot(freq_2, 'orange', label='S ruskom')
    plt.gca().set_xlabel("Ramce")
    plt.gca().set_ylabel("f0")
    plt.gca().set_title("Zakladna frekvencia ramcov")
    plt.legend()
    plt.tight_layout()
    plt.savefig("task4_freq.pdf")


# ____________________________ Signal loading  _______________________________________

file1 = "maskoff_tone"
fs1, signal1 = wavfile.read('../audio/' + file1 + '.wav')
signal1 = cutWav(signal1, fs1)

file2 = "maskon_tone"
fs2, signal2 = wavfile.read('../audio/' + file2 + '.wav')
signal2 = cutWav(signal2, fs2)

# ____________________________ Task 3 _______________________________________

frames_1 = task3ProcessSig(signal1, fs1)
frames_2 = task3ProcessSig(signal2, fs2)

# Frame which will be saved
frame_idx = 50
plt.clf()
fig, ax = plt.subplots(2)
ax[0].plot([x / 320 * 0.02 for x in range(len(frames_1[frame_idx]))], frames_1[frame_idx])
ax[0].set_xlabel("t[s]")
ax[0].set_title("Ramec z nahravky maskoff_tone")

ax[1].plot([x / 320 * 0.02 for x in range(len(frames_2[frame_idx]))], frames_2[frame_idx])
ax[1].set_xlabel("t[s]")
ax[1].set_title("Ramec z nahravky maskon_tone")
plt.tight_layout()
plt.savefig("task_3_graph.pdf", bbox_inches='tight')

# ____________________________ Task 4 _______________________________________

task4(frames_1, frames_2)

# ____________________________ Task 5 _______________________________________

# DFT
N = 1024

dft_sig1 = np.array([myDFT(x, N) for x in frames_1])
dft_sig1_log = np.array([logSpec(x) for x in dft_sig1])

plt.clf()
plt.figure(figsize=[9, 3])
plt.imshow(dft_sig1_log.T[:512], aspect='auto', extent=[0, 1, 8000, 0])
plt.gca().invert_yaxis()
plt.gca().set_xlabel("t[s]")
plt.gca().set_title("Spektogram bez ruska")
plt.gca().set_ylabel("frekvencia")
plt.colorbar()
plt.tight_layout()
plt.savefig("task_5_spec_maskoff.pdf")

dft_sig2 = np.array([myDFT(x, N) for x in frames_2])
dft_sig2_log = np.array([logSpec(x) for x in dft_sig2])

plt.clf()
plt.figure(figsize=[9, 3])
plt.imshow(dft_sig2_log.T[:512], aspect='auto', extent=[0, 1, 8000, 0])
plt.gca().invert_yaxis()
plt.gca().set_xlabel("t[s]")
plt.gca().set_ylabel("frekvencia")
plt.gca().set_title("Spektogram s ruskom")
plt.colorbar()
plt.tight_layout()
plt.savefig("task_5_spec_maskon.pdf")


# ____________________________ Task 6 _______________________________________

freq_res = np.array([dft_sig2[x] / dft_sig1[x] for x in range(len(dft_sig1))])
freq_char = np.average(np.abs(freq_res), axis=0)[:512]
frplot = np.array([logSpec(x) for x in freq_char])
plt.clf()
plt.plot([x / len(frplot) * 8000 for x in range(len(frplot))], frplot)
plt.gca().set_title("Frekvencna charakteristika filtra")
plt.gca().set_xlabel("Frekvencia")
plt.tight_layout()
plt.savefig("task_6_freq_char.pdf")

# ____________________________ Task 7 _______________________________________

filter_impuls = np.array(myIDFT(freq_char, 1024)[:512])
plt.clf()
plt.plot(filter_impuls.real)
plt.gca().set_title("Impulzna odozva ruska")
plt.tight_layout()
plt.savefig("task_7_impulse.pdf")

# ____________________________ Task 8 _______________________________________

_, maskoff = wavfile.read('../audio/maskoff_sentence.wav')
_, toneoff = wavfile.read('../audio/maskoff_tone.wav')

tone_sim = lfilter(x=toneoff, a=[1], b=filter_impuls.real)
sen_sim = lfilter(x=maskoff, a=[1], b=filter_impuls.real)

plt.clf()
plt.figure(figsize=[15,4])
plt.plot(maskoff, 'b', label='Nahravka bez ruska')
plt.plot(sen_sim, 'orange', label='Simulovane rusko')
plt.legend()
plt.tight_layout()
plt.savefig("task_8_sim_comp.pdf")

_, maskon = wavfile.read('../audio/maskon_sentence.wav')
plt.clf()
plt.plot(maskoff)
plt.gca().set_title("Nahravka bez ruska")
plt.tight_layout()
plt.savefig('task_8_maskoff.pdf')

plt.clf()
plt.figure(figsize=[15,4])
plt.plot(maskon, 'b', label='Nahravka s ruskom')
plt.plot(sen_sim, 'orange', label='Simulovane rusko')
plt.legend()
plt.tight_layout()
plt.savefig("task_8_sim_comp_mask.pdf")

plt.clf()
plt.plot(maskon)
plt.gca().set_title("Nahravka s ruskom")
plt.tight_layout()
plt.savefig('task_8_maskon.pdf')

plt.clf()
plt.plot(sen_sim)
plt.gca().set_title("Simulovane rusko")
plt.tight_layout()
plt.savefig('task_8_sim.pdf')

sen_sim = np.int16(sen_sim)
wavfile.write("../audio/sim_maskon_sentence.wav", 16000, sen_sim)

tone_sim = np.int16(tone_sim)
wavfile.write("../audio/sim_maskon_tone.wav", 16000, tone_sim)


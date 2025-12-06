import numpy as np
import matplotlib.pyplot as plt
import cmath

# ==================== 1. РЕКУРСИВНАЯ РЕАЛИЗАЦИЯ FFT ====================
def recursive_FFT(a):
    """
    Рекурсивное вычисление БПФ (алгоритм Кули-Тьюки)
    Вход: список комплексных чисел длиной степени двойки
    Выход: список комплексных чисел - результат FFT
    """
    n = len(a)
    
    # Базовый случай рекурсии
    if n == 1:
        return a
    
    # Разделяем на четные и нечетные индексы
    a_even = [a[i] for i in range(0, n, 2)]  # четные
    a_odd = [a[i] for i in range(1, n, 2)]   # нечетные
    
    # Рекурсивные вызовы
    f_even = recursive_FFT(a_even)
    f_odd = recursive_FFT(a_odd)
    
    # Объединяем результаты
    result = [0] * n
    for k in range(n // 2):
        # Поворачивающий множитель (комплексная экспонента)
        omega = cmath.exp(-2j * cmath.pi * k / n)
        
        # Бабочка Кули-Тьюки
        t = omega * f_odd[k]
        result[k] = f_even[k] + t
        result[k + n // 2] = f_even[k] - t
    
    return result

# ==================== 2. ИТЕРАТИВНАЯ РЕАЛИЗАЦИЯ FFT ====================
def iterative_FFT(a):
    """
    Итеративная реализация БПФ с бит-реверсией
    Более эффективна по памяти
    """
    n = len(a)
    
    # Бит-реверсия перестановка
    def bit_reverse_copy(arr):
        log_n = int(np.log2(n))
        result = [0] * n
        for i in range(n):
            # Переворачиваем биты индекса
            rev_i = int(bin(i)[2:].zfill(log_n)[::-1], 2)
            result[rev_i] = arr[i]
        return result
    
    # Начинаем с бит-реверсии
    arr = bit_reverse_copy(a)
    
    # Основной цикл итеративного БПФ
    s = 1
    while s <= int(np.log2(n)):
        m = 1 << s  # 2^s
        omega_m = cmath.exp(-2j * cmath.pi / m)
        
        for k in range(0, n, m):
            omega = 1
            for j in range(m // 2):
                t = omega * arr[k + j + m // 2]
                u = arr[k + j]
                arr[k + j] = u + t
                arr[k + j + m // 2] = u - t
                omega *= omega_m
        s += 1
    
    return arr

# ==================== 3. ПОДГОТОВКА СИГНАЛА ====================
# Параметры сигнала
fs = 128  # Частота дискретизации (Гц)
duration = 1.0  # Длительность (сек)
N = 128  # Количество отсчетов (степень двойки)

# Временная ось
t = np.linspace(0, duration, N, endpoint=False)

# Создаем сигнал: сумма трех синусоид + шум
freq1, amp1 = 10, 0.8   # 10 Гц, амплитуда 0.8
freq2, amp2 = 25, 0.5   # 25 Гц, амплитуда 0.5
freq3, amp3 = 40, 0.3   # 40 Гц, амплитуда 0.3

signal = (amp1 * np.sin(2 * np.pi * freq1 * t) +
          amp2 * np.sin(2 * np.pi * freq2 * t) +
          amp3 * np.sin(2 * np.pi * freq3 * t) +
          0.1 * np.random.randn(N))  # небольшой шум

# ==================== 4. ВЫЧИСЛЕНИЕ FFT ====================
# Используем нашу рекурсивную реализацию
fft_result = recursive_FFT(signal.tolist())

# Также вычислим через numpy для сравнения
fft_numpy = np.fft.fft(signal)

# Преобразуем в numpy array для удобства
fft_result = np.array(fft_result)

# ==================== 5. АНАЛИЗ РЕЗУЛЬТАТОВ ====================
# Частотная ось
freqs = np.fft.fftfreq(N, 1/fs)

# Вычисляем амплитуды (нормированные)
amplitudes = np.abs(fft_result) / N * 2
phases = np.angle(fft_result)

# Только положительные частоты (физические)
positive_mask = freqs >= 0
positive_freqs = freqs[positive_mask]
positive_amplitudes = amplitudes[positive_mask]
positive_phases = phases[positive_mask]

# Находим основные частотные компоненты
sorted_indices = np.argsort(positive_amplitudes)[::-1]  # по убыванию амплитуд

print("=" * 60)
print("АНАЛИЗ СИГНАЛА С ПОМОЩЬЮ FFT")
print("=" * 60)
print(f"\nПараметры сигнала:")
print(f"Частота дискретизации: {fs} Гц")
print(f"Длительность: {duration} с")
print(f"Количество отсчетов: {N}")
print(f"Разрешение по частоте: {fs/N:.2f} Гц")

print(f"\nИсходный сигнал содержит частоты:")
print(f"1. {freq1} Гц с амплитудой {amp1}")
print(f"2. {freq2} Гц с амплитудой {amp2}")
print(f"3. {freq3} Гц с амплитудой {amp3}")

print(f"\nРезультат FFT (первые 5 значений комплексных чисел):")
for i in range(5):
    print(f"f[{i}] = {fft_result[i]:.3f}  |  Амплитуда: {amplitudes[i]:.3f}, Фаза: {phases[i]:.3f} рад")

print(f"\nТоп-5 частотных компонент, обнаруженных FFT:")
for i, idx in enumerate(sorted_indices[:5]):
    freq = positive_freqs[idx]
    amp = positive_amplitudes[idx]
    phase = positive_phases[idx]
    print(f"{i+1}. Частота: {freq:6.1f} Гц | Амплитуда: {amp:.3f} | Фаза: {phase:.3f} рад")

# ==================== 6. ВИЗУАЛИЗАЦИЯ ====================
fig, axes = plt.subplots(2, 3, figsize=(15, 10))
fig.suptitle('Анализ сигнала с помощью FFT', fontsize=16)

# 1. Исходный сигнал
axes[0, 0].plot(t, signal, 'b-', linewidth=2, alpha=0.7)
axes[0, 0].set_title('Исходный сигнал (временная область)')
axes[0, 0].set_xlabel('Время (с)')
axes[0, 0].set_ylabel('Амплитуда')
axes[0, 0].grid(True, alpha=0.3)

# 2. Амплитудный спектр
axes[0, 1].stem(positive_freqs, positive_amplitudes, basefmt=" ", use_line_collection=True)
axes[0, 1].set_title('Амплитудный спектр (частотная область)')
axes[0, 1].set_xlabel('Частота (Гц)')
axes[0, 1].set_ylabel('Амплитуда')
axes[0, 1].set_xlim(0, fs/2)
axes[0, 1].grid(True, alpha=0.3)

# Подпишем пики
for idx in sorted_indices[:3]:
    axes[0, 1].annotate(f'{positive_freqs[idx]:.0f} Гц',
                       xy=(positive_freqs[idx], positive_amplitudes[idx]),
                       xytext=(0, 10),
                       textcoords='offset points',
                       ha='center',
                       arrowprops=dict(arrowstyle='->', color='red'))

# 3. Фазовый спектр
axes[0, 2].stem(positive_freqs, positive_phases, basefmt=" ", use_line_collection=True)
axes[0, 2].set_title('Фазовый спектр')
axes[0, 2].set_xlabel('Частота (Гц)')
axes[0, 2].set_ylabel('Фаза (радианы)')
axes[0, 2].set_xlim(0, fs/2)
axes[0, 2].grid(True, alpha=0.3)

# 4. Спектр мощности (в логарифмической шкале)
power_spectrum = positive_amplitudes ** 2
axes[1, 0].plot(positive_freqs, 10 * np.log10(power_spectrum + 1e-10), 'r-', linewidth=2)
axes[1, 0].set_title('Спектр мощности (dB)')
axes[1, 0].set_xlabel('Частота (Гц)')
axes[1, 0].set_ylabel('Мощность (dB)')
axes[1, 0].set_xlim(0, fs/2)
axes[1, 0].grid(True, alpha=0.3)

# 5. Комплексная плоскость (первые 20 значений)
axes[1, 1].scatter(fft_result[:20].real, fft_result[:20].imag, c='g', alpha=0.6, s=50)
axes[1, 1].plot([0, 0], [-max(abs(fft_result[:20].imag)), max(abs(fft_result[:20].imag))], 
               'k--', alpha=0.3)
axes[1, 1].plot([-max(abs(fft_result[:20].real)), max(abs(fft_result[:20].real))], 
               [0, 0], 'k--', alpha=0.3)
axes[1, 1].set_title('Комплексные значения (первые 20)')
axes[1, 1].set_xlabel('Действительная часть (Re)')
axes[1, 1].set_ylabel('Мнимая часть (Im)')
axes[1, 1].grid(True, alpha=0.3)

# 6. Сравнение с numpy FFT
axes[1, 2].plot(positive_freqs, positive_amplitudes, 'b-', linewidth=2, label='Наш FFT', alpha=0.7)
numpy_amplitudes = np.abs(fft_numpy)[positive_mask] / N * 2
axes[1, 2].plot(positive_freqs, numpy_amplitudes, 'r--', linewidth=1, label='NumPy FFT', alpha=0.7)
axes[1, 2].set_title('Сравнение с NumPy FFT')
axes[1, 2].set_xlabel('Частота (Гц)')
axes[1, 2].set_ylabel('Амплитуда')
axes[1, 2].set_xlim(0, 60)
axes[1, 2].legend()
axes[1, 2].grid(True, alpha=0.3)

plt.tight_layout()
plt.show()

# ==================== 7. ОБРАТНОЕ ПРЕОБРАЗОВАНИЕ ====================
def inverse_FFT(f):
    """Обратное преобразование Фурье"""
    n = len(f)
    
    if n == 1:
        return f
    
    # Разделяем
    f_even = [f[i] for i in range(0, n, 2)]
    f_odd = [f[i] for i in range(1, n, 2)]
    
    # Рекурсия
    a_even = inverse_FFT(f_even)
    a_odd = inverse_FFT(f_odd)
    
    # Объединяем с обратным знаком в экспоненте
    result = [0] * n
    for k in range(n // 2):
        omega = cmath.exp(2j * cmath.pi * k / n)  # Плюс вместо минуса!
        t = omega * a_odd[k]
        result[k] = a_even[k] + t
        result[k + n // 2] = a_even[k] - t
    
    return result

# Проверяем обратное преобразование
reconstructed = inverse_FFT(fft_result.tolist())
reconstructed = np.array(reconstructed) / N  # Нормировка

print("\n" + "=" * 60)
print("ПРОВЕРКА ОБРАТНОГО ПРЕОБРАЗОВАНИЯ")
print("=" * 60)
print(f"Средняя ошибка восстановления: {np.mean(np.abs(signal - reconstructed.real)):.6f}")
print("(Должна быть близка к нулю)")

# ==================== 8. ПРОСТОЙ ПРИМЕР ФИЛЬТРАЦИИ ====================
print("\n" + "=" * 60)
print("ПРИМЕР ФИЛЬТРАЦИИ: УДАЛЕНИЕ ВЫСОКИХ ЧАСТОТ")
print("=" * 60)

# Копируем спектр
filtered_spectrum = fft_result.copy()

# Обнуляем высокие частоты (> 30 Гц)
for i in range(len(freqs)):
    if abs(freqs[i]) > 30:
        filtered_spectrum[i] = 0

# Обратное преобразование
filtered_signal = np.array(inverse_FFT(filtered_spectrum.tolist())).real / N

print("Удалены все частоты выше 30 Гц")
print(f"Оставшиеся частоты: 10 Гц ({amp1}) и 25 Гц ({amp2})")
print(f"Удаленная частота: 40 Гц ({amp3})")

# Визуализация фильтрации
fig2, axes2 = plt.subplots(1, 2, figsize=(12, 4))

axes2[0].plot(t, signal, 'b-', alpha=0.5, label='Исходный')
axes2[0].plot(t, filtered_signal, 'r-', linewidth=2, label='После фильтрации')
axes2[0].set_title('Сравнение до и после фильтрации')
axes2[0].set_xlabel('Время (с)')
axes2[0].set_ylabel('Амплитуда')
axes2[0].legend()
axes2[0].grid(True, alpha=0.3)

# Спектр после фильтрации
filtered_amplitudes = np.abs(filtered_spectrum)[positive_mask] / N * 2
axes2[1].stem(positive_freqs, filtered_amplitudes, basefmt=" ", use_line_collection=True)
axes2[1].set_title('Спектр после фильтрации (>30 Гц)')
axes2[1].set_xlabel('Частота (Гц)')
axes2[1].set_ylabel('Амплитуда')
axes2[1].set_xlim(0, 60)
axes2[1].axvline(x=30, color='r', linestyle='--', alpha=0.5, label='Граница фильтра')
axes2[1].legend()
axes2[1].grid(True, alpha=0.3)

plt.tight_layout()
plt.show()

print("\n" + "=" * 60)
print("ВЫВОДЫ:")
print("=" * 60)
print("1. FFT преобразует сигнал из временной области в частотную")
print("2. Результат - массив комплексных чисел, где каждый элемент")
print("   соответствует определенной частоте")
print("3. Амплитуда показывает 'силу' частоты, фаза - её сдвиг")
print("4. С FFT можно анализировать, фильтровать и обрабатывать сигналы")
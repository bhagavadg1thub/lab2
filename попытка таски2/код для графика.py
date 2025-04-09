import matplotlib.pyplot as plt
import numpy as np

def process_numbers(input_string):
    input_string = input_string.replace(',', '.')
    numbers = list(map(float, input_string.split()))
    return numbers

x_values = process_numbers('1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288')

y_values_1 = process_numbers('0 0 0 1 2 2 20 32 11 46 61 95 194 475 939 1767 2847 5576 11645 21050')
y_values_2 = process_numbers('0 0 0 0 0 0 1 2 4 27 17 34 134 271 438 728 954 2611 4788 7041')

plt.scatter(x_values, y_values_1, color='blue', label='push_times')
plt.scatter(x_values, y_values_2, color='red', label='poll_times')


plt.yscale('log')
plt.xscale('log')
plt.xlabel('Ось N')
plt.ylabel('Ось t')
plt.title('Сравнение push_times и poll_times')
plt.legend()
plt.grid(True)

plt.show()

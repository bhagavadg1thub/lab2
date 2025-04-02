import matplotlib.pyplot as plt
import numpy as np

def process_numbers(input_string):
    input_string = input_string.replace(',', '.')
    numbers = list(map(float, input_string.split()))
    return numbers

x_values = ([100.0, 200.0, 400.0, 800.0, 1600.0, 3200.0, 6400.0, 12800.0, 25600.0, 51200.0, 102400.0, 204800.0, 409600.0, 819200.0])

y_values_1 = process_numbers('158 173 557 833 2418 5841 15059 67038 125578 511907 2205717 8676353 115246079 731933449')
y_values_2 = process_numbers('25 24 92 87 349 669 1174 1890 4999 15298 32686 101113 1282755 7008385')
y_values_3 = process_numbers('47 42 89 92 291 584 739 1327 2623 6504 14066 26989 49444 99616')

plt.scatter(x_values, y_values_1, color='blue', label='График Метод1')
plt.scatter(x_values, y_values_2, color='red', label='График Метод2')
plt.scatter(x_values, y_values_3, color='green', label='График Метод3')

plt.yscale('log') # логарифмическая шкала по y 
plt.xscale('log') # логарифмическая шкала по x


plt.xlabel('Ось N')
plt.ylabel('Ось t')
plt.title('Сравнение методов 1-3')
plt.legend()
plt.grid(True)

plt.show()

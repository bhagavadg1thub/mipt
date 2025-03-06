import matplotlib.pyplot as plt
import numpy as np

def process_numbers(input_string):
    input_string = input_string.replace(',', '.')
    numbers = list(map(float, input_string.split()))
    return numbers

x_values = np.arange(100, 1000000, 33330)

input_string1 = input()
y_values_1 = process_numbers(input_string1)

input_string2 = input()
y_values_2 = process_numbers(input_string2)

plt.scatter(x_values, y_values_1, color='blue', label='График linearSearch')
plt.scatter(x_values, y_values_2, color='red', label='График binarySearch')

plt.xlabel('Ось N')
plt.ylabel('Ось t, мс*10е6')
plt.title('Сравнение linearSearch и binarySearch')
plt.legend()
plt.grid(True)

plt.show()

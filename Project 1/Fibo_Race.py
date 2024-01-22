# Elias Woldie
# Class (CECS 342-07)
# Project Name (Prog 1 – Fibonacci Race)
# 09/12/2023

#  I certify that this program is my own original work. I did not copy any part of this program from
# any other source. I further certify that I typed each and every line of code in this program.

import time


def fibonacci(n):
    if n <= 1:
        return n
    return fibonacci(n-1) + fibonacci(n-2)


n = 51
numbers = list(range(n))
fib_results = []
times_python = []

print(f"{'Number':<10}{'Fibonacci Value':<20}{'Time (seconds)':<15}")
print("-" * 45)

for i in numbers:
    start_time = time.time()
    result = fibonacci(i)
    fib_results.append(result)
    end_time = time.time()
    elapsed_time = end_time - start_time
    times_python.append(elapsed_time)
    print(f"{i:<10}{result:<20}{elapsed_time:.2f}")

with open('python_data.txt', 'w') as f:
    f.write("Number\tFibonacci Value\tTime (seconds)\n")
    for i, result, elapsed_time in zip(numbers, fib_results, times_python):
        f.write(f"{i}\t{result}\t{elapsed_time:.2f}\n")

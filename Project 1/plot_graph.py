import os
import matplotlib.pyplot as plt


def read_data_from_file(filename):
    with open(filename, 'r') as f:
        lines = f.readlines()[1:]  # Skip header line
        numbers, fib_results, times = [], [], []
        for line in lines:
            # Remove empty strings after splitting by any whitespace
            data = list(filter(None, line.strip().split()))
            
            # If data doesn't contain the expected 3 values, skip processing this line
            if len(data) != 3:
                continue
            
            num, fib, time_taken = data
            numbers.append(int(num))
            fib_results.append(int(fib))
            times.append(float(time_taken))
        return numbers, fib_results, times



# Change the directory to where the data files are located
os.chdir('/Users/eliaswoldie/Desktop/CS/Python/CECS 342/Project 1/')

# Read data from the two files
cpp_numbers, cpp_fibs, cpp_times = read_data_from_file('cpp_data.txt')
py_numbers, py_fibs, py_times = read_data_from_file('python_data.txt')

# Plot the data on a single graph
plt.figure(figsize=(12, 5))

plt.plot(py_numbers, py_times, 'o-', label='Python Time Taken (seconds)')
# Swapped 'o-' with 's-'
plt.plot(cpp_numbers, cpp_times, 's-', label='C++ Time Taken (seconds)')

# Set xticks for every number
plt.xticks(range(max(py_numbers) + 1))


plt.xlabel('Number')
plt.ylabel('Time Taken (seconds)')
plt.title('Time Taken for Fibonacci Calculation (C++ vs. Python)')
plt.legend()

plt.tight_layout()
plt.show()

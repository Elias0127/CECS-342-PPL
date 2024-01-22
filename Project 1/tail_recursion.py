
def fibonacci(n):
    def fib_tail(n, a, b):
        if n == 0:
            return a
        else:
            return fib_tail(n - 1, b, a + b)

    return fib_tail(n, 0, 1)

print(fibonacci(200))  
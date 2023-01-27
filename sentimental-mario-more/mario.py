from cs50 import get_int

n = get_int("Height: ")
k = 1
# this governs inputs that are outside of the specified range


if n > 8 or n < 1:
    print("Invalid input. Please enter a height between 1 and 8.")
    n = get_int("Height: ")
    # this governs inputs that are outside of the specified range

for i in range(n):
    print(" " * (n - k), end="")
    print("#" * k, end="")
    print("  ", end="")
    print("#" * k)
    k = k + 1
    # this governs inputs that are outside of the specified range

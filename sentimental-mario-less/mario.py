from cs50 import get_int

n = get_int("Height: ")
if n == 1:
    k = 0
elif n > 1:
    k = 1
    # this governs the input parameters of entry; if a 1 is entered or otherwise

if n > 8 or n < 1:
    print("Invalid input. Please enter a height between 1 and 8.")
    n = get_int("Height: ")
    # this governs inputs that are outside of the specified range

while n <= 8 and k < n:
    if k == 0:
        print("#")
        k = k + 1
        # this is for that bullshit situation where the height of the pyramid is 1

    elif k == 1:
        for i in range(n):
            print(" " * (n - k), end="")
            print("#" * k)
            k = k + 1
            # this governs the situation where the height of the pyramid is anything other than 1

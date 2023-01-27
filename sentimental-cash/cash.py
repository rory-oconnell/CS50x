from cs50 import get_float

# This function calculates the amount of quarters owed.


def calculate_quarters(coins):
    quarters = 0
    while coins >= 0.25:
        coins = coins - 0.25
        coins = round(float(coins), 2)
        quarters = quarters + 1
    return quarters

# This function calculates the amount of dimes owed.


def calculate_dimes(coins):
    dimes = 0
    while coins >= 0.10:
        coins = coins - 0.10
        coins = round(float(coins), 2)
        dimes = dimes + 1
    return dimes

# This function calculates the amount of nickles owed.


def calculate_nickles(coins):
    nickles = 0
    while coins >= 0.05:
        coins = coins - 0.05
        coins = round(float(coins), 2)
        nickles = nickles + 1
    return nickles

# This is the main function. It is the main program, and is defined as the usage of all of the functions described above.


def main():

    coins = get_float("Change owed: ")

    while coins < 0:
        print("Please enter a valid number")
        coins = get_float("Change owed: ")

    quarters = calculate_quarters(coins)
    coins = coins - (quarters * 0.25)

    # This goddamn function needs to be enacted multiple times in the program in order to keep the floats in order

    coins = round(float(coins), 2)
    dimes = calculate_dimes(coins)
    coins = coins - (dimes * 0.10)

    # This goddamn function needs to be enacted multiple times in the program in order to keep the floats in order

    coins = round(float(coins), 2)
    nickles = calculate_nickles(coins)
    coins = coins - (nickles * 0.05)

    # This goddamn function needs to be enacted multiple times in the program in order to keep the floats in order

    coins = round(float(coins), 2)
    pennies = coins / 0.01
    coins_owed = quarters + dimes + nickles + pennies
    print(coins_owed)


# The main function is enacted here
main()

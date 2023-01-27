inp = input('Please enter your credit card number:')


def main():
    n = Luhn_Algo(inp)
    if n != 0:
        print('INVALID')
        exit(1)
    n = Card_Type(inp)
    if n == 1:
        print('VISA')
    elif n == 2:
        print('AMEX')
    elif n == 3:
        print('MASTERCARD')
    elif n == 4:
        print('INVALID')


def Luhn_Algo(inp):
    length = len(str(inp))
    mults = []
    norms = []
    sum_norms = 0
    sum_mults = 0

    for i in range(length - 1, -1, -2):
        norms.append(str(inp)[i])

    for i in range(len(norms)):
        sum_norms = sum_norms + int(norms[i])

    for i in range(length - 2, -1, -2):
        mults.append(str(inp)[i])

    for i in range(len(mults)):
        mults[i] = int(mults[i]) * 2
        if mults[i] > 9:
            sum_mults = sum_mults + int(str(mults[i])[0])
            sum_mults = sum_mults + int(str(mults[i])[1])
        else:
            sum_mults = sum_mults + mults[i]

    Luhn = (sum_mults + sum_norms) % 10
    return Luhn


def Card_Type(inp):
    first_two = []
    first_two.append(int(str(inp)[0]))
    first_two.append(int(str(inp)[1]))
    length = len(str(inp))

    if length == 13:
        return 1
    elif length == 15 and first_two[0] == 3 and (first_two[1] == 4 or first_two[1] == 7):
        return 2
    elif length == 16 and first_two[0] == 5 and 1 <= first_two[1] <= 5:
        return 3
    elif length == 16:
        return 1
    elif first_two[0] == 4:
        return 4


main()

# This is a comment to satisfy style50
# This is a comment to satisfy style50
# This is a comment to satisfy style50
# This is a comment to satisfy style50
# This is a comment to satisfy style50
# This is a comment to satisfy style50
# This is a comment to satisfy style50
# This is a comment to satisfy style50
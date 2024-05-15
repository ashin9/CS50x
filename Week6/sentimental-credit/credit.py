from cs50 import get_string


def main():
    while True:
        n = get_string("Number: ")
        if int(n) > 0:
            break

    result = whichone(n)
    print(result)


def whichone(n):
    if len(n) == 15 and check(n):
        if n[:2] == "34" or n[:2] == "37":
            return "AMEX"

    elif len(n) == 16 and check(n):
        if n[:2] == "51" or n[:2] == "51" or n[:2] == "53" or n[:2] == "54" or n[:2] == "55":
            return "MASTERCARD"
        if n[:1] == "4":
            return "VISA"

    elif len(n) == 13 and check(n):
        if n[:1] == "4":
            return "VISA"

    return "INVALID"


def check(n):
    sum = 0
    for i in n[-2::-2]:
        sum += ((int(i) * 2) % 10)        # 取个位
        sum += ((int(i) * 2) // 10) % 10  # 取十位
        # print(i)
    for i in n[-1::-2]:
        sum += int(i)
        # print(i)

    # print(sum)
    if sum % 10 == 0:
        return True
    return False


if __name__ == "__main__":
    main()

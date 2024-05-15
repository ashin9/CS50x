while True:
    h = input("height: ")
    if h.isdigit():
        h = int(h)
        if h > 0 and h < 9:
            break

for row in range(h):
    for _ in range(h-(row+1)):
        print(" ", end="")
    for _ in range(row+1):
        print("#", end="")

    print("  ", end="")

    for _ in range(row+1):
        print("#", end="")

    print()

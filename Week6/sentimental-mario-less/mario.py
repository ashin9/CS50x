
while True:
    height = input("Height: ")
    if height.isdigit():
        height = int(height)
        if height > 0 and height < 9:
            break

for row in range(height):
    for i in range(height-(row+1)):
        print(" ", end="")
    for i in range(row+1):
        print("#", end="")
    print()

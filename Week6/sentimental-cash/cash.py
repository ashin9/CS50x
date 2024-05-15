from cs50 import get_float

while True:
    change = get_float("Change: ")
    if change > 0:
        break

n = 0

while change > 0.249:
    change -= 0.25
    n += 1
    # print(change)
while change > 0.09:
    change -= 0.1
    n += 1
    # print(change)
while change > 0.049:
    change -= 0.05
    n += 1
    # print(change)
while change > 0.009:
    change -= 0.01
    n += 1
    # print(change)

print(n)

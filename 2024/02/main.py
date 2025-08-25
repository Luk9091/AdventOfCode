from colorama import Fore, Back, Style


# path = "example.txt"
path = "input.txt"
sep_char = ' '

with open(path) as f:
    data = f.read().splitlines()



def sign(x):
    if x > 0:
        return 1
    elif x < 0:
        return -1
    else:
        return 0



def checkSlope(numbers: list, failed = 0) -> bool:
    difference = int(numbers[1]) - int(numbers[0])
    signed = sign(difference)

    i = 0
    for _  in range(1, len(numbers)):
        i += 1
        difference = int(numbers[i]) - int(numbers[i-1])
        if abs(difference) > 3 or difference == 0:
            failed += 1
            if failed > 1:
                return False

            numbers.pop(i)
            i -= 1
            continue

        if (sign(difference) != signed):
            failed += 1
            if failed > 1:
                return False

            numbers.pop(i)
            i -= 1
            continue
        signed = sign(difference)

    return True



save = 0
for line in data:
    numbers = line.split(sep_char)

    if not checkSlope(numbers.copy()):
        if not checkSlope((numbers[1:]).copy(), 1):
            print(f"{Fore.RED}NOT{Fore.RESET}\t{numbers}")
            checkSlope(numbers.copy())
            continue

    save += 1
    print(f"{Fore.GREEN} OK{Fore.RESET}\t{numbers}")


print(save)
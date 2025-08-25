import re

# path = "example.txt"
# path = "example2.txt"
path = "input.txt"

def getNumbers(string: str) -> list[int, int]:
    string = string.replace("mul(", "")[:-1]
    return list(map(int, string.split(",")))



with open(path, 'r') as file:
    data = file.read()

# pattern_1 = r"mul\([0-9]{1,},[0-9]{1,}\)"
pattern_2 = r"mul\([0-9]{1,},[0-9]{1,}\)|don't\(\)|do\(\)"
out = re.findall(pattern_2, data)

def first(out):
    numbers = []
    sumOf = 0
    for inst in out:
        number = getNumbers(inst)
        numbers.append(number)
        sumOf += number[0] * number[1]

    print(out)
    print(numbers)
    print(f"Sum: {sumOf}")

def second(out):
    numbers = []
    sumOf = 0
    use = True

    for inst in out:
        if "do()" in inst:
            use = True
        elif "don't()" in inst:
            use = False
        elif use:
            number = getNumbers(inst)
            numbers.append(number)
            sumOf += number[0] * number[1]

    print(out)
    print(numbers)
    print(f"Sum: {sumOf}")



# first(out)
second(out)
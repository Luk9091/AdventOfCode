import pandas as pd

# path = "example.txt"
path = "input.txt"

data = pd.read_csv(path, sep='   ', header=None, names=["left", "right"], engine='python')


length = len(data)
# print(data)
# print(length)
left = data["left"]
right = data["right"]



def minDiff(left, right):
    sum = 0
    for i in range(length):
        l = min(left)
        r = min(right)

        diff = (l - r)
        if (diff < 0):
            diff = r - l
        sum += diff
        left = left.drop(left.idxmin())
        right = right.drop(right.idxmin())

    print(sum)

def histogram(left, right):
    hist = {}

    for i in range(len(left)):
        if not left[i] in hist.keys():
            hist[left[i]] = [0, 0]

        hist[left[i]][0] += 1

    for i in range(len(right)):
        if not right[i] in hist.keys():
            continue

        hist[right[i]][1] += 1

    sumOf = 0
    for key in hist.keys():
        sumOf += hist[key][0] * hist[key][1] * key
    print(hist)
    print(f"sum: {sumOf}")


# minDiff(left, right)
histogram(left, right)
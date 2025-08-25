import numpy as np
# Example
# Time     = [7,  15,   30]
# Distance = [9,  40,  200]

# Input
# Time        = [56,     97,     77,     93]
# Distance    = [499,   2210,   1097,   1440]

# Input 2
Time        = [56977793]
Distance    = [499221010971440]

combinations = [0] * len(Time)
numOfCombinations = 0
def mux(values):
    ret = 1
    for value in values:
        ret *= value
    return ret


for i in range(len(Time)):
    for pressTime in range(int(np.ceil(Time[i]))):
        reachDistance = (Time[i] - pressTime) * pressTime

        if reachDistance >= Distance[i]:
            # combinations[i] += 1
            # print(f"{pressTime}: {reachDistance}")
            numOfCombinations += 1

    
    # combinations[i] = combinations[i] * 2
    # if pressTime % 2 == 0:
    #     combinations[i] -= 1
    print("#"*30)

# print(combinations)
# print(mux(combinations))
print(numOfCombinations)


    

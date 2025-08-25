from enum import Enum

import numpy as np
from scipy.optimize import curve_fit

# INPUT_FILE = "examples.txt"
INPUT_FILE = "input.txt"

class STATE(Enum):
    SEED = 0
    SOLID = 1
    FERTILIZE = 2
    WATER = 3
    LIGHT = 4
    TEMPERATURE = 5
    HUMIDITY = 6
    LOCATION = 7

    def __iter__(self):
        return self
    def __next__(self):
        value = self.value + 1

        if value > 7:
            value = 0
        
        return STATE(value)



state = STATE.SEED

seeds = []
toSolid = {"start": [], "destination": [], "range": []}
toFertilize = {"start": [], "destination": [], "range": []}
toWater = {"start": [], "destination": [], "range": []}
toLight = {"start": [], "destination": [], "range": []}
toTemperature = {"start": [], "destination": [], "range": []}
toHumidity = {"start": [], "destination": [], "range": []}
toLocation = {"start": [], "destination": [], "range": []}
locations = []
location = 2**32


FILL_DICT = {
    STATE.SOLID:        toSolid,
    STATE.FERTILIZE:    toFertilize,
    STATE.WATER:        toWater,
    STATE.LIGHT:        toLight,
    STATE.TEMPERATURE:  toTemperature,
    STATE.HUMIDITY:     toHumidity,
    STATE.LOCATION:     toLocation,
}
    



def findSeed(line: str):
    line = line.strip("seeds: ")
    seed = line.split(" ")
    
    for i, value in enumerate(seed):
        seed[i] = int(value)
    return seed

def findSeed(line: str):
    line = line.strip("seeds: ")
    seed = line.split(" ")
    
    for i, value in enumerate(seed):
        seed[i] = int(value)
    return seed

def findRange(line: str, dict: dict[list[int], list[int], list[int]]):
    if line[0].isdigit():
        line = line.split(" ")

        dict["start"].append(int(line[1]))
        dict["destination"].append(int(line[0]))
        dict["range"].append(int(line[2]))
    
    return dict

def fromTo(value, dictionary):
    start = dictionary["start"]
    destination = dictionary["destination"]
    span = dictionary["range"]

    for i in range(len(start)):
        if start[i] <= value and value < start[i] + span[i]:
            delta = start[i] - value
            value = destination[i] - delta
            break

    return value



with open(INPUT_FILE, "r") as file:
    for line in file:
        if line == "\n":
            state = next(state)
            continue

        line = line.strip("\n")
        
        if state is STATE.SEED:
            seeds = findSeed(line)
        else:
            FILL_DICT[state] = findRange(line, FILL_DICT[state])


## Part one
# for seed in seeds:
#     nextValue = seed
#     state = STATE.SOLID
#     for _ in range(1, 8):
#         nextValue = fromTo(nextValue, FILL_DICT[state])
#         state = next(state)
#         # print(state.name, seed, nextValue)
#     # print("#"*30)
#     if nextValue < location:
#         location = nextValue
#     print(seed, nextValue)
# print(seeds)

# Part two -- brute force
# for i in range(0, len(seeds), 2):
#     seed = seeds[i]
#     inRange = seeds[i+1]
#     for j in range(inRange):
#         nextValue = seed + j
#         state = STATE.SOLID
#         for _ in range(1, 8):
#             nextValue = fromTo(nextValue, FILL_DICT[state])
#             state = next(state)
#             print(state.name, seed+j, nextValue)
#         print(seed+j, nextValue)
#         print("#"*30)
#         if nextValue < location:
#             location = nextValue
# exit()




## Part two -- split input in ranges
inputSeeds = {"start": [], "destination": [], "range": []}

def findSmallRanges(start, inRange):
    minRange = inRange
    nextValue = start

    for state in STATE:
        if state is STATE.SEED:
            continue

        for i in range(len(FILL_DICT[state]["start"])):
            if FILL_DICT[state]["start"][i] <= nextValue and nextValue < FILL_DICT[state]["start"][i] + FILL_DICT[state]["range"][i]:
                ceilOfMap = FILL_DICT[state]["start"][i] + FILL_DICT[state]["range"][i]

                upperLim = ceilOfMap - nextValue
                if upperLim < minRange:
                    minRange = upperLim
                

                ceilOfValue = nextValue + minRange
                if ceilOfValue >= ceilOfMap:
                    diff = ceilOfValue - ceilOfMap
                    minRange = minRange - diff
                    if minRange > 1:
                        minRange -= 1


                delta = FILL_DICT[state]["start"][i] - nextValue
                nextValue = FILL_DICT[state]["destination"][i] - delta
                break

        # print(state.name, start, nextValue, minRange)
    return minRange

def findOut(start):
    value = 0
    for state in STATE:
        if state is STATE.SEED:
            value = start
            continue

        value = fromTo(value, FILL_DICT[state])

    return value



iteration = 0
for i in range(0, len(seeds), 2):
    seed = seeds[i]
    inRange = seeds[i+1]

    while True:
        iteration += 1
        minRange = findSmallRanges(seed, inRange)
        if inRange <= 0:
            break

        inputSeeds["start"].append(seed)
        inputSeeds["destination"].append(minRange)
        # print(seed, minRange)

        inRange = inRange - minRange
        seed = seed + minRange
# print(iteration)

for seed in inputSeeds["start"]:
    locations.append(findOut(seed))

print(locations)
print(min(locations))






        
# print(location)


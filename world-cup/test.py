# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000

# Ensure correct usage
if len(sys.argv) != 2:
    sys.exit("Usage: python tournament.py FILENAME")

#Read teams into memory from file
teams = []
filename = sys.argv[1]
with open(filename) as f:
    reader = csv.DictReader(f)
    for line in reader:
        # print(type(line["rating"]))
        line["rating"] = int(line["rating"])
        # print(type(line["rating"]))
        teams.append(line)

for i in range(len(teams)):
    print((teams[i])["team"])
    print((teams[i])["rating"])
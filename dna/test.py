import csv
import sys

# with open(sys.argv[1], "r") as file:
#     reader = csv.reader(file)
#     next(reader)
#     for row in reader:
#         print(row[1])

with open(sys.argv[1], "r") as file:
    reader = csv.DictReader(file)

    for row in reader:
        print(row["name"])
        print()

with open(sys.argv[1], "r") as file:
    reader = csv.DictReader(file)

    for row in reader:
        print(row["name"])

with open(sys.argv[1], "r") as file:
    reader = csv.DictReader(file)

    for row in reader:
        print(row["name"])
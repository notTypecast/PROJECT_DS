import csv
with open('../data/agn.us.txt', newline='') as csvfile:
  rd = csv.reader(csvfile, delimiter=",")
  dates = [x[0] for x in list(rd)[1:]]

def asciisum(datestr):
  return sum(ord(x) for x in datestr)

datemin = min(dates, key=asciisum)
datemax = max(dates, key=asciisum)

print("Minimum ASCII sum is:", str(asciisum(datemin)) + ", for date:", datemin)
print("Maximum ASCII sum is:", str(asciisum(datemax)) + ", for date:", datemax)
print("Range is:", asciisum(datemax) - (asciisum(datemin) - 1))
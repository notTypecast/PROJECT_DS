import csv
import matplotlib.pyplot as plt
import time
import datetime
from sys import argv

def getLineEq(p1, p2):
	m = (p2[1] - p1[1])/(p2[0] - p1[0])
	return m, p1[1] - m*p1[0]

# read all timestamps
timestamps = []
with open('gumbel.rnd.txt') as csv_file:
	csv_reader = csv.reader(csv_file, delimiter=',')
	line_count = 0
	for row in csv_reader:
		line_count += 1
		if line_count - 1 == 0:
			continue
		timestamps.append(int(time.mktime(datetime.datetime.strptime(row[0], "%Y-%m-%d").timetuple())))

# 1 entry per timestamp
xvals = range(len(timestamps))

TOTAL_TO_DISPLAY = len(timestamps) if len(argv) < 2 or not argv[1].isnumeric() else int(argv[1])
m, b = getLineEq((xvals[0], timestamps[0]), (xvals[-1], timestamps[-1]))

# actual data plot
plt.plot(xvals[:TOTAL_TO_DISPLAY], timestamps[:TOTAL_TO_DISPLAY], label = "Actual")
# expected plot, line between first and last entry
xExpected = xvals[0], TOTAL_TO_DISPLAY - 1
yExpected = m*xExpected[0] + b, m*xExpected[1] + b
plt.plot(xExpected, yExpected, label = "Expected linear")


plt.xlabel("Day")
plt.ylabel('Date')

plt.title('gumbel.rnd.txt')
  
# function to show the plot
plt.legend()
plt.show()
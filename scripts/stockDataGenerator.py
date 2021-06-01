from random import randint
from datetime import datetime
from numpy import random as nprnd

def dayTimestampToDate(dts):
	return 	datetime.fromtimestamp((dts+0.5)*86400).strftime('%Y-%m-%d')


mean = 15133
std_dev = 10000

lines = ["Date,Open,High,Low,Close,Volume,OpenInt\n"]

total = 300000


allTimestamps = nprnd.gumbel(loc = mean, scale = std_dev, size = (1, total))[0]
allTimestamps = list(set([int(x) for x in allTimestamps]))

template = "{},{},{},{},{},{},{}\n"

allTimestamps.sort()

for timestamp in allTimestamps:
	lines.append(template.format(dayTimestampToDate(timestamp), 0, 0, 0, 0, randint(0, 294967295), 0))

with open("gumbel.rnd.txt", "w") as f:
	f.writelines(lines)

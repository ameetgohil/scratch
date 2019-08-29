import re
import matplotlib.pyplot as plt
import numpy as np

y_data = []
with open("ping_output.txt", "r") as f:
    line = f.readline()
    while line:
        #print(line)
        seq_finder = re.compile('icmp_seq=(\d+).*\n')
        y_data.append(int(seq_finder.findall(line)[0]))
        line = f.readline()
    
#print(y_data)

plt.plot(np.diff(y_data))
plt.ylabel('icmp_seq')
plt.show()

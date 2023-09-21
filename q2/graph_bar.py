
import matplotlib.pyplot as plt
data = []
with open("RESULT.txt","r") as f:
    for i in range(3):
        x=float(f.readline())
        data.append(x)
labels = ['FIFO', 'RR', 'OTHER']
colors=["springgreen","mediumpurple","lightcoral"]
plt.bar(labels, data,color=colors)

plt.xlabel('PROCESSES')
plt.ylabel('TIME')
plt.title('Bar Graph of execution time of three processes')
plt.show()

import matplotlib.pyplot as plt
data=[]
with open("RESULT.txt","r") as f:
    for i in range(3):
        x=float(f.readline())
        data.append(x)
plt.hist(data, color='orange',alpha=0.4, edgecolor='black')
plt.xlabel('TIME')
plt.ylabel('FREQUENCY')
plt.title('Histogram of Time taken by 3 processes')
plt.show()

import matplotlib.pyplot as plt #import plot function as plt for plotting the graph

#input the data 
log2n = [13.2877, 16.6096, 19.9316, 23.2535]
data = [10000, 100000, 1000000, 10000000]

#setting xaxis and yaxis
plt.plot(data, log2n)
plt.title('data vs logN')
plt.xlabel('data')
plt.ylabel('logN')

plt.show() #show the plot
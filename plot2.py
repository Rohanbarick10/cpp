import matplotlib.pyplot as plt

# Given data
data = [10000, 100000, 1000000, 10000000]
fibo_time = [156, 333, 468, 625]
binary_S_Time = [156, 170, 156, 468]

# Create the figure and the first axis
fig, ax1 = plt.subplots()

# Plot the Fibonacci search times on the first y-axis
ax1.plot(data, fibo_time, 'b-', marker='o', label='Fibonacci Search Time')
ax1.set_xlabel('Data Size (n)')
ax1.set_ylabel('Fibonacci Search Time (ns)', color='b')
ax1.tick_params('y', colors='b')

# Create a second y-axis sharing the same x-axis for binary search times
ax2 = ax1.twinx()
ax2.plot(data, binary_S_Time, 'r--', marker='x', label='Binary Search Time')
ax2.set_ylabel('Binary Search Time (ns)', color='r')
ax2.tick_params('y', colors='r')

# Add a title and show the plot
plt.title('Comparison of Binary Search and Fibonacci Search Times (Worst Case)')
fig.tight_layout()  # Adjust layout to prevent overlap
plt.show()

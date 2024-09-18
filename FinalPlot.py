import matplotlib.pyplot as plt

# Data
xlabel = [10000, 100000, 1000000, 10000000]
ylabel1 = [73, 97, 116, 131]  # Binary Search
ylabel2 = [130, 163, 198, 233]  # Fibonacci Search

# Plot
plt.figure(figsize=(10, 6))
plt.plot(xlabel, ylabel1, marker='o', label='Binary Search')
plt.plot(xlabel, ylabel2, marker='o', label='Fibonacci Search')

# Labels and Title
plt.xlabel('Dataset Size')
plt.ylabel('Running Time (ns)')
plt.title('Search Algorithm Performance Comparison(Worst Case)')
plt.xscale('log')  # Using log scale for better visualization
plt.yscale('log')  # Optional: if running time spans a large range
plt.legend()
plt.grid(True, which='both', linestyle='--', linewidth=0.5)

# Show Plot
plt.show()

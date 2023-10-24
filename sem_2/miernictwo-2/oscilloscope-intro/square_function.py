# import matplotlib.pyplot as plt
# import numpy as np

# # Create x values from 0 to 1 millisecond
# x = np.linspace(0, 1e-3, 1000)

# # Calculate y values for the square wave function with an offset of -1V, amplitude of 520mV, and frequency of 5kHz
# offset = -1
# amplitude = 260e-3  # half of the peak-to-peak amplitude
# frequency = 5e3
# y = offset + amplitude * np.sign(np.sin(2 * np.pi * frequency * x))


# # Plot the square wave function
# plt.plot(x, y)

# # Add labels and a title to the plot

# plt.xlabel('T [s]')
# plt.ylabel('U [V]')
# plt.title('Square Wave Function')


# # Display the plot
# plt.show()

import matplotlib.pyplot as plt
import numpy as np

# Create x values from 0 to 200 microseconds
x = np.linspace(-600, 600, 1000)

# Calculate y values for the square wave function with an offset of -1V, amplitude peak-to-peak of 520mV, and frequency of 5kHz
offset = -1
amplitude = 260e-3  # half of the peak-to-peak amplitude
frequency = 5e3
y = offset + amplitude * np.sign(np.sin(2 * np.pi * frequency * x * 1e-6))

# Set the first square to end at zero

# Plot the square wave function
plt.plot(x, y)

# Add labels and a title to the plot
plt.xlabel('T ($\mu$s)')
plt.ylabel('U (V)')

plt.xlim(-600, 600)
plt.ylim(-1.5, 1)
plt.grid()
# Display the plot
plt.show()

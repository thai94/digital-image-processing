import numpy as np
import scipy.signal as sig
import cv2
import matplotlib.pyplot as plt


img = cv2.imread("image_0033.jpg")
img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# Define the Sobel operator kernels.
kernel_x = np.array([[-1, 0, 1],[-2, 0, 2],[-1, 0, 1]])
kernel_y = np.array([[1, 2, 1], [0, 0, 0], [-1, -2, -1]])

G_x = sig.convolve2d(img, kernel_x, mode='same')
G_y = sig.convolve2d(img, kernel_y, mode='same')
# G_x = cv2.Sobel(img, cv2.CV_32F, 1, 0, ksize=1)
# G_y = cv2.Sobel(img, cv2.CV_32F, 0, 1, ksize=1)

# Plot them!
ax1 = plt.subplot(1, 2, 1)
ax2 = plt.subplot(1, 2, 2)

# Actually plt.imshow() can handle the value scale well even if I don't do 
# the transformation (G_x + 255) / 2.
ax1.imshow(G_x, cmap='gray'); ax1.set_xlabel("Gx")
ax2.imshow(G_y, cmap='gray'); ax2.set_xlabel("Gy")
plt.show()
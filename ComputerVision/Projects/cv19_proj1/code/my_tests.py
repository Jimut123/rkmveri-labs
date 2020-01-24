import cv2
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
from utils import vis_hybrid_image, load_image, save_image
from student_code import my_imfilter, create_hybrid_image

image1 = load_image('../data/dog.bmp')
image2 = load_image('../data/cat.bmp')
plt.figure(figsize=(3,3)); plt.imshow((image1*255).astype(np.uint8));
plt.figure(figsize=(3,3)); plt.imshow((image2*255).astype(np.uint8));

cutoff_frequency = 7
filter = cv2.getGaussianKernel(ksize=cutoff_frequency*4+1,
                               sigma=cutoff_frequency)
filter = np.dot(filter, filter.T)
# let's take a look at the filter!
plt.figure(figsize=(4,4)); plt.imshow(filter);

blurry_dog = my_imfilter(image1, filter)




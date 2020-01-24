import numpy as np
#### DO NOT IMPORT cv2 

def rgb2gray(rgb):
    return np.dot(rgb[...,:3], [0.2989, 0.5870, 0.1140])

def my_imfilter(image, filter):
  """
  Apply a filter to an image. Return the filtered image.

  Args
  - image: numpy nd-array of dim (m, n, c)
  - filter: numpy nd-array of dim (k, k)
  Returns
  - filtered_image: numpy nd-array of dim (m, n, c)

  HINTS:
  - You may not use any libraries that do the work for you. Using numpy to work
   with matrices is fine and encouraged. Using opencv or similar to do the
   filtering for you is not allowed.
  - I encourage you to try implementing this naively first, just be aware that
   it may take an absurdly long time to run. You will need to get a function
   that takes a reasonable amount of time to run so that I can verify
   your code works.
  - Remember these are RGB images, accounting for the final image dimension.
  """

  assert filter.shape[0] % 2 == 1
  assert filter.shape[1] % 2 == 1

  ############################
  ### TODO: YOUR CODE HERE ###

  # grab the spatial dimensions of the image, along with
  # the spatial dimensions of the kernel

  #print(image.shape)
  #print(filter.shape)

  (iH, iW) = image.shape[:2]
  (kH, kW) = filter.shape[:2]
  #print(iH," ",iW)
  filtered_image = np.zeros((iH, iW), dtype="float32")

  # allocate memory for the output image, taking care to
  # "pad" the borders of the input image so the spatial
  # size (i.e., width and height) are not reduced
  pad = (kW - 1) // 2
  #print("pad = ",pad)
  
  image1 = rgb2gray(image)
  #print(image1.shape)
  image2 = np.pad(image1, pad_width=pad, mode='constant', constant_values=0)
  #print(x[0:10,0:10])
  # for y in np.arange(pad, iH + pad):
  #   print(image1[y-pad,0])
  #   #  print("yikes")
  
  # loop over the input image, "sliding" the kernel across
  # each (x, y)-coordinate from left-to-right and top to
  # bottom
  
  for y in np.arange(pad, iH + pad):
    for x in np.arange(pad, iW + pad):
      # extract the ROI of the image by extracting the
      # *center* region of the current (x, y)-coordinates
      # dimensions
      roi = image2[y - pad:y + pad+1, x - pad:x + pad+1]

      # perform the actual convolution by taking the
      # element-wise multiplicate between the ROI and
      # the kernel, then summing the matrix
      #print("roi = ",roi," filter = ",filter)
      
      k = (roi * filter).sum()
      # k = np.dot(roi*filter).sum()
      # store the convolved value in the output (x,y)-
      # coordinate of the output image
     
      filtered_image[y - pad, x - pad] = k
  
  ### END OF STUDENT CODE ####
  ############################
  
  return filtered_image

def create_hybrid_image(image1, image2, filter):
  """
  Takes two images and creates a hybrid image. Returns the low
  frequency content of image1, the high frequency content of
  image 2, and the hybrid image.

  Args
  - image1: numpy nd-array of dim (m, n, c)
  - image2: numpy nd-array of dim (m, n, c)
  Returns
  - low_frequencies: numpy nd-array of dim (m, n, c)
  - high_frequencies: numpy nd-array of dim (m, n, c)
  - hybrid_image: numpy nd-array of dim (m, n, c)

  HINTS:
  - You will use your my_imfilter function in this function.
  - You can get just the high frequency content of an image by removing its low
    frequency content. Think about how to do this in mathematical terms.
  - Don't forget to make sure the pixel values are >= 0 and <= 1. This is known
    as 'clipping'.
  - If you want to use images with different dimensions, you should resize them
    in the notebook code.
  """

  assert image1.shape[0] == image2.shape[0]
  assert image1.shape[1] == image2.shape[1]
  assert image1.shape[2] == image2.shape[2]

  ############################
  ### TODO: YOUR CODE HERE ###
  

  ### END OF STUDENT CODE ####
  ############################

  return low_frequencies, high_frequencies, hybrid_image

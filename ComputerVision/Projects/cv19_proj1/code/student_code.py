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

  filtered_image = image.copy()                          # copying the filtered image
  image_dimension=image.shape                            # capturing the shape of the image
  filter_dimension=filter.shape                          # capturing the shape of the filter
  height=image_dimension[0]                              # x
  width=image_dimension[1]                               # y
  flt_dim1=filter_dimension[0]                           # x   works for non-square filters
  flt_dim2=filter_dimension[1]                           # y   works for non-square filters
  pad_height=int((flt_dim1-1)/2)                         # estimating the size of the padding of height with the help of filter
  pad_width=int((flt_dim2-1)/2)                          # estimating the size of the padding of width with the help of filter
  pad_mat=np.zeros((height+2*pad_height,width+2*pad_width,3))
  # this part of code creates the image inside the padded version of the numpy zero matrix
  pad_mat[pad_height: height + pad_height, pad_width: width + pad_width] = image
  for d in range(len(image[0][0])):                       # going through all the channels of the images in the case if it is not in grayscale
      for i in range(len(image)):                         # x value iteration or height
          for j in range(len(image[0])):                  # y value or width
              # now using the padded 3D numpy array or 1D array as the case may be, we apply gaussian blur.
              filtered_image[i][j][d] = sum(sum(np.multiply(filter,pad_mat[i:i+flt_dim1,j:j+flt_dim2,d])))
  
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
  # low_fc_im1 = 
  # high_fc_im2 = 

  ### END OF STUDENT CODE ####
  ############################

  return low_frequencies, high_frequencies, hybrid_image

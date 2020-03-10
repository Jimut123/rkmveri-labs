import numpy as np
from matplotlib import pyplot as plt
import cv2 # You must not use cv2.cornerHarris()
# You must not add any other library


### If you need additional helper methods, add those. 
### Write details description of those

### Other codes given by guide

"""
  Returns the harris corners,  image derivative in X direction,  and 
  image derivative in Y direction.
  Args
  - image: numpy nd-array of dim (m, n, c)
  - window_size: The shape of the windows for harris corner is (window_size, wind)
  - alpha: used in calculating corner response function R
  - threshold: For accepting any point as a corner, the R value must be 
   greater then threshold * maximum R value. 
  - nms_size = non maximum suppression window size is (nms_size, nms_size) 
    around the corner
  Returns 
  - corners: the list of detected corners
  - Ix: image derivative in X direction
  - Iy: image derivative in Y direction

"""
def harris_corners(image, window_size=5, alpha=0.04, threshold=1e-2, nms_size=10):
    ### YOUR CODE HERE

    dy, dx = np.gradient(image)
    Ix = dx**2
    Iy = dy*dx
    Ixy = dy**2
    #Ix = cv2.Sobel(image,cv2.CV_64F,1,0,ksize=5)
    #Iy = cv2.Sobel(image,cv2.CV_64F,0,1,ksize=5)  
    #Ixy = cv2.Sobel(image,cv2.CV_64F,1,1,ksize=5) 
    fig = plt.figure(figsize=(10, 10))
    ax1 = fig.add_subplot(1,2,1)
    ax1.imshow(Ix[:,:,::-1])#,cmap='gray')
    plt.title("Image 1")
    plt.axis('off')
    ax2 = fig.add_subplot(1,2,2)
    ax2.imshow(Iy[:,:,::-1])#,cmap='gray')
    plt.title("Image 2")
    plt.axis('off')
    height = image.shape[0]
    width = image.shape[1]

    corners = []
    image2 = image.copy()
    color_img = image2#cv2.cvtColor(image2,cv2.COLOR_GRAY2RGB)
    padding = window_size/2

    for y in range(padding,height-padding):
      for x in range(padding,width-padding):
        windowIx2 = Ix[y-padding:y+padding+1, x-padding:x+padding+1]
        windowIxy = Ixy[y-padding:y+padding+1, x-padding:x+padding+1]
        windowIy2 = Iy[y-padding:y+padding+1, x-padding:x+padding+1]
        Sx2 = windowIx2.sum()
        Sxy = windowIxy.sum()
        Sy2 = windowIy2.sum()
        # response function
        det = (Sx2 * Sy2) - (Sxy ** 2)
        trace = Sx2 + Sy2
        r = det - alpha*(trace**2)

        #color if greater than threshold
        if r>threshold:
          corners.append([x,y,r])
          color_img.itemset((y, x, 0), 0)
          color_img.itemset((y, x, 1), 0)
          color_img.itemset((y, x, 2), 255)
    return corners, Ix, Iy

"""
  Creates key points form harris corners and returns the list of keypoints. 
  You must use cv2.KeyPoint() method. 
  Args
  - corners:  list of Normalized corners.  
  - Ix: image derivative in X direction
  - Iy: image derivative in Y direction
  - threshold: only select corners whose R value is greater than threshold
  
  Returns 
  - keypoints: list of cv2.KeyPoint
  
  Notes:
  You must use cv2.KeyPoint() method. You should also pass 
  angle of gradient at the corner. You can calculate this from Ix, and Iy 

"""
def get_keypoints(corners, Ix, Iy, threshold):
    
    ### YOUR CODE HERE

        
    return keypoints
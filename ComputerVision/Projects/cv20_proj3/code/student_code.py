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
    print("Starting Harris Corners...")
    img1_gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    img1_gray_blur = cv2.GaussianBlur(img1_gray,(5,5),0)
    Ix_ = cv2.Sobel(img1_gray_blur,cv2.CV_8U,1,0,ksize=3)
    Iy_ = cv2.Sobel(img1_gray_blur,cv2.CV_8U,0,1,ksize=3)  
    Ixy_ = Ix_*Iy_ 
    Ix = cv2.GaussianBlur(Ix_,(5,5),cv2.BORDER_DEFAULT) 
    Ix2 = Ix * Ix
    Iy = cv2.GaussianBlur(Iy_,(5,5),cv2.BORDER_DEFAULT) 
    Iy2 = Iy * Iy
    Ixy = cv2.GaussianBlur(Ixy_,(5,5),cv2.BORDER_DEFAULT) 
    height = image.shape[0]
    width = image.shape[1]
    window_size = 5
    image2 = image.copy()
    color_img = image2
    padding = int(window_size/2)
    Response_mat = np.full((height,width), 0,  dtype=np.float)
    for y in range(padding,height-padding):
        for x in range(padding,width-padding):
            windowIx2 = Ix2[y-padding:y+padding+1, x-padding:x+padding+1]
            windowIxy = Ixy[y-padding:y+padding+1, x-padding:x+padding+1]
            windowIy2 = Iy2[y-padding:y+padding+1, x-padding:x+padding+1]
            Sx2 = windowIx2.sum()
            Sxy = windowIxy.sum()
            Sy2 = windowIy2.sum()
            # response function
            det = (Sx2 * Sy2) - (Sxy ** 2)
            trace = Sx2 + Sy2
            r = det - alpha*(trace**2)
            if r>threshold:
                Response_mat[y][x] = 255
            else:
                Response_mat[y][x] = 0
    Backup_response = Response_mat.copy()  
    corners = []
    for y in range(int(nms_size/2),height-int(nms_size/2)):
        for x in range(int(nms_size/2),width-int(nms_size/2)):
            # perform NMS
            if Response_mat[y][x]==255:
                Response_mat[y-int(nms_size/2):y+int(nms_size/2),x-int(nms_size/2):x+int(nms_size/2)]=0
                Response_mat[y][x]=255
                corners.append([y,x])
            x=x+10
        y=y+10
    
    return corners, Ix_, Iy_

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
    keypoints = 'a'
    for item in corners:
      print(item[0],item[1])
    print("?")
    return keypoints

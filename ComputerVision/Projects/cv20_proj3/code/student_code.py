import numpy as np
from matplotlib import pyplot as plt
import cv2 # You must not use cv2.cornerHarris()
import math
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
    #img2_gray = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)
    Ix_ = cv2.Sobel(img1_gray_blur,cv2.CV_64F,1,0,ksize=3)
    Iy_ = cv2.Sobel(img1_gray_blur,cv2.CV_64F,0,1,ksize=3)  
    Ixy_ = Ix_*Iy_ #cv2.Sobel(img1_gray_blur,cv2.CV_64F,1,1,ksize=3) 
    Ix = cv2.GaussianBlur(Ix_,(5,5),cv2.BORDER_DEFAULT) 
    Ix2 = Ix * Ix
    Iy = cv2.GaussianBlur(Iy_,(5,5),cv2.BORDER_DEFAULT) 
    Iy2 = Iy * Iy
    Ixy = cv2.GaussianBlur(Ixy_,(5,5),cv2.BORDER_DEFAULT) 

    #img1_gray_blur
    fig = plt.figure(figsize=(5, 5))
    ax1 = fig.add_subplot(1,1,1)
    ax1.imshow(img1_gray_blur,cmap='gray')
    plt.title("img1_gray_blur")
    plt.axis('off')

    fig = plt.figure(figsize=(15, 15))
    ax1 = fig.add_subplot(1,3,1)
    ax1.imshow(Ix,cmap='gray')
    plt.title("Ix")
    plt.axis('off')
    ax2 = fig.add_subplot(1,3,2)
    ax2.imshow(Iy,cmap='gray')
    plt.title("Iy")
    plt.axis('off')
    ax3 = fig.add_subplot(1,3,3)
    ax3.imshow(Ixy,cmap='gray')
    plt.title("Ixy")
    plt.axis('off')

    height = image.shape[0]
    width = image.shape[1]
    window_size = 5
    corners = []
    image2 = image.copy()
    color_img = image2#cv2.cvtColor(image2,cv2.COLOR_GRAY2RGB)
    padding = int(window_size/2)
    threshold = 10**8
    alpha = 0.04
    max = 0
    total_r = 0
    count_r = 0
    wc = 0 # wild card
    Response_mat = np.full((height,width), 0,  dtype=np.float)
    NMS_mat = np.full((height,width), 0,  dtype=np.float)
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
            Response_mat[y][x] = r
    Response_mat = np.clip(Response_mat, -255.0, 255.0)
    Backup_response = Response_mat.copy()    
    fig = plt.figure(figsize=(5, 5))
    ax1 = fig.add_subplot(1,1,1)
    ax1.imshow(Backup_response)#,cmap='gray')
    plt.title("Response matrix")
    plt.axis('off')

    #performing NMS
    corners = []
    nms_pad = int(nms_size/2)
    for y in range(nms_pad,height-nms_pad):
        for x in range(nms_pad,width-nms_pad):
            # perform NMS
            # https://stackoverflow.com/questions/56099302/how-to-zero-out-all-values-of-matrix-2d-array-except-top-n-values-using-numpy
            nullified_arr = np.zeros_like(Response_mat[y-nms_pad:y+nms_pad,x-nms_pad:x+nms_pad])
            top_n = 6
            top_n_idxs = np.argpartition(Response_mat[y-nms_pad:y+nms_pad,
                          x-nms_pad:x+nms_pad].reshape(-1), -top_n)[-top_n:]

            nullified_arr.reshape(-1)[top_n_idxs] = Response_mat[y-nms_pad:y+nms_pad,
                          x-nms_pad:x+nms_pad].reshape(-1)[top_n_idxs]

            Response_mat[y-nms_pad:y+nms_pad,x-nms_pad:x+nms_pad] = nullified_arr
            x_val,y_val = np.where(Response_mat[y-nms_pad:y+nms_pad,
                          x-nms_pad:x+nms_pad]==np.max(Response_mat[y-nms_pad:y+nms_pad,x-nms_pad:x+nms_pad]))
            try:
              #print([int(x_val[0]),int(y_val[0])])
              corners.append([int(x_val[0]),int(y_val[0])])
            except:
              #print("err")
              pass
            x=x+10
        y=y+10
    #img1_gray_blur
    fig = plt.figure(figsize=(5, 5))
    ax1 = fig.add_subplot(1,1,1)
    ax1.imshow(Response_mat)#,cmap='gray')
    plt.title("NMS matrix")
    plt.axis('off')

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
    keypoints = []
    points = []
    for x,y in corners:
        #print(item[0],item[1])
        gx = Ix[y,x]
        gy = Iy[y,x]
        gx2 = gx*gx
        gy2 = gy*gy
        mag_ = math.sqrt(gx2+gy2)
        points.append(mag_)
        if mag_> 80:
          keypoints.append(cv2.KeyPoint(x, y, mag_))
    print("done")
    plt.hist(points, normed=True, bins=30) 
    plt.ylabel('magnitude value')
    #print(points)
    return keypoints

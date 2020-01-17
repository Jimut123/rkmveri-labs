import cv2
import numpy as np
import os.path

'''
Class Demo: Images as Functions
'''


img1 = cv2.imread('input/peppers.png', cv2.IMREAD_COLOR)
cv2.imwrite('output/peppers_new.png', img1)
img2 = cv2.imread('input/dolphin.png', cv2.IMREAD_COLOR)
cv2.imwrite('output/dolphin_new.png', img2)



cv2.imshow('peppers', img1)
cv2.imshow('dolphin', img2)
cv2.waitKey(0)
cv2.destroyAllWindows()

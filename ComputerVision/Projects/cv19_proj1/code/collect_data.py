"""
Auto-script for collecting data for higher dimensional visualization.

This script takes all the images and computes the time taken by lowpass and highpass filter for 
every images and stores it in a json file.

Author: Jimut Bahan Pal
Dated: 27th January, 2019
"""


import os
import cv2
import sys
import json
import time
import matplotlib
import numpy as np
from tqdm import tqdm
import matplotlib.pyplot as plt
from utils import vis_hybrid_image, load_image, save_image
from student_code import my_imfilter, create_hybrid_image


with open('json_data.json') as f:
    data = json.load(f)
print(data)


pictures_mydata = ['cowboyhat.jpg','lambo.jpg','mexican_house.jpg','palm.jpg','sasuke.png','viveka.jpg',
'ferrari.jpg','mattd.jpg','naruto.jpg','ramakrishna.jpg','tom.jpg','ylambo.jpg',
'housebung.jpg','mexican_hat.jpg','olive.jpg','sasuke.jpg','tomsad.jpg']

given_data=['bicycle.bmp',  'cat.bmp',  'einstein.bmp',  'marilyn.bmp','submarine.bmp',
'bird.bmp','dog.bmp',  'fish.bmp',  'motorcycle.bmp',  'plane.bmp']

cutoff_freq = [2,4,5,7,10,15,20,25,30]

path_ = "../data/"
full_data = {}
for pictures in tqdm(given_data):
    full_path = path_+pictures
    picture_data = {}
    image1 = load_image(full_path)
    print(pictures," :: loaded ")
    picture_data["height"] = image1.shape[0]
    picture_data["width"] = image1.shape[1]
    for freq in tqdm(cutoff_freq):
        filter = cv2.getGaussianKernel(ksize=freq*4+1,
                                sigma=freq)
        filter = np.dot(filter, filter.T)
        start = time.time()
        print(" Applying low pass filter on ",pictures)
        blurry_dog = my_imfilter(image1, filter)
        done = time.time()
        elapsed_lowpass = done - start
        print("Time for low pass filter of size ",freq," : ",elapsed_lowpass)
        print(" Applying high pass filter on ",pictures)
        h=-filter
        h[int(filter.shape[0]/2),int(filter.shape[0]/2)] = filter[int(filter.shape[0]/2),int(filter.shape[0]/2)]
        h[int(filter.shape[0]/2),int(filter.shape[0]/2)] = h[int(filter.shape[0]/2),int(filter.shape[0]/2)] -h.sum()
        start = time.time()
        high_frequencies = my_imfilter(image1,h)
        done = time.time()
        elapsed_highpass = done - start
        print("Time for high pass filter of size ",freq," : ",elapsed_highpass)
        new_info = {
            "elapsed_lowpass":elapsed_lowpass,
            "elapsed_highpass":elapsed_highpass,
        }
        print(json.dumps(new_info, indent=4, sort_keys=True))
        picture_data[freq] = new_info
    print("Summary of Image ",pictures," :::=> ")
    #print(json.dumps(picture_data, indent=4, sort_keys=True))
    full_data[pictures] = picture_data
    with open('json_data.json', 'w') as f:
        json.dump(full_data, f,ensure_ascii=False, indent=4)



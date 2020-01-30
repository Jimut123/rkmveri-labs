"""
Script to collect the data from the json files and plot accordingly. This plots the time Vs size of images along with the size of kernels.

Author: Jimut Bahan Pal
Date: 27th January 2019
"""


import json
import matplotlib.pyplot as plt

# collect the data
with open('json_data_given.json') as f:
    data1 = json.load(f)
with open('json_data_myfiles.json') as f:
    data2 = json.load(f)

filter_2 = []
filter_4 = []
filter_5 = []
filter_7 = []
filter_10 = []
filter_15 = []
filter_20 = []
filter_25 = []
filter_30 = []

sizes = []
# put the data in list
for item in data1:
    size = data1[item]["height"]*data1[item]["width"]*3
    sizes.append(size)
    filter_2.append([data1[item]["2"]["elapsed_lowpass"],data1[item]["2"]["elapsed_highpass"]])
    filter_4.append([data1[item]["4"]["elapsed_lowpass"],data1[item]["4"]["elapsed_highpass"]])
    filter_5.append([data1[item]["5"]["elapsed_lowpass"],data1[item]["5"]["elapsed_highpass"]])
    filter_7.append([data1[item]["7"]["elapsed_lowpass"],data1[item]["7"]["elapsed_highpass"]])
    filter_10.append([data1[item]["10"]["elapsed_lowpass"],data1[item]["10"]["elapsed_highpass"]])
    filter_15.append([data1[item]["15"]["elapsed_lowpass"],data1[item]["15"]["elapsed_highpass"]])
    filter_20.append([data1[item]["20"]["elapsed_lowpass"],data1[item]["20"]["elapsed_highpass"]])
    filter_25.append([data1[item]["25"]["elapsed_lowpass"],data1[item]["25"]["elapsed_highpass"]])
    filter_30.append([data1[item]["30"]["elapsed_lowpass"],data1[item]["30"]["elapsed_highpass"]])
for item in data2:
    size = data2[item]["height"]*data2[item]["width"]*3
    sizes.append(size)
    filter_2.append([data2[item]["2"]["elapsed_lowpass"],data2[item]["2"]["elapsed_highpass"]])
    filter_4.append([data2[item]["4"]["elapsed_lowpass"],data2[item]["4"]["elapsed_highpass"]])
    filter_5.append([data2[item]["5"]["elapsed_lowpass"],data2[item]["5"]["elapsed_highpass"]])
    filter_7.append([data2[item]["7"]["elapsed_lowpass"],data2[item]["7"]["elapsed_highpass"]])
    filter_10.append([data2[item]["10"]["elapsed_lowpass"],data2[item]["10"]["elapsed_highpass"]])
    filter_15.append([data2[item]["15"]["elapsed_lowpass"],data2[item]["15"]["elapsed_highpass"]])
    filter_20.append([data2[item]["20"]["elapsed_lowpass"],data2[item]["20"]["elapsed_highpass"]])
    filter_25.append([data2[item]["25"]["elapsed_lowpass"],data2[item]["25"]["elapsed_highpass"]])
    filter_30.append([data2[item]["30"]["elapsed_lowpass"],data2[item]["30"]["elapsed_highpass"]])
fig, ax = plt.subplots(figsize=(10,5))
size_plot = 5

# plot for low pass filter
plt.scatter(sizes,[filter_2[0] for filter_2 in filter_2],s=size_plot,cmap='#ba1616',label='filter 2')
plt.scatter(sizes,[filter_4[0] for filter_4 in filter_4], s=size_plot,cmap='#168bba',label='filter 4')
plt.scatter(sizes,[filter_5[0] for filter_5 in filter_5], s=size_plot,cmap='#0cf556',label='filter 5')
plt.scatter(sizes,[filter_7[0] for filter_7 in filter_7],s=size_plot,cmap='#f50cf2 ',label='filter 7')
plt.scatter(sizes,[filter_10[0] for filter_10 in filter_10], s=size_plot,cmap='#ddf50c',label='filter 10')
plt.scatter(sizes,[filter_15[0] for filter_15 in filter_15], s=size_plot,cmap='#f5730c',label='filter 15')
plt.scatter(sizes,[filter_20[0] for filter_20 in filter_20], s=size_plot,cmap='#760cf5',label='filter 20')
plt.scatter(sizes,[filter_25[0] for filter_25 in filter_25], s=size_plot,cmap='#070708',label='filter 25')
plt.scatter(sizes,[filter_30[0] for filter_30 in filter_30], s=size_plot,cmap='#23d58c',label='filter 30')


#ax.axis('equal')
leg = ax.legend();
plt.title('Plot for Time Vs Size for lowpass filter');
plt.xlabel('Size = (widthxheightx3)')
plt.ylabel('Time (in sec)')



# plot for high pass filter
fig, ax = plt.subplots(figsize=(10,5))
size_plot = 5
plt.scatter(sizes,[filter_2[1] for filter_2 in filter_2],s=size_plot,cmap='#ba1616',label='filter 2')
plt.scatter(sizes,[filter_4[1] for filter_4 in filter_4], s=size_plot,cmap='#168bba',label='filter 4')
plt.scatter(sizes,[filter_5[1] for filter_5 in filter_5], s=size_plot,cmap='#0cf556',label='filter 5')
plt.scatter(sizes,[filter_7[1] for filter_7 in filter_7],s=size_plot,cmap='#f50cf2 ',label='filter 7')
plt.scatter(sizes,[filter_10[1] for filter_10 in filter_10], s=size_plot,cmap='#ddf50c',label='filter 10')
plt.scatter(sizes,[filter_15[1] for filter_15 in filter_15], s=size_plot,cmap='#f5730c',label='filter 15')
plt.scatter(sizes,[filter_20[1] for filter_20 in filter_20], s=size_plot,cmap='#760cf5',label='filter 20')
plt.scatter(sizes,[filter_25[1] for filter_25 in filter_25], s=size_plot,cmap='#070708',label='filter 25')
plt.scatter(sizes,[filter_30[1] for filter_30 in filter_30], s=size_plot,cmap='#23d58c',label='filter 30')
#ax.axis('equal')
leg = ax.legend();
plt.title('Plot for Time Vs Size for highpass filter');
plt.xlabel('Size = (widthxheightx3)')
plt.ylabel('Time (in sec)')



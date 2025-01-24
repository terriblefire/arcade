#!/usr/bin/env python

import os
import numpy as np
os.chdir(os.path.dirname(__file__))

profiles = []

def find_nearest(array, value):
    array = np.asarray(array)
    idx = (np.abs(array - value)).argmin()
    return idx

for i in range(1,5):
    with open("calib_{}.csv".format(i), "r") as f:
        lines = f.readlines()
        profile = [float(line.split(',')[1].strip()) for line in lines]
        profiles.append(np.array(profile[0:128]))

with open("measured.csv", "r") as f:
    lines = f.readlines()
    measured_profile = [float(x) for x in lines]

calibrated_profile = np.mean(profiles, axis=0)


for i in range(0, 256, 8):
    value = np.mean(measured_profile[i:i+8])
    idx = find_nearest(calibrated_profile, value)
    print("%02X" % (idx,))



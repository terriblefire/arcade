#!/usr/bin/env python

from math import exp,log

mag = 0.41284

def fn(x):
    return mag/(1.0+exp(-10*((x/256.0)-0.6)))

values = [fn(x) for x in range(0,256)]
dbs = [10*log(fn(x)/mag, 10) for x in range(0,256)]

#for db in dbs:                                                                                                                                                                   
#    print(abs(round(db*2)))                                                                                                                                                      

new_vals = [mag*pow(10, round(db*2)/20) for db in dbs]

steps = 8
for db in dbs[::steps]:
    print("%02x" % abs(round(db*2)))
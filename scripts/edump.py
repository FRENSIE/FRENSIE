#! /usr/bin/env python
import argparse as ap
import h5py

# Set up the argument parser
description = "This script allows one to pull information from the "\
              "simulation.h5 file generated after running facemc. The output "\
              "is dumped to the screen."

parser = ap.ArgumentParser(description=description)

simulation_file_msg = "the simulation.h5 file (with path)"
parser.add_argument('-f', help=simulation_file_msg, required=True)

estimator_id_msg = "the desired estimator id"
parser.add_argument('-e', help=estimator_id_msg, required=True)

entity_id_msg = "the desired entity id (or total)"
parser.add_argument('-i', help=entity_id_msg, required=True)

bin_msg = "the desired bin (Energy)"
parser.add_argument('-b', help=bin_msg)

# Parse the user's arguments
user_args = parser.parse_args()

# Open the simulation.h5 file
hdf5_file = h5py.File(user_args.f,'r')

estimator_group = "Estimators/"+str(user_args.e)+"/"

# Construct the dataset name of the desired data
if user_args.i != "total":
    estimator_group += str(user_args.i)+"/processed_bin_data"
else:
    estimator_group += "processed_total_bin_data"

# Construct the dataset name for the desired bin
bin_group = "Estimators/"+str(user_args.e)+"/"+str(user_args.b)

print "# ", estimator_group, ":"

# Print the dataset if it exists
if estimator_group in hdf5_file:
    dset = hdf5_file[estimator_group]
    array = dset[:]

    if bin_group in hdf5_file:
        bin_dset = hdf5_file[bin_group]
        bins = bin_dset[:]

        print bins[0], 0.0, 0.0

        for i in range(0,len(array)):
            print bins[i+1], array[i][0], array[i][1]

    else:
        for i in array:
            print i[0], i[1]

else:
    print "Error: the requested estimator id and/or entity id does not exist"

hdf5_file.close()


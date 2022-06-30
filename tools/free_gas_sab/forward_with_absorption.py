# Imports
import matplotlib.pyplot as plt 
import numpy             as np 
from   struct        import *
import math
from   pylab         import *
import pylab

# Define Plotting Script
def parse_data( filename ):
    file_open = open( filename, 'rb' )
    file_read = file_open.read()

    num_scatters  = unpack('i', file_read[0:4])[0]
    num_particles = unpack('i', file_read[4:8])[0]

    data_map = {}
    index    = int(8)
    indnext  = index+int(8)

    for i in range(0, num_scatters):

        temp_array  = []

        for j in range(0, num_particles):
            temp_array.append( unpack( 'd', file_read[ index:indnext ] )[0] )
            index = index + 8
            indnext = indnext + 8

        # Extract the data
        data_map[ i ] = temp_array

    return data_map

# Load the data 
data_dir   = '/home/ecmoll/software/frensie/test_data/forward_transport/'
figure_dir = '/home/ecmoll/software/frensie/test_data/forward_transport/figures/'
adjoint_dir= '/home/ecmoll/software/frensie/test_data/adjoint_transport/sources/'
data_files = ['H_293K_absorption.output']

temps = [293]

colors = 20
cm     = pylab.get_cmap('rainbow')

for i in range(0, 1):
    data = parse_data( data_dir + data_files[i] )

    plt.figure()
    plt.gca().set_xscale('log')
    bin_vals = np.geomspace( 1e-10, 5e-6, num=100 )

    hist = np.histogram( data[ 9 ], bin_vals )

    np.savetxt(adjoint_dir + 'H_9.abs', hist[0].T, delimiter=',')
    np.savetxt(adjoint_dir + 'bin_bounds.abs', hist[1].T, delimiter=',')

    hist = np.histogram( data[ 19 ], bin_vals )

    np.savetxt(adjoint_dir + 'H_19.abs', hist[0].T, delimiter=',')
    np.savetxt(adjoint_dir + 'bin_bounds.abs', hist[1].T, delimiter=',')

    hist = np.histogram( data[ 49 ], bin_vals )

    np.savetxt(adjoint_dir + 'H_49.abs', hist[0].T, delimiter=',')
    np.savetxt(adjoint_dir + 'bin_bounds.abs', hist[1].T, delimiter=',')

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
data_dir   = '/home/ecmoll/software/frensie/test_data/adjoint_transport/'
figure_dir = '/home/ecmoll/software/frensie/test_data/adjoint_transport/figures/'
data_files = ['H_293K.transport',
              'H_600K.transport',
              'H_900K.transport',
              'H_1200K.transport',
              'H_2500K.transport']

temps = [293, 600, 900, 1200, 2500]

colors = 20
cm     = pylab.get_cmap('rainbow')

for i in range(0, 5):
    data = parse_data( data_dir + data_files[i] )

    plt.figure()
    plt.gca().set_xscale('log')
    bin_vals = np.geomspace( 1e-10, 5e-6, num=100 )
    scatter  = 0

    for key,value in data.items():
        hist = np.hstack( value )
        
        if scatter%2 == 1:
            plt.hist(hist, bin_vals, histtype='step',label='C: ' + str(int(scatter)), color=cm(1.*scatter/colors) )
        else:
            plt.hist(hist, bin_vals, histtype='step',  color=cm(1.*scatter/colors) )
        
        scatter = scatter + 1

    plt.ticklabel_format(axis='y', style='sci', scilimits=(-2,2))
    plt.title('Infinite Medium Pure Scattering (Adjoint) - ' + str(int(temps[i])) + 'K')
    plt.xlabel('Energy (MeV)')
    plt.ylabel('Population in Bin - 1e6 Source Particles')
    plt.legend(loc='upper left')
    
    filename = figure_dir + 'adjoint_scattering_' + str(temps[i]) + 'K.png'
    plt.savefig(filename, dpi=600)
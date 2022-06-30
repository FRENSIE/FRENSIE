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
data_files = ['H_293K.output',
              'H_600K.output',
              'H_900K.output',
              'H_1200K.output',
              'H_2500K.output']

temps = [293, 600, 900, 1200, 2500]

colors = 20
cm     = pylab.get_cmap('rainbow')

for i in range(0, 5):
    data = parse_data( data_dir + data_files[i] )

    plt.figure(figsize=(7.5,9.0))
    plt.subplot(211)
    plt.gca().set_xscale('log')
    plt.title('Infinite Medium Pure Adjoint Scattering - ' + str(int(temps[i])) + 'K')
    plt.ylabel('Population in Bin - 1e6 Source Particles')
    bin_vals = np.geomspace( 1e-10, 5e-6, num=100 )
    scatter  = 0

    for key,value in data.items():
        hist = np.hstack( value )
        
        if scatter%2 == 0:
            plt.hist(hist, bin_vals, histtype='step',label='C: ' + str(int(scatter)), color=cm(1.*scatter/colors) )
        else:
            plt.hist(hist, bin_vals, histtype='step',  color=cm(1.*scatter/colors) )
        
        scatter = scatter + 1
    plt.axis([1e-10,5e-6,0,1e6])
    plt.legend(loc='upper left')
    plt.ticklabel_format(axis='y', style='sci', scilimits=(-2,2))

    scatter = 0

    plt.subplot(212)
    plt.gca().set_xscale('log')
    for key,value in data.items():
        hist = np.hstack( value )
        
        if scatter%2 == 0:
            plt.hist(hist, bin_vals, histtype='step',label='C: ' + str(int(scatter)), color=cm(1.*scatter/colors) )
        else:
            plt.hist(hist, bin_vals, histtype='step',  color=cm(1.*scatter/colors) )
        
        scatter = scatter + 1

    plt.ticklabel_format(axis='y', style='sci', scilimits=(-2,2))
    plt.axis([1e-10,5e-6,0,1.5e5])
    plt.xlabel('Energy (MeV)')
    plt.ylabel('Population in Bin - 1e6 Source Particles')
    plt.legend(loc='upper left')
    
    filename = figure_dir + 'adjoint_scattering_' + str(temps[i]) + 'K.png'
    plt.savefig(filename, dpi=600)
    #plt.show()

# Imports
import matplotlib.pyplot as plt 
import numpy             as np 
from   struct        import *
import math
from   pylab         import *
import pylab
import pickle

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

    bin_vals = np.geomspace( 1e-10, 5e-6, num=100 )
    bin_vals_centroids = np.zeros(len(bin_vals)-1)

    for j in range(0, len(bin_vals_centroids)):
        bin_vals_centroids[j] = (bin_vals[j] + bin_vals[j+1])/2.0

    scatter  = 0

    for key,value in data.items():
        hist = np.hstack( value )
        
        if scatter%2 == 1:
            plt.hist(hist, bin_vals, histtype='step',label='C: ' + str(int(scatter)), color=cm(1.*scatter/colors) )
        else:
            plt.hist(hist, bin_vals, histtype='step',  color=cm(1.*scatter/colors) )
        
        scatter = scatter + 1

    plt.ticklabel_format(axis='y', style='sci', scilimits=(-2,2))
    plt.title('Infinite Medium Pure Scattering - ' + str(int(temps[i])) + 'K')
    plt.xlabel('Energy (MeV)')
    plt.ylabel('Population in Bin - 1e6 Source Particles')
    plt.legend(loc='upper left')
    
    filename = figure_dir + 'forward_scattering_' + str(temps[i]) + 'K.png'
    plt.savefig(filename, dpi=600)

    hist = np.histogram( data[ 19 ], bin_vals )

    for j in range(0, 19):
        print(np.average(data[j]))

    np.savetxt(adjoint_dir + data_files[i] + '.eq_src', hist[0].T, delimiter=',')
    np.savetxt(adjoint_dir + 'bin_bounds.eq_src', hist[1].T, delimiter=',')

    """
    if i == 0:
        file_WW = '/home/ecmoll/software/frensie/test_data/forward_transport/ww.p'
        ifile = open(file_WW,'rb')
        ww_data = pickle.load(ifile)

        ww_hist = np.histogram( ww_data[19], bin_vals )
        F_hist = np.array(hist[0])
        f_hist = F_hist/np.amax(F_hist)
        W_hist = np.array(ww_hist[0])
        w_hist = W_hist/np.amax(W_hist)

        ferr   = np.sqrt(F_hist)/F_hist
        werr   = np.sqrt(W_hist)/W_hist

        ce     = f_hist/w_hist
        cerr   = np.sqrt(ferr*ferr + werr*werr)

        for i in range(len(ce)):
            if math.isnan(ce[i]):
                ce[i] = 1
                cerr[i] = 0.001

        plt.figure()
        plt.subplot(211)
        plt.title('Comparison of FRENSIE and Wigner-Wilkins for Simple Proton Gas')
        plt.gca().set_xscale('log')
        plt.step( bin_vals_centroids, f_hist, where='mid', color='r', label='FRENSIE')
        plt.step( bin_vals_centroids, w_hist, where='mid', color='k', linestyle=':', label='Wigner-Wilkins')
        plt.legend()
        plt.axis([1e-10,5e-6,0,1.1])
        plt.ylabel('Normalized Neutron Energy Distribution')

        plt.subplot(212)
        plt.gca().set_xscale('log')
        plt.errorbar( bin_vals_centroids, ce, yerr=cerr, fmt='.')
        plt.ylabel('C/E')
        plt.xlabel('Energy (MeV)')
        plt.axis([1e-10,5e-6,0.5,1.5])
        plt.axhline(1, color='k', linewidth=0.5)
        plt.show()
    """
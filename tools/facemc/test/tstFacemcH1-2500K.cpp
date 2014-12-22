//---------------------------------------------------------------------------//
//!
//! \file   tstFacemcH1-2500K.cpp
//! \author Alex Robinson
//! \brief  facemc executable verification test for H-1 at 2500K
//!
//---------------------------------------------------------------------------//

// Teuchos Includes
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_LocalTestingHelpers.hpp>

// FRENSIE Includes
#include "facemcCore.hpp"
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

int main( int argc, char** argv )
{
  Teuchos::FancyOStream& out = 
    *Teuchos::VerboseObjectBase::getDefaultOStream();
  
  bool success = true;

  // Run the test problem
  int return_value = facemcCore( argc, argv );

  if( return_value == 0 )
  {
    Teuchos::Array<MonteCarlo::PhaseSpaceDimension> dimension_ordering( 1 ),
      dimension_ordering_result;

    dimension_ordering[0] = MonteCarlo::ENERGY_DIMENSION;
    
    Teuchos::Array<double> energy_bins( 111 ),
      energy_bins_result;
    energy_bins[0] = 1e-11;
    energy_bins[1] = 1.2589e-11;
    energy_bins[2] = 1.5849e-11;
    energy_bins[3] = 1.9953e-11;
    energy_bins[4] = 2.5119e-11;
    energy_bins[5] = 3.1623e-11;
    energy_bins[6] = 3.9811e-11;
    energy_bins[7] = 5.0119e-11; 
    energy_bins[8] = 6.3096e-11; 
    energy_bins[9] = 7.9433e-11; 
    energy_bins[10] = 1e-10; 
    energy_bins[11] = 1.2589e-10;
    energy_bins[12] = 1.5849e-10; 
    energy_bins[13] = 1.9953e-10; 
    energy_bins[14] = 2.5119e-10; 
    energy_bins[15] = 3.1623e-10; 
    energy_bins[16] = 3.9811e-10; 
    energy_bins[17] = 5.0119e-10;
    energy_bins[18] = 6.3096e-10; 
    energy_bins[19] = 7.9433e-10; 
    energy_bins[20] = 1e-09; 
    energy_bins[21] = 1.2589e-09; 
    energy_bins[22] = 1.5849e-09; 
    energy_bins[23] = 1.9953e-09;
    energy_bins[24] = 2.5119e-09; 
    energy_bins[25] = 3.1623e-09; 
    energy_bins[26] = 3.9811e-09; 
    energy_bins[27] = 5.0119e-09; 
    energy_bins[28] = 6.3096e-09; 
    energy_bins[29] = 7.9433e-09;
    energy_bins[30] = 1e-08; 
    energy_bins[31] = 1.2589e-08; 
    energy_bins[32] = 1.5849e-08; 
    energy_bins[33] = 1.9953e-08; 
    energy_bins[34] = 2.5119e-08; 
    energy_bins[35] = 3.1623e-08;
    energy_bins[36] = 3.9811e-08; 
    energy_bins[37] = 5.0119e-08; 
    energy_bins[38] = 6.3096e-08; 
    energy_bins[39] = 7.9433e-08; 
    energy_bins[40] = 1e-07; 
    energy_bins[41] = 1.2589e-07;
    energy_bins[42] = 1.5849e-07; 
    energy_bins[43] = 1.9953e-07; 
    energy_bins[44] = 2.5119e-07; 
    energy_bins[45] = 3.1623e-07; 
    energy_bins[46] = 3.9811e-07; 
    energy_bins[47] = 5.0119e-07;
    energy_bins[48] = 6.3096e-07; 
    energy_bins[49] = 7.9433e-07; 
    energy_bins[50] = 1e-06; 
    energy_bins[51] = 1.2589e-06; 
    energy_bins[52] = 1.5849e-06; 
    energy_bins[53] = 1.9953e-06;
    energy_bins[54] = 2.5119e-06; 
    energy_bins[55] = 3.1623e-06; 
    energy_bins[56] = 3.9811e-06; 
    energy_bins[57] = 5.0119e-06; 
    energy_bins[58] = 6.3096e-06; 
    energy_bins[59] = 7.9433e-06;
    energy_bins[60] = 1e-05; 
    energy_bins[61] = 1.2589e-05; 
    energy_bins[62] = 1.5849e-05; 
    energy_bins[63] = 1.9953e-05; 
    energy_bins[64] = 2.5119e-05; 
    energy_bins[65] = 3.1623e-05;
    energy_bins[66] = 3.9811e-05; 
    energy_bins[67] = 5.0119e-05; 
    energy_bins[68] = 6.3096e-05; 
    energy_bins[69] = 7.9433e-05; 
    energy_bins[70] = 0.0001; 
    energy_bins[71] = 0.00012589;
    energy_bins[72] = 0.00015849; 
    energy_bins[73] = 0.00019953; 
    energy_bins[74] = 0.00025119; 
    energy_bins[75] = 0.00031623; 
    energy_bins[76] = 0.00039811; 
    energy_bins[77] = 0.00050119;
    energy_bins[78] = 0.00063096; 
    energy_bins[79] = 0.00079433; 
    energy_bins[80] = 0.001; 
    energy_bins[81] = 0.0012589; 
    energy_bins[82] = 0.0015849; 
    energy_bins[83] = 0.0019953;
    energy_bins[84] = 0.0025119; 
    energy_bins[85] = 0.0031623; 
    energy_bins[86] = 0.0039811; 
    energy_bins[87] = 0.0050119; 
    energy_bins[88] = 0.0063096; 
    energy_bins[89] = 0.0079433; 
    energy_bins[90] = 0.01;
    energy_bins[91] = 0.012589; 
    energy_bins[92] = 0.015849; 
    energy_bins[93] = 0.019953; 
    energy_bins[94] = 0.025119; 
    energy_bins[95] = 0.031623; 
    energy_bins[96] = 0.039811; 
    energy_bins[97] = 0.050119;
    energy_bins[98] = 0.063096; 
    energy_bins[99] = 0.079433; 
    energy_bins[100] = 0.1; 
    energy_bins[101] = 0.12589; 
    energy_bins[102] = 0.15849; 
    energy_bins[103] = 0.19953; 
    energy_bins[104] = 0.25119; 
    energy_bins[105] = 0.31623;
    energy_bins[106] = 0.39811; 
    energy_bins[107] = 0.50119; 
    energy_bins[108] = 0.63096; 
    energy_bins[109] = 0.79433; 
    energy_bins[110] = 1.0;
    
    Teuchos::Array<Utility::Pair<double,double> > raw_bin_data( 110 ),
      raw_bin_data_result;
    raw_bin_data[0]( 0, 0 ); 
    raw_bin_data[1]( 0, 0 ); 
    raw_bin_data[2]( 0, 0 ); 
    raw_bin_data[3]( 0, 0 ); 
    raw_bin_data[4]( 0, 0 ); 
    raw_bin_data[5]( 0, 0 ); 
    raw_bin_data[6]( 0, 0 ); 
    raw_bin_data[7]( 0, 0 ); 
    raw_bin_data[8]( 0, 0 );
    raw_bin_data[9]( 0, 0 ); 
    raw_bin_data[10]( 0, 0 ); 
    raw_bin_data[11]( 0, 0 ); 
    raw_bin_data[12]( 0, 0 ); 
    raw_bin_data[13]( 0, 0 ); 
    raw_bin_data[14]( 1, 1 ); 
    raw_bin_data[15]( 0, 0 ); 
    raw_bin_data[16]( 0, 0 ); 
    raw_bin_data[17]( 0, 0 );
    raw_bin_data[18]( 1, 1 ); 
    raw_bin_data[19]( 2, 2 ); 
    raw_bin_data[20]( 1, 1 ); 
    raw_bin_data[21]( 4, 4 ); 
    raw_bin_data[22]( 3, 3 ); 
    raw_bin_data[23]( 10, 10 ); 
    raw_bin_data[24]( 8, 8 ); 
    raw_bin_data[25]( 11, 11 );
    raw_bin_data[26]( 27, 27 ); 
    raw_bin_data[27]( 42, 42 ); 
    raw_bin_data[28]( 68, 68 ); 
    raw_bin_data[29]( 94, 94 ); 
    raw_bin_data[30]( 142, 142 ); 
    raw_bin_data[31]( 241, 241 );
    raw_bin_data[32]( 421, 421 ); 
    raw_bin_data[33]( 679, 679 ); 
    raw_bin_data[34]( 1064, 1064 ); 
    raw_bin_data[35]( 1711, 1711 ); 
    raw_bin_data[36]( 2630, 2630 );
    raw_bin_data[37]( 4153, 4153 ); 
    raw_bin_data[38]( 6411, 6411 ); 
    raw_bin_data[39]( 9851, 9851 ); 
    raw_bin_data[40]( 14675, 14675 );
    raw_bin_data[41]( 21187, 21187 ); 
    raw_bin_data[42]( 29736, 29736 ); 
    raw_bin_data[43]( 39653, 39653 ); 
    raw_bin_data[44]( 50267, 50267 );
    raw_bin_data[45]( 59184, 59184 ); 
    raw_bin_data[46]( 64131, 64131 ); 
    raw_bin_data[47]( 62341, 62341 ); 
    raw_bin_data[48]( 52699, 52699 );
    raw_bin_data[49]( 38400, 38400 ); 
    raw_bin_data[50]( 22795, 22795 ); 
    raw_bin_data[51]( 11215, 11215 ); 
    raw_bin_data[52]( 4830, 4830 );
    raw_bin_data[53]( 2640, 2640 ); 
    raw_bin_data[54]( 2147, 2147 ); 
    raw_bin_data[55]( 1982, 1982 ); 
    raw_bin_data[56]( 1958, 1958 ); 
    raw_bin_data[57]( 1968, 1968 );
    raw_bin_data[58]( 1902, 1902 ); 
    raw_bin_data[59]( 1852, 1852 ); 
    raw_bin_data[60]( 1891, 1891 ); 
    raw_bin_data[61]( 1896, 1896 ); 
    raw_bin_data[62]( 1821, 1821 );
    raw_bin_data[63]( 1883, 1883 ); 
    raw_bin_data[64]( 1914, 1914 ); 
    raw_bin_data[65]( 1781, 1781 ); 
    raw_bin_data[66]( 1866, 1866 ); 
    raw_bin_data[67]( 1797, 1797 );
    raw_bin_data[68]( 1793, 1793 ); 
    raw_bin_data[69]( 1873, 1873 ); 
    raw_bin_data[70]( 1821, 1821 ); 
    raw_bin_data[71]( 1861, 1861 ); 
    raw_bin_data[72]( 1883, 1883 );
    raw_bin_data[73]( 1802, 1802 ); 
    raw_bin_data[74]( 1845, 1845 ); 
    raw_bin_data[75]( 1817, 1817 ); 
    raw_bin_data[76]( 1840, 1840 ); 
    raw_bin_data[77]( 1790, 1790 );
    raw_bin_data[78]( 1821, 1821 ); 
    raw_bin_data[79]( 1843, 1843 ); 
    raw_bin_data[80]( 1846, 1846 ); 
    raw_bin_data[81]( 1816, 1816 ); 
    raw_bin_data[82]( 1922, 1922 );
    raw_bin_data[83]( 1904, 1904 ); 
    raw_bin_data[84]( 1882, 1882 ); 
    raw_bin_data[85]( 1916, 1916 ); 
    raw_bin_data[86]( 1865, 1865 ); 
    raw_bin_data[87]( 1959, 1959 );
    raw_bin_data[88]( 2048, 2048 ); 
    raw_bin_data[89]( 1970, 1970 ); 
    raw_bin_data[90]( 1971, 1971 ); 
    raw_bin_data[91]( 2108, 2108 ); 
    raw_bin_data[92]( 2120, 2120 );
    raw_bin_data[93]( 2213, 2213 ); 
    raw_bin_data[94]( 2367, 2367 ); 
    raw_bin_data[95]( 2477, 2477 ); 
    raw_bin_data[96]( 2720, 2720 ); 
    raw_bin_data[97]( 2917, 2917 );
    raw_bin_data[98]( 3067, 3067 ); 
    raw_bin_data[99]( 3330, 3330 ); 
    raw_bin_data[100]( 3959, 3959 ); 
    raw_bin_data[101]( 4470, 4470 ); 
    raw_bin_data[102]( 4949, 4949 );
    raw_bin_data[103]( 5865, 5865 ); 
    raw_bin_data[104]( 6770, 6770 ); 
    raw_bin_data[105]( 7790, 7790 ); 
    raw_bin_data[106]( 9232, 9232 ); 
    raw_bin_data[107]( 10558, 10558 ); 
    raw_bin_data[108]( 12040, 12040 ); 
    raw_bin_data[109]( 13510, 13510 );
    
    Teuchos::Array<Utility::Pair<double,double> > processed_bin_data( 110 ),
      processed_bin_data_result;
    processed_bin_data[0]( 0, 0 ); 
    processed_bin_data[1]( 0, 0 ); 
    processed_bin_data[2]( 0, 0 ); 
    processed_bin_data[3]( 0, 0 ); 
    processed_bin_data[4]( 0, 0 ); 
    processed_bin_data[5]( 0, 0 ); 
    processed_bin_data[6]( 0, 0 ); 
    processed_bin_data[7]( 0, 0 ); 
    processed_bin_data[8]( 0, 0 );
    processed_bin_data[9]( 0, 0 ); 
    processed_bin_data[10]( 0, 0 ); 
    processed_bin_data[11]( 0, 0 ); 
    processed_bin_data[12]( 0, 0 ); 
    processed_bin_data[13]( 0, 0 ); 
    processed_bin_data[14]( 1e-06, 0.999999499999875 );
    processed_bin_data[15]( 0, 0 ); 
    processed_bin_data[16]( 0, 0 ); 
    processed_bin_data[17]( 0, 0 ); 
    processed_bin_data[18]( 1e-06, 0.999999499999875 );
    processed_bin_data[19]( 2e-06, 0.707106074079413 ); 
    processed_bin_data[20]( 1e-06, 0.999999499999875 );
    processed_bin_data[21]( 4e-06, 0.499998999999 ); 
    processed_bin_data[22]( 3e-06, 0.577349403163572 );
    processed_bin_data[23]( 1e-05, 0.316226184874055 ); 
    processed_bin_data[24]( 8e-06, 0.353551976376883 );
    processed_bin_data[25]( 1.1e-05, 0.301509686260808 ); 
    processed_bin_data[26]( 2.7e-05, 0.192447491636127 );
    processed_bin_data[27]( 4.2e-05, 0.154300109557718 ); 
    processed_bin_data[28]( 6.8e-05, 0.121263689342446 );
    processed_bin_data[29]( 9.4e-05, 0.103137276832096 ); 
    processed_bin_data[30]( 0.000142, 0.0839121774304943 );
    processed_bin_data[31]( 0.000241, 0.0644079000850128 ); 
    processed_bin_data[32]( 0.000421, 0.0487267576605915 );
    processed_bin_data[33]( 0.000679, 0.0383634467960536 ); 
    processed_bin_data[34]( 0.001064, 0.0306406531271798 );
    processed_bin_data[35]( 0.001711, 0.0241547828792538 ); 
    processed_bin_data[36]( 0.00263, 0.0194737807547001 );
    processed_bin_data[37]( 0.004153, 0.0154851474165693 ); 
    processed_bin_data[38]( 0.006411, 0.0124491729082254 );
    processed_bin_data[39]( 0.009851, 0.0100255940870501 ); 
    processed_bin_data[40]( 0.014675, 0.00819408936435729 );
    processed_bin_data[41]( 0.021187, 0.00679696652580367 ); 
    processed_bin_data[42]( 0.029736, 0.00571220368311622 );
    processed_bin_data[43]( 0.039653, 0.00492125724327767 ); 
    processed_bin_data[44]( 0.050267, 0.00434669613415872 );
    processed_bin_data[45]( 0.059184, 0.00398703630561573 ); 
    processed_bin_data[46]( 0.064131, 0.00382008938487332 );
    processed_bin_data[47]( 0.062341, 0.00387824803423937 ); 
    processed_bin_data[48]( 0.052699, 0.00423977501034793 );
    processed_bin_data[49]( 0.0384, 0.00500416493200081 ); 
    processed_bin_data[50]( 0.022795, 0.00654746283507295 );
    processed_bin_data[51]( 0.011215, 0.00938969089695912 ); 
    processed_bin_data[52]( 0.00483, 0.0143540704148377 );
    processed_bin_data[53]( 0.00264, 0.0194367661607552 ); 
    processed_bin_data[54]( 0.002147, 0.0215584365243619 );
    processed_bin_data[55]( 0.001982, 0.0224397163041401 ); 
    processed_bin_data[56]( 0.001958, 0.0225770952477584 );
    processed_bin_data[57]( 0.001968, 0.0225195488698334 ); 
    processed_bin_data[58]( 0.001902, 0.0229076920578078 );
    processed_bin_data[59]( 0.001852, 0.023215443210409 ); 
    processed_bin_data[60]( 0.001891, 0.0229743493873626 );
    processed_bin_data[61]( 0.001896, 0.022943978738169 ); 
    processed_bin_data[62]( 0.001821, 0.0234125782290212 );
    processed_bin_data[63]( 0.001883, 0.0230231936439232 ); 
    processed_bin_data[64]( 0.001914, 0.022835630924225 );
    processed_bin_data[65]( 0.001781, 0.0236745076676819 ); 
    processed_bin_data[66]( 0.001866, 0.0231280280309458 );
    processed_bin_data[67]( 0.001797, 0.0235686874320075 ); 
    processed_bin_data[68]( 0.001793, 0.0235950097288569 );
    processed_bin_data[69]( 0.001873, 0.023084688208529 ); 
    processed_bin_data[70]( 0.001821, 0.0234125782290212 );
    processed_bin_data[71]( 0.001861, 0.0231591345512946 ); 
    processed_bin_data[72]( 0.001883, 0.0230231936439232 );
    processed_bin_data[73]( 0.001802, 0.0235359078158197 ); 
    processed_bin_data[74]( 0.001845, 0.0232595232120996 );
    processed_bin_data[75]( 0.001817, 0.0234383816106433 ); 
    processed_bin_data[76]( 0.00184, 0.0232911627204304 );
    processed_bin_data[77]( 0.00179, 0.0236148092915673 ); 
    processed_bin_data[78]( 0.001821, 0.0234125782290212 );
    processed_bin_data[79]( 0.001843, 0.0232721635735819 ); 
    processed_bin_data[80]( 0.001846, 0.0232532107313688 );
    processed_bin_data[81]( 0.001816, 0.0234448457651472 ); 
    processed_bin_data[82]( 0.001922, 0.022787965314248 );
    processed_bin_data[83]( 0.001904, 0.0228956346064837 ); 
    processed_bin_data[84]( 0.001882, 0.0230293210506793 );
    processed_bin_data[85]( 0.001916, 0.0228236865571374 ); 
    processed_bin_data[86]( 0.001865, 0.0231342393324401 );
    processed_bin_data[87]( 0.001959, 0.0225713208013105 ); 
    processed_bin_data[88]( 0.002048, 0.0220744478979656 );
    processed_bin_data[89]( 0.00197, 0.0225080921714385 ); 
    processed_bin_data[90]( 0.001971, 0.0225023703582586 );
    processed_bin_data[91]( 0.002108, 0.0217573735020517 ); 
    processed_bin_data[92]( 0.00212, 0.02169557819482 );
    processed_bin_data[93]( 0.002213, 0.0212338240178742 ); 
    processed_bin_data[94]( 0.002367, 0.0205298735419099 );
    processed_bin_data[95]( 0.002477, 0.0200677395430422 ); 
    processed_bin_data[96]( 0.00272, 0.019148030155176 );
    processed_bin_data[97]( 0.002917, 0.0184883196548874 ); 
    processed_bin_data[98]( 0.003067, 0.0180291851213401 );
    processed_bin_data[99]( 0.00333, 0.0173002976939791 ); 
    processed_bin_data[100]( 0.003959, 0.0158615584869762 );
    processed_bin_data[101]( 0.00447, 0.0149235936199174 ); 
    processed_bin_data[102]( 0.004949, 0.014179598810572 );
    processed_bin_data[103]( 0.005865, 0.013019331158021 ); 
    processed_bin_data[104]( 0.00677, 0.0121124104720988 );
    processed_bin_data[105]( 0.00779, 0.0112858187452076 ); 
    processed_bin_data[106]( 0.009232, 0.0103594831345274 );
    processed_bin_data[107]( 0.010558, 0.00968064605935674 ); 
    processed_bin_data[108]( 0.01204, 0.00905850309959188 );
    processed_bin_data[109]( 0.01351, 0.00854512989975582 );
    
    Teuchos::Array<Utility::Quad<double,double,double,double> >
      raw_total_data( 1 ), raw_total_data_result;
    raw_total_data[0]( 673536, 673536, 673536, 673536 );
    
    Teuchos::Array<Utility::Quad<double,double,double,double> >
      processed_total_data( 1 ), processed_total_data_result;
    processed_total_data[0]( 0.673536, 
			     0.000696205166857844, 
			     5.47826511834568e-07, 
			     6572.10628209639 );
    
    MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( 
	 "FacemcH1-2500K.h5",
	 MonteCarlo::EstimatorHDF5FileHandler::READ_ONLY_ESTIMATOR_HDF5_FILE );

    // Check the dimension ordering
    hdf5_file_handler.getEstimatorDimensionOrdering( 
					       1u, dimension_ordering_result );

    TEST_EQUALITY_CONST( dimension_ordering.size(), 1 );
    TEST_EQUALITY_CONST( dimension_ordering[0], MonteCarlo::ENERGY_DIMENSION );
    
    // Check the energy bins
    hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
						      1u, energy_bins_result );

    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( energy_bins,
					  energy_bins_result,
					  1e-15 );
    
    // Check the raw entity bin data
    hdf5_file_handler.getRawEstimatorEntityBinData( 
						 1u, 1u, raw_bin_data_result );
    
    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					  raw_bin_data_result,
					  1e-15 );
    
    // Check the processed entity bin data
    hdf5_file_handler.getProcessedEstimatorEntityBinData( 
					   1u, 1u, processed_bin_data_result );

    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data,
					  processed_bin_data_result,
					  1e-12 );
    
    // Check the raw total data
    hdf5_file_handler.getRawEstimatorTotalData( 1u, raw_total_data_result );
    
    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
					  raw_total_data_result,
					  1e-15 );
    
    // Check the processed total data (ignore fom)
    hdf5_file_handler.getProcessedEstimatorTotalData( 
					     1u, processed_total_data_result );

    TEST_FLOATING_EQUALITY( processed_total_data[0].first,
			    processed_total_data_result[0].first,
			    1e-15 );
    TEST_FLOATING_EQUALITY( processed_total_data[0].second,
			    processed_total_data_result[0].second,
			    1e-15 );
    TEST_FLOATING_EQUALITY( processed_total_data[0].third,
			    processed_total_data_result[0].third,
			    1e-15 );
  }
  else // Bad return value
    success = false;
      
  if( success )
    out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    out << "\nEnd Result: TEST FAILED" << std::endl;

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstFacemcH1-2500K
//---------------------------------------------------------------------------//

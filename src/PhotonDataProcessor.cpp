//---------------------------------------------------------------------------//
// \file PhotonDataProcessor.cpp
// \author Alex Robinson
// \brief Photon Data Processor definitions
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <cmath>
#include <fstream>

// FACEMC Includes
#include "PhotonDataProcessor.hpp"
#include "FACEMC_Assertion.hpp"
#include "HDF5ScalarTraits.hpp"
#include "HDF5DataFileNames.hpp"

namespace FACEMC{

//! Constructor
PhotonDataProcessor::PhotonDataProcessor( const std::string epdl_file_name,
					  const std::string eadl_file_name,
					  const std::string compton_file_prefix,
					  const double energy_min = 0.001,
					  const double energy_max = 20.0 )
  : DataProcessorBase(), 
    d_epdl_file_name(epdl_file_name), 
    d_eadl_file_name(eadl_file_name),
    d_compton_file_prefix(compton_file_prefix), 
    d_energy_min(energy_min),
    d_energy_max(energy_max)
{ 
  assertAlways( d_energy_min > 0.0 );
  assertAlways( d_energy_min < d_enegy_max );
}
  
/*! Process Photon Data Files
 * \brief Unfortunately, the data file processing must be done in this order.
 * This is because when an HDF5 file is opened, one must specify if the file
 * will be overwritten, appended and/or read. The processEPDLFile() member 
 * function will overwrite an existing HDF5 file while the two other member
 * functions will only append to an existing HDF5 file.
 */
void PhotonDataProcessor::processDataFiles()
{
  processEPDLFile();
  processEADLFile();
  processComptonFiles();
}

//! Process EPDL file
void PhotonDataProcessor::processEPDLFile()
{ 
  // EPDL file
  FILE* epdl;
  epdl = fopen( d_epdl_file_name.c_str() );
  assertAlways( epdl );

  // Atomic number of element currently being processed
  int atomic_number = 0;

  // Information in first header of the EPDL file
  int atomic_number_in_table = 0;
  int outgoing_particle_designator = 0;
  double atomic_weight = 0.0;
  int interpolation_flag = 0;

  // Information in the second header of the EPDL file
  int reaction_type = 0;
  int electron_shell = 0;
  
  // Process every element (Z=1-100) in the EPDL file
  while( !feof(epdl) )
  {
    // Read first table header and determine which element is being processed
    readFirstTableHeader( epdl,
			  atomic_number_in_table,
			  outgoing_particle_designator,
			  atomic_weight,
			  interpolation_flag );

    // If a new element is found, close the current HDF5 file and open a new one
    if( atomic_number != atomic_number_in_table )
    {
      if( atomic_number != 0 )
	closeHDF5File( file_id );
      
      ++atomic_number;

      // Open a new HDF5 file
      std::ostringstream file_number << atomic_number;
      d_hdf5_file_handler.openHDF5FileAndOverwrite( PHOTON_DATA_FILE_PREFIX + 
						    file_number.str() + 
						    DATA_FILE_PREFIX );

      // Create a top level attribute to store the atomic weight
      d_hdf5_file_handler.writeSingleValueAttributeToHDF5File<double>( 
								atomic_weight,
								"Atomic_Weight",
								"Weight" );
    }

    // Read second table header and determine the reaction type
    readSecondTableHeader( epdl,
			   reaction_type,
			   electron_shell );

    // Read and process the data in the current table, then store in the HDF5
    // file
    switch( reaction_type )
    {
  
    
    case 71000:
      // Read in the integrated coherent cross section data
      
      // The interpolation flag should be log-log (5)
      assertAlways( interpolation_flag == 5 );
      
      Teuchos::Array<double> data[2];
      
      readTwoColumnTableInRange<LogLogDataProcessingPolicy>( epdl,
							     data,
							     d_energy_min,
							     d_energy_max );
      d_hdf5_file_handler.write2DArrayToHDF5File<double>( 
						  data,
						  COHERENT_CROSS_SECTION_LOC );
      break;

    case 71010:
      // Average energy of scattered photon from coherent scattering ignored
      
      skipTwoColumnTable( epdl );
      
      break;

    case 72000:
      // Read in the integrated incoherent cross section data
      
      // The interpolation flag should be log-log (5)
      assertAlways( interpolation_flag == 5 );

      Teuchos::Array<double> data[2];

      readTwoColumnTableInRange<LogLogDataProcessingPolicy>( epdl,
							     data,
							     d_energy_min,
							     d_energy_max );
      write2DArrayToHDF5File<double>( file_id,
				      data,
				      INCOHERENT_CROSS_SECTION_LOC );
      break;

    case 72010:
      // Average energy of scattered photon from incoherent scattering 
      // currently ignored ( Yo == 7 )
      // Average energy of scattered electron from incoherent scattering
      // currently ignored ( Yo == 9 )
      
      skipTwoColumnTable( epdl );

      break;

    case 73000:
      // Read the total integrated photoelectric cross section
      if( electron_shell == 0 )
      {
	assertAlways( interpolation_flag == 5 );
	
	Teuchos::Array<double> data[2];
	
	readTwoColumnTableInRange<LogLogDataProcessingPolicy>( epdl,
							       data,
							       d_energy_min,
							       d_energy_max );
	write2DArrayToHDF5File<double>( file_id,
					data,
					PHOTOELECTRIC_CROSS_SECTION_LOC );
      }
      // Read the total integrated photoelectric cross section for a subshell
      else
      {
	assertAlways( interpolation_flag == 5 );
	
	Teuchos::Array<double> data[2];
	
	readTwoColumnTableInRange<LogLogDataProcessingPolicy>( epdl,
							       data,
							       d_energy_min,
							       d_energy_max );
	write2DArrayToHDF5File<double>( file_id,
					data,
					PHOTOELECTRIC_SUBSHELL_CROSS_SECTION_ROOT + intToShellStr( electron_shell ) );
      }
      break;

    case 73011:
      // Average energy to residual atom from photoelectric effect currently
      // ignored.
      
      skipTwoColumnTable( epdl );

      break;

    case 73010:
      // Average energy of secondary photon from photoelectric effect ignored 
      // ( Yo == 7 )
      // Average energy of secondary electron from photoelectric effect ignored
      // ( Yo == 9 )

      skipTwoColumnTable( epdl );

      break;

    case 74000:
      // Read the integrated pair production cross section
      assertAlways( interpolation_flag == 5 );

      Teuchos::Array<double> data[2];
	
      readTwoColumnTableInRange<LogLogDataProcessingPolicy>( epdl,
							     data,
							     d_energy_min,
							     d_energy_max );
      write2DArrayToHDF5File<double>( file_id,
				      data,
				      PAIR_PRODUCTION_CROSS_SECTION_LOC );
      break;

    case 74010:
      // Average energy of secondary positron from pair production ignored
      // ( Yo == 8 )
      // Average energy of secondary electron from pair production ignored
      // ( Yo == 9 )
      
      skipTwoColumnTable( epdl );

      break;

    case 75000:
      // Read the integrated triplet production cross section
      assertAlways( interpolation_flag == 5 );

      Teuchos::Array<double> data[2];
	
      readTwoColumnTableInRange<LogLogDataProcessingPolicy>( epdl,
							     data,
							     d_energy_min,
							     d_energy_max );
      write2DArrayToHDF5File<double>( file_id,
				      data,
				      TRIPLET_PRODUCTION_CROSS_SECTION_LOC );
      break;

    case 75010:
      // Average energy of secondary positron from triplet production ignored
      // ( Yo == 8 )
      // Average energy of secondary electron from triplet production ignored
      // ( Yo == 9 )

      skipTwoColumnTable( epdl );

      break;

    case 93941:
      // Read the atomic form factor
      assertAlways( interpolation_flag == 5 );

      Teuchos::Array<double> data[2];
	
      readTwoColumnTable<LinearLinearDataProcessingPolicy>( epdl,
							    data );
      // For efficient sampling, the atomic form factor must be squared and
      // integrated over its squared argument
      double tmp_integral;
      Teuchos::Array<double> integrated_squared_ff;
      integrated_squared_ff.push_back( 0.0 );
      
      // The form factor has a linear region between the first two arguments
      tmp_integral = 0.5*(data[0][1]*data[0][1]-data[0][0]*data[0][0])*
	(data[1][0]*data[1][0]+data[1][1]*data[1][1]);
      integrated_squared_ff.push_back( tmp_integral );

      // Integrate between data points assuming a functional form of
      // dep = dep_0*indep^exponent
      double exponent;
      double indep_begin, indep_end;
      double dep_begin, dep_end;
      for( int i = 2; i < data[0].size(); ++i )
      {
	indep_begin = data[0][i-1]*data[0][i-1];
	indep_end = data[0][i]*data[0][i];
	dep_begin = data[1][i-1]*data[1][i-1];
	dep_end = data[1][i]*data[1][i];
	exponent = log( dep_end/dep_begin )/log( indep_begin/indep_end );
	
	tmp_integral = dep_begin/((exponent+1)*pow( indep_begin, exponent ))*
	  (pow( indep_end, exponent+1 ) - pow( indep_begin, exponent+1 ));

	integrated_squared_ff.push_back( integrated_squared_ff.back() +
					 tmp_integral );
      }
      
      // Update data array
      data[0][0] = log( std::numeric_limits<double>::min() );
      data[1][0] = log( std::numeric_limits<double>::min() );
      for( int i = 1; i < data[0].size(); ++i )
      {
	// square the argument
	data[0][i] = log( data[0][i]*data[0][i] );

	// replace the form factor with the squared form factor integrated
	// over the squared argument
	data[1][i] = log( integrated_squared_ff[i] );
      }
      
      write2DArrayToHDF5File<double>( file_id,
				      data,
				      ATOMIC_FORM_FACTOR_LOC );
      break;

    case 93942:
      // Read the scattering function
      assertAlways( interpolation_flag == 5 );

      Teuchos::Array<double> data[2];
	
      readTwoColumnTableInRange<LogLogDataProcessingPolicy>( epdl,
							     data );
							     
      write2DArrayToHDF5File<double>( file_id,
				      data,
				      SCATTERING_FUNCTION_LOC );
      break;

    case 93943:
      // Imaginary anomalous scattering factor ignored
       
      skipTwoColumnTable( epdl );

      break;

    case 93944:
      // Real anomalous scattering factor ignored
      
      skipTwoColumnTable( epdl );

      break;

    default:
      // Unknown reaction type found
      bool known_reaction_type = false
      assertAlways( known_reaction_type );
      break;
    }
  }
  
  // Close the last HDF5 file
  closeHDF5File( file_id );

  // Close the EPDL data file
  fclose( epdl );
}

//! Process EADL file 
void PhotonDataProcessor::processEADLFile()
{
  // EPDL file
  FILE* eadl;
  eadl = fopen( d_eadl_file_name.c_str() );
  assertAlways( eadl );

  // HDF5 file information
  hid_t file_id;

  // Atomic number of element currently being processed
  int atomic_number = 0;

  // Information in first header of the EPDL file
  int atomic_number_in_table = 0;
  int outgoing_particle_designator = 0;
  double atomic_weight = 0.0;
  int interpolation_flag = 0;

  // Information in the second header of the EPDL file
  int reaction_type = 0;
  int electron_shell = 0;
  
  // Process every element (Z=1-100) in the EPDL file
  while( !feof(eadl) )
  {
    // Read first table header and determine which element is being processed
    readFirstTableHeader( eadl,
			  atomic_number_in_table,
			  outgoing_particle_designator,
			  atomic_weight,
			  interpolation_flag );

    // If a new element is found, close the current HDF5 file and open a new one
    if( atomic_number != atomic_number_in_table )
    {
      if( atomic_number != 0 )
	closeHDF5File( file_id );
      
      ++atomic_number;

      // Open a new HDF5 file
      std::ostringstream file_number << atomic_number;
      file_id = openHDF5FileAndAppend( PHOTON_DATA_FILE_PREFIX + 
				       file_number.str() + 
				       DATA_FILE_PREFIX );
    }

    // Read second table header and determine the reaction type
    readSecondTableHeader( eadl,
			   reaction_type,
			   electron_shell );

    // Read and process the data in the current table, then store in the HDF5
    // file
    switch( reaction_type )
    {
    case 91912:
      // Read number of electrons per subshell
      
      Teuchos::Array<double> data[2];
	
      readTwoColumnTable<LinearLinearDataProcessingPolicy>( eadl,
							    data );
      
      // Create the electron shell cdf
      double tmp_sum = 0.0;
      for( int i = 0; i < data[0].size(); ++i )
      {
	tmp_sum += data[1][i];
	data[1][i] = tmp_sum;
      }

      // Normalize the cdf
      Teuchos::Array<double> electron_shell_cdf;
      for( int i = 0; i < data[0].size(); ++i )
	electron_shell_cdf.push_back( data[1][i]/tmp_sum );
      
      writeArrayToHDF5File<double>( file_id,
				    electron_shell_cdf,
				    ELECTRON_SHELL_CDF_LOC );

      // Create the Electron Shell Index Map
      Teuchos::Array<int> electron_shell_index_map[2];      
      createElectronShellIndexMap( atomic_number,
				   electron_shell_index_map );

      write2DArrayToHDF5File<int>( file_id,
				   electron_shell_index_map,
				   ELECTRON_SHELL_INDEX_MAP_LOC );      
      break;

    case 91913:
      // Read binding energy per subshell
      
      Teuchos::Array data[2];
      
      readTwoColumnTable<LinearLinearDataProcessingPolicy>( eadl,
							    data );

      write2DArrayToHDF5File<double>( file_id,
				      data,
				      ELECTRON_SHELL_BINDING_ENERGY_LOC );
      break;

    case 91914:
      // Read kinetic energy per subshell
      
      Teuchos::Array data[2];
      
      readTwoColumnTable<LinearLinearDataProcessingPolicy>( eadl,
							    data );

      writeArrayToHDF5File<double>( file_id,
				    data,
				    ELECTRON_SHELL_KINETIC_ENERGY_LOC );
      break;

    case 92931:
      // Read radiative transition probability per subshell
      
      Teuchos::Array data[3];

      readThreeColumnTable( eadl,
			    data );

      // Calculate the total radiative transition probability for
      // this subshell
      double total_radiative_trans_prob = 0.0;
      for( int i = 0; i < data[0].size(); ++i )
	total_radiative_trans_prob += data[1][i];

      writeSingleValueAttribute<double>( file_id,
					 total_radiative_trans_prob,
					 RADIATIVE_TRANSITION_PROBABILITY_ROOT + intToShellStr( electron_shell ),
					 "Total_Radiative_Transition_Probability"
					 );

      write2DArrayToHDF5File<double, 3>( file_id,
					 data,
					 RADIATIVE_TRANSITION_PROBABILITY_ROOT + intToShellStr( electron_shell )
					 );
					 
      break;

    case 92932:
      // Read nonradiative transition probability per subshell
      
      Teuchos::Array<double> data[4];

      readFourColumnTable( eadl,
			   data );

      write2DArrayToHDF5File<double, 4>( file_id,
					 data,
					 NONRADIATIVE_TRANSITION_PROBABILITY_ROOT + intToShellStr( electron_shell )
					 );
					 
      break;

    case 91915:
      // Average radius of subshell ignored
      
      skipTwoColumnTable( eadl );

      break;

    case 91921:
      // Radiative level width ignored
      
      skipTwoColumnTable( eadl );
      
      break;

    case 91922:
      // Nonradiative level width ignored

      skipTwoColumnTable( eadl );

      break;

    case 92933:
      // Average number of photons emitted per initial vacancy ignored 
      // ( Yo == 7 )
      // Average number of electrons emitted per initial vacancy ignored
      // ( Yo == 9 )
      
      skipTwoColumnTable( eadl );
      
      break;
      
    case 92934:
      // Average energy of photons emitted per initial vacancy ignored
      // ( Yo == 7 )
      // Average energy of electrons emitted per initial vacancy ignored
      // ( Yo == 9 )
      
      skipTwoColumnTable( eadl );

      break;

    case 92935:
      // Average energy to residual atom per initial vacancy ignored

      skipTwoColumnTable( eadl );

      break;

    case 93941:
      // Atomic form factor ignored
      
      skipTwoColumnTable( eadl );
      
      break;

    case 93942:
      // Scattering function ignored
      
      skipTwoColumnTable( eadl );

      break;
      
    case 93943:
      // Imaginary anomalous scattering factor ignored
      
      skipTwoColumnTable( eadl );

      break;

    case 93944:
      // Real anomalous scattering factor ignored
      
      skipTwoColumnTable( eadl );

      break;

    default:
      // Unknown reaction type found
      std::cerr << "Unknown reaction type ( " << reaction_type << " )" 
		<< std::endl;
      exit(1);
      break;
    }
  }

  // Close the last HDF5 file
  closeHDF5File( file_id );

  // Close the EPDL data file
  fclose( epdl );
}

//! Process Compton files
void PhotonDataProcessor::processComptonFiles()
{
  // Compton file information
  std::ifstream compton_file_stream;
  std::string compton_file_name;

  // HDF5 file information
  hid_t file_id;
  
  // Compton Profile Q values
  double q_values[] = { 0.00,
			0.05,
			0.10,
			0.15,
			0.20,
			0.30,
			0.40,
			0.50,
			0.60,
			0.70,
			0.80,
			1.00,
			1.20,
			1.40,
			1.60,
			1.80,
			2.00,
			2.40,
			3.00,
			4.00,
			5.00,
			6.00,
			7.00,
			8.00,
			10.00,
			15.00,
			20.00,
			30.00,
			40.00,
			60.00,
			100.00 };

  for( int atomic_number = 1; atomic_number <= 100; ++atomic_number )
  {
    std::ostringstream file_number << atomic_number;
    file_id = openHDF5FileAndAppend( PHOTON_DATA_FILE_PREFIX + 
				       file_number.str() + 
				       DATA_FILE_PREFIX );
    
    compton_file_name = d_compton_file_prefix + file_number.str() + ".dat";
    compton_file_stream.open( compton_file_name.c_str() );
    assertAlways( compton_file_stream.is_open() );

    Teuchos::Array<double> data[31];
    while( !comton_file_stream.eof() )
    {
      //each block of data has 31 evaluated data points
      double data_point;
      for( int i = 0; i < 31; ++i )
      {
	compton_file_stream >> data_point;
	data[i].push_back( data_point );
      }
    }

    Teuchos::Array<double> compton_profile_cdfs[31];
    
    double tmp_integral = 0.0;
    double exponent;
    double indep_begin, indep_end;
    double dep_begin, dep_end;
    // Create the Compton Profile CDFs
    for( int i = 0; i < data[0].size(); ++i )
    {
      compton_profile_cdfs[0][i].push_back( 0.0 );
      tmp_integral = 0.5*( q_values[1]-q_values[0] )*( data[1][i] + data[0][i]);
      compton_profile_cdfs[1].push_back( tmp_integral );
      for( int j = 2; j < 31; ++j )
      {
	indep_begin = q_values[j-1];
	indep_end = q_values[j];
	dep_begin = data[j-1][i];
	dep_end = data[j][i];
	exponent = log( dep_end/dep_begin )/log( indep_begin/indep_end );
	
	tmp_integral = dep_begin/((exponent+1)*pow( indep_begin, exponent ))*
	  (pow( indep_end, exponent+1 ) - pow( indep_begin, exponent+1 ));

	compton_profile_cdfs[j].push_back( compton_profile_cdf.back() +
					  tmp_integral );
      }
      
      // Normalize the CDF
      compton_profile_cdfs[0][i] /= compton_profile_cdf[30][i];
      for( int j = 1; j < 31; ++j )
	compton_profile_cdfs[j][i] = log( compton_profile_cdfs[j][i]/
					  compton_profile_cdf[30][i] );
    }

    write2DArrayToHDF5File<double, 31>( file_id,
					compton_profile_cdfs,
					COMPTON_PROFILE_CDF_LOC );

    // Close the Compton Profile stream
    compton_profile_stream.close();

    // Close the HDF5 file
    closeHDF5File( file_id );
  }
}

//! Create the Electron Shell Index Map
void PhotonDataProcessor::createElectronShellIndexMap( int atomic_number,
						       Teuchos::Array<int>
						       map[2] )
{
  // Non-Relativistic profiles are given for atomic numbers < 36
  if( atomic_number < 36 )
  {
    // Z = 1 or 2
    map[0].push_back( 1 );
    
    map[1].push_back( 0 );
    
    // Z = 3 or 4
    if( atomic_number > 2 )
    {
      map[0].push_back( 3 );
      
      map[1].push_back( 1 );
    }  
    // Z = 5, 6, 7, 8, 9 or 10
    if( atomic_number > 4 )
    {
      map[0].push_back( 5 );
      map[0].push_back( 6 );

      map[1].push_back( 2 );
      map[1].push_back( 2 );
    }
    // Z = 11 or 12
    if( atomic_number > 10 )
    {
      map[0].push_back( 8 );
    
      map[1].push_back( 3 );
    }
    // Z = 13, 14, 15, 16, 17, 18
    if( atomic_number > 12 )
    {
      map[0].push_back( 10 );
      map[0].push_back( 11 );

      map[1].push_back( 4 );
      map[1].push_back( 4 );
    }
    
    // Filling order changes for Z=19 and 20 (4s1/2 before 3d)
    // Need to keep shell indices monotonically increasing  
    if( atomic_number == 19 ||
	atomic_number == 20 )
    {
      map[0].push_back( 16 );
      
      map[1].push_back( 5 );
    }
    // Z = 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 or 30
    if( atomic_number > 20 )
    {
      map[0].push_back( 13 );
      map[0].push_back( 14 );
      map[0].push_back( 16 );
      
      map[1].push_back( 5 );
      map[1].push_back( 5 );
      map[1].push_back( 6 );
    }
    // Z = 31, 32, 33, 34, 35
    if( atomic_number > 30 )
    {
      map[0].push_back( 18 );
      map[0].push_back( 19 );

      map[1].push_back( 7 );
      map[1].push_back( 7 );
    }
  }
  // Relativistic profiles are given for atomic numbers >= 36
  else
  {
    map[0].push_back( 1 );
    map[0].push_back( 3 );
    map[0].push_back( 5 );
    map[0].push_back( 6 );
    map[0].push_back( 8 );
    map[0].push_back( 10 );
    map[0].push_back( 11 );
    map[0].push_back( 13 );
    map[0].push_back( 14 );
    map[0].push_back( 16 );
    map[0].push_back( 18 );
    map[0].push_back( 19 );

    map[1].push_back( 0 );
    map[1].push_back( 1 );
    map[1].push_back( 2 );
    map[1].push_back( 3 );
    map[1].push_back( 4 );
    map[1].push_back( 5 );
    map[1].push_back( 6 );
    map[1].push_back( 7 );
    map[1].push_back( 8 );
    map[1].push_back( 9 );
    map[1].push_back( 10 );
    map[1].push_back( 11 );
    
    // Filling order changes for Z=37 and 38 (5s1/2 before 4d)
    // Need to keep shell indices monotonically increasing 
    if( atomic_number == 37 ||
	atomic_number == 38 )
    {
      map[0].push_back( 27 );
      
      map[1].push_back( 12 );
    }
    else if( atomic_number == 39 ||
	     atomic_number == 40 ||
	     atomic_number == 41 )
    {
      map[0].push_back( 21 );
      map[0].push_back( 22 );
      map[0].push_back( 27 );

      map[1].push_back( 12 );
      map[1].push_back( 12 );
      map[1].push_back( 13 );
    }
    else if( atomic_number == 42 ||
	     atomic_number == 43 ||
	     atomic_number == 44 ||
	     atomic_number == 45 ||
	     atomic_number == 47 ||
	     atomic_number == 48 )
    {
      map[0].push_back( 21 );
      map[0].push_back( 22 );
      map[0].push_back( 27 );

      map[1].push_back( 12 );
      map[1].push_back( 13 );
      map[1].push_back( 14 );
    }
    else if( atomic_number == 46 )
    {
      map[0].push_back( 21 );
      map[0].push_back( 22 );

      map[1].push_back( 12 );
      map[1].push_back( 13 );
    }
    else if( atomic_number == 49 ||
	     atomic_number == 50 )
    {
      map[0].push_back( 21 );
      map[0].push_back( 22 );
      map[0].push_back( 27 );
      map[0].push_back( 29 );
      map[0].push_back( 30 );

      map[1].push_back( 12 );
      map[1].push_back( 13 );
      map[1].push_back( 14 );
      map[1].push_back( 15 );
      map[1].push_back( 15 );
    }
    else if( atomic_number == 51 ||
	     atomic_number == 52 ||
	     atomic_number == 53 ||
	     atomic_number == 54 )
    {
      map[0].push_back( 21 );
      map[0].push_back( 22 );
      map[0].push_back( 27 );
      map[0].push_back( 29 );
      map[0].push_back( 30 );

      map[1].push_back( 12 );
      map[1].push_back( 13 );
      map[1].push_back( 14 );
      map[1].push_back( 15 );
      map[1].push_back( 16 );
    }
    else if( atomic_number == 55 ||
	     atomic_number == 56 )
    {
      map[0].push_back( 21 );
      map[0].push_back( 22 );
      map[0].push_back( 27 );
      map[0].push_back( 29 );
      map[0].push_back( 30 );
      map[0].push_back( 41 );

      map[1].push_back( 12 );
      map[1].push_back( 13 );
      map[1].push_back( 14 );
      map[1].push_back( 15 );
      map[1].push_back( 16 );
      map[1].push_back( 17 );
    }
    else if( atomic_number == 57 )
    {
      map[0].push_back( 21 );
      map[0].push_back( 22 );
      map[0].push_back( 27 );
      map[0].push_back( 29 );
      map[0].push_back( 30 );
      map[0].push_back( 32 );
      map[0].push_back( 33 );
      map[0].push_back( 41 );

      map[1].push_back( 12 );
      map[1].push_back( 13 );
      map[1].push_back( 14 );
      map[1].push_back( 15 );
      map[1].push_back( 16 );
      map[1].push_back( 17 );
      map[1].push_back( 17 );
      map[1].push_back( 18 );
    }
    else if( atomic_number == 58 )
    {
      map[0].push_back( 21 );
      map[0].push_back( 22 );
      map[0].push_back( 24 );
      map[0].push_back( 25 );
      map[0].push_back( 27 );
      map[0].push_back( 29 );
      map[0].push_back( 30 );
      map[0].push_back( 41 );

      map[1].push_back( 12 );
      map[1].push_back( 13 );
      map[1].push_back( 14 );
      map[1].push_back( 14 );
      map[1].push_back( 15 );
      map[1].push_back( 16 );
      map[1].push_back( 17 );
      map[1].push_back( 19 );
    }
    else if( atomic_number == 59 ||
	     atomic_number == 60 ||
	     atomic_number == 61 ||
	     atomic_number == 62 )
    {
      map[0].push_back( 21 );
      map[0].push_back( 22 );
      map[0].push_back( 24 );
      map[0].push_back( 25 );
      map[0].push_back( 27 );
      map[0].push_back( 29 );
      map[0].push_back( 30 );
      map[0].push_back( 41 );

      map[1].push_back( 12 );
      map[1].push_back( 13 );
      map[1].push_back( 14 );
      map[1].push_back( 14 );
      map[1].push_back( 15 );
      map[1].push_back( 16 );
      map[1].push_back( 17 );
      map[1].push_back( 18 );
    }
    else if( atomic_number == 63 ||
	     atomic_number == 65 ||
	     atomic_number == 66 ||
	     atomic_number == 67 ||
	     atomic_number == 68 ||
	     atomic_number == 69 ||
	     atomic_number == 70 )
    {
      map[0].push_back( 21 );
      map[0].push_back( 22 );
      map[0].push_back( 24 );
      map[0].push_back( 25 );
      map[0].push_back( 27 );
      map[0].push_back( 29 );
      map[0].push_back( 30 );
      map[0].push_back( 41 );

      map[1].push_back( 12 );
      map[1].push_back( 13 );
      map[1].push_back( 14 );
      map[1].push_back( 15 );
      map[1].push_back( 16 );
      map[1].push_back( 17 );
      map[1].push_back( 18 );
      map[1].push_back( 19 );
    }
    else if( atomic_number == 64 ||
	     atomic_number == 71 ||
	     atomic_number == 72 ||
	     atomic_number == 73 ||
	     atomic_number == 74 )
    {
      map[0].push_back( 21 );
      map[0].push_back( 22 );
      map[0].push_back( 24 );
      map[0].push_back( 25 );
      map[0].push_back( 27 );
      map[0].push_back( 29 );
      map[0].push_back( 30 );
      map[0].push_back( 32 );
      map[0].push_back( 33 );
      map[0].push_back( 41 );

      map[1].push_back( 12 );
      map[1].push_back( 13 );
      map[1].push_back( 14 );
      map[1].push_back( 15 );
      map[1].push_back( 16 );
      map[1].push_back( 17 );
      map[1].push_back( 18 );
      map[1].push_back( 19 );
      map[1].push_back( 19 );
      map[1].push_back( 20 );
    }
    else if( atomic_number == 75 ||
	     atomic_number == 76 ||
	     atomic_number == 78 ||
	     atomic_number == 79 ||
	     atomic_number == 80 )
    {
      map[0].push_back( 21 );
      map[0].push_back( 22 );
      map[0].push_back( 24 );
      map[0].push_back( 25 );
      map[0].push_back( 27 );
      map[0].push_back( 29 );
      map[0].push_back( 30 );
      map[0].push_back( 32 );
      map[0].push_back( 33 );
      map[0].push_back( 41 );

      map[1].push_back( 12 );
      map[1].push_back( 13 );
      map[1].push_back( 14 );
      map[1].push_back( 15 );
      map[1].push_back( 16 );
      map[1].push_back( 17 );
      map[1].push_back( 18 );
      map[1].push_back( 19 );
      map[1].push_back( 20 );
      map[1].push_back( 21 );
    }
    else if( atomic_number == 77 )
    {
      map[0].push_back( 21 );
      map[0].push_back( 22 );
      map[0].push_back( 24 );
      map[0].push_back( 25 );
      map[0].push_back( 27 );
      map[0].push_back( 29 );
      map[0].push_back( 30 );
      map[0].push_back( 32 );
      map[0].push_back( 33 );

      map[1].push_back( 12 );
      map[1].push_back( 13 );
      map[1].push_back( 14 );
      map[1].push_back( 15 );
      map[1].push_back( 16 );
      map[1].push_back( 17 );
      map[1].push_back( 18 );
      map[1].push_back( 19 );
      map[1].push_back( 20 );
    }
    else if( atomic_number == 81 ||
	     atomic_number == 82 )
    {
      map[0].push_back( 21 );
      map[0].push_back( 22 );
      map[0].push_back( 24 );
      map[0].push_back( 25 );
      map[0].push_back( 27 );
      map[0].push_back( 29 );
      map[0].push_back( 30 );
      map[0].push_back( 32 );
      map[0].push_back( 33 );
      map[0].push_back( 41 );
      map[0].push_back( 43 );
      map[0].push_back( 44 );

      map[1].push_back( 12 );
      map[1].push_back( 13 );
      map[1].push_back( 14 );
      map[1].push_back( 15 );
      map[1].push_back( 16 );
      map[1].push_back( 17 );
      map[1].push_back( 18 );
      map[1].push_back( 19 );
      map[1].push_back( 20 );
      map[1].push_back( 21 );
      map[1].push_back( 22 );
      map[1].push_back( 22 );
    }
    else if( atomic_number == 83 ||
	     atomic_number == 84 ||
	     atomic_number == 85 ||
	     atomic_number == 86 )
    {
      map[0].push_back( 21 );
      map[0].push_back( 22 );
      map[0].push_back( 24 );
      map[0].push_back( 25 );
      map[0].push_back( 27 );
      map[0].push_back( 29 );
      map[0].push_back( 30 );
      map[0].push_back( 32 );
      map[0].push_back( 33 );
      map[0].push_back( 41 );
      map[0].push_back( 43 );
      map[0].push_back( 44 );

      map[1].push_back( 12 );
      map[1].push_back( 13 );
      map[1].push_back( 14 );
      map[1].push_back( 15 );
      map[1].push_back( 16 );
      map[1].push_back( 17 );
      map[1].push_back( 18 );
      map[1].push_back( 19 );
      map[1].push_back( 20 );
      map[1].push_back( 21 );
      map[1].push_back( 22 );
      map[1].push_back( 23 );
    }
    else if( atomic_number == 87 ||
	     atomic_number == 88 )
    {
      map[0].push_back( 21 );
      map[0].push_back( 22 );
      map[0].push_back( 24 );
      map[0].push_back( 25 );
      map[0].push_back( 27 );
      map[0].push_back( 29 );
      map[0].push_back( 30 );
      map[0].push_back( 32 );
      map[0].push_back( 33 );
      map[0].push_back( 41 );
      map[0].push_back( 43 );
      map[0].push_back( 44 );
      map[0].push_back( 58 );

      map[1].push_back( 12 );
      map[1].push_back( 13 );
      map[1].push_back( 14 );
      map[1].push_back( 15 );
      map[1].push_back( 16 );
      map[1].push_back( 17 );
      map[1].push_back( 18 );
      map[1].push_back( 19 );
      map[1].push_back( 20 );
      map[1].push_back( 21 );
      map[1].push_back( 22 );
      map[1].push_back( 23 );
      map[1].push_back( 24 );
    }
    else if( atomic_number == 89 ||
	     atomic_number == 90 )
    {
      map[0].push_back( 21 );
      map[0].push_back( 22 );
      map[0].push_back( 24 );
      map[0].push_back( 25 );
      map[0].push_back( 27 );
      map[0].push_back( 29 );
      map[0].push_back( 30 );
      map[0].push_back( 32 );
      map[0].push_back( 33 );
      map[0].push_back( 41 );
      map[0].push_back( 43 );
      map[0].push_back( 44 );
      map[0].push_back( 46 );
      map[0].push_back( 47 );
      map[0].push_back( 58 );

      map[1].push_back( 12 );
      map[1].push_back( 13 );
      map[1].push_back( 14 );
      map[1].push_back( 15 );
      map[1].push_back( 16 );
      map[1].push_back( 17 );
      map[1].push_back( 18 );
      map[1].push_back( 19 );
      map[1].push_back( 20 );
      map[1].push_back( 21 );
      map[1].push_back( 22 );
      map[1].push_back( 23 );
      map[1].push_back( 24 );
      map[1].push_back( 24 );
      map[1].push_back( 25 );
    }
    else if( atomic_number == 91 ||
	     atomic_number == 92 ||
	     atomic_number == 93 )
    {
      map[0].push_back( 21 );
      map[0].push_back( 22 );
      map[0].push_back( 24 );
      map[0].push_back( 25 );
      map[0].push_back( 27 );
      map[0].push_back( 29 );
      map[0].push_back( 30 );
      map[0].push_back( 32 );
      map[0].push_back( 33 );
      map[0].push_back( 35 );
      map[0].push_back( 36 );
      map[0].push_back( 41 );
      map[0].push_back( 43 );
      map[0].push_back( 44 );
      map[0].push_back( 46 );
      map[0].push_back( 47 );
      map[0].push_back( 58 );

      map[1].push_back( 12 );
      map[1].push_back( 13 );
      map[1].push_back( 14 );
      map[1].push_back( 15 );
      map[1].push_back( 16 );
      map[1].push_back( 17 );
      map[1].push_back( 18 );
      map[1].push_back( 19 );
      map[1].push_back( 20 );
      map[1].push_back( 21 );
      map[1].push_back( 21 );
      map[1].push_back( 22 );
      map[1].push_back( 23 );
      map[1].push_back( 24 );
      map[1].push_back( 25 );
      map[1].push_back( 25 );
      map[1].push_back( 26 );
    }
    else if( atomic_number == 94 )
    {
      map[0].push_back( 21 );
      map[0].push_back( 22 );
      map[0].push_back( 24 );
      map[0].push_back( 25 );
      map[0].push_back( 27 );
      map[0].push_back( 29 );
      map[0].push_back( 30 );
      map[0].push_back( 32 );
      map[0].push_back( 33 );
      map[0].push_back( 35 );
      map[0].push_back( 36 );
      map[0].push_back( 41 );
      map[0].push_back( 43 );
      map[0].push_back( 44 );
      map[0].push_back( 58 );

      map[1].push_back( 12 );
      map[1].push_back( 13 );
      map[1].push_back( 14 );
      map[1].push_back( 15 );
      map[1].push_back( 16 );
      map[1].push_back( 17 );
      map[1].push_back( 18 );
      map[1].push_back( 19 );
      map[1].push_back( 20 );
      map[1].push_back( 21 );
      map[1].push_back( 21 );
      map[1].push_back( 22 );
      map[1].push_back( 23 );
      map[1].push_back( 24 );
      map[1].push_back( 25 );
    }
    else if( atomic_number == 95 ||
	     atomic_number == 98 ||
	     atomic_number == 99 ||
	     atomic_number == 100 )
    {
      map[0].push_back( 21 );
      map[0].push_back( 22 );
      map[0].push_back( 24 );
      map[0].push_back( 25 );
      map[0].push_back( 27 );
      map[0].push_back( 29 );
      map[0].push_back( 30 );
      map[0].push_back( 32 );
      map[0].push_back( 33 );
      map[0].push_back( 35 );
      map[0].push_back( 36 );
      map[0].push_back( 41 );
      map[0].push_back( 43 );
      map[0].push_back( 44 );
      map[0].push_back( 58 );

      map[1].push_back( 12 );
      map[1].push_back( 13 );
      map[1].push_back( 14 );
      map[1].push_back( 15 );
      map[1].push_back( 16 );
      map[1].push_back( 17 );
      map[1].push_back( 18 );
      map[1].push_back( 19 );
      map[1].push_back( 20 );
      map[1].push_back( 21 );
      map[1].push_back( 22 );
      map[1].push_back( 23 );
      map[1].push_back( 24 );
      map[1].push_back( 25 );
      map[1].push_back( 26 );
    }
    else if( atomic_number == 96 )
    {
      map[0].push_back( 21 );
      map[0].push_back( 22 );
      map[0].push_back( 24 );
      map[0].push_back( 25 );
      map[0].push_back( 27 );
      map[0].push_back( 29 );
      map[0].push_back( 30 );
      map[0].push_back( 32 );
      map[0].push_back( 33 );
      map[0].push_back( 35 );
      map[0].push_back( 36 );
      map[0].push_back( 41 );
      map[0].push_back( 43 );
      map[0].push_back( 44 );
      map[0].push_back( 46 );
      map[0].push_back( 47 );
      map[0].push_back( 58 );

      map[1].push_back( 12 );
      map[1].push_back( 13 );
      map[1].push_back( 14 );
      map[1].push_back( 15 );
      map[1].push_back( 16 );
      map[1].push_back( 17 );
      map[1].push_back( 18 );
      map[1].push_back( 19 );
      map[1].push_back( 20 );
      map[1].push_back( 21 );
      map[1].push_back( 22 );
      map[1].push_back( 23 );
      map[1].push_back( 24 );
      map[1].push_back( 25 );
      map[1].push_back( 26 );
      map[1].push_back( 26 );
      map[1].push_back( 27 );
    }
    // WARNING: No Hartree-Fock Compton Profile data for 6d3/2 or 6d5/2
    // map these shells to the 6p+ shell for now...
    else if( atomic_number == 97 )
    {
      map[0].push_back( 21 );
      map[0].push_back( 22 );
      map[0].push_back( 24 );
      map[0].push_back( 25 );
      map[0].push_back( 27 );
      map[0].push_back( 29 );
      map[0].push_back( 30 );
      map[0].push_back( 32 );
      map[0].push_back( 33 );
      map[0].push_back( 35 );
      map[0].push_back( 36 );
      map[0].push_back( 41 );
      map[0].push_back( 43 );
      map[0].push_back( 44 );
      map[0].push_back( 46 );
      map[0].push_back( 47 );
      map[0].push_back( 58 );

      map[1].push_back( 12 );
      map[1].push_back( 13 );
      map[1].push_back( 14 );
      map[1].push_back( 15 );
      map[1].push_back( 16 );
      map[1].push_back( 17 );
      map[1].push_back( 18 );
      map[1].push_back( 19 );
      map[1].push_back( 20 );
      map[1].push_back( 21 );
      map[1].push_back( 22 );
      map[1].push_back( 23 );
      map[1].push_back( 24 );
      map[1].push_back( 25 );
      map[1].push_back( 25 );
      map[1].push_back( 26 );
    }
  }
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end PhotonDataProcessor.cpp
//---------------------------------------------------------------------------//

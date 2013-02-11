//---------------------------------------------------------------------------//
// \file PhotonDataProcessor.cpp
// \author Alex Robinson
// \brief Photon Data Processor definitions
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <cmath>

// FACEMC Includes
#include "PhotonDataProcessor.hpp"
#include "Exception.hpp"
#include "HDF5ScalarTraits.hpp"

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
{ /* ... */ }
  
//! Process Photon Data Files
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
  testFileOpen( epdl,
		"Could not open file " + d_epdl_file_name );

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
      file_id = openHDF5FileAndOverwrite( PHOTON_DATA_FILE_PREFIX + 
					  file_number.str() + 
					  DATA_FILE_PREFIX );

      // Create a top level attribute to store the atomic weight
      writeAtomicWeightAttributeToHDF5File( file_id,
					    atomic_weight );
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
      testInterpFlagException( interpolation_flag == 5,
			       "Unexpected interpolation flag for integrated coherent cross section data" );
      
      Teuchos::Array<double> data[2];
      
      readTwoColumnTableInRange<LogLogDataProcessingPolicy>( epdl,
							     data,
							     d_energy_min,
							     d_energy_max );
      writeDataToHDF5File<double>( file_id,
				   data,
				   "/Basic_Data/Coherent_Cross_Section" );
      break;

    case 71010:
      // Average energy of scattered photon from coherent scattering ignored
      
      skipTwoColumnTable( epdl );
      
      break;

    case 72000:
      // Read in the integrated incoherent cross section data
      
      // The interpolation flag should be log-log (5)
      testInterpFlagException( interpolation_flag == 5,
			       "Unexpected interpolation flag for integrated incoherent cross section data" );

      Teuchos::Array<double> data[2];

      readTwoColumnTableInRange<LogLogDataProcessingPolicy>( epdl,
							     data,
							     d_energy_min,
							     d_energy_max );
      writeDataToHDF5File<double>( file_id,
				   data,
				   "/Basic_Data/Incoherent_Cross_Section" );
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
	testInterpFlagException( interpolation_flag == 5,
				 "Unexpected interpolation flag for total integrated photoelectric cross section data" );
	
	Teuchos::Array<double> data[2];
	
	readTwoColumnTableInRange<LogLogDataProcessingPolicy>( epdl,
							       data,
							       d_energy_min,
							       d_energy_max );
	writeDataToHDF5File<double>( file_id,
				     data,
				     "/Basic_Data/Photoelectric_Cross_Section" );
      }
      // Read the total integrated photoelectric cross section for a subshell
      else
      {
	testInterpFlagException( interpolation_flag == 5,
				 "Unexpected interpolation flag for subshell integrated photoelectric cross section data" );
	
	Teuchos::Array<double> data[2];
	
	readTwoColumnTableInRange<LogLogDataProcessingPolicy>( epdl,
							       data,
							       d_energy_min,
							       d_energy_max );
	std::string location = 
	  "/Fluorescence_Data/Photoelectric_Cross_Section/";
	location += intToShellStr( electron_shell );
	location += intToShellStr( electron_shell );
	writeDataToHDF5File<double>( file_id,
				     data,
				     location );
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
      testInterpFlagException( interpolation_flag == 5,
			       "Unexpected interpolation flag for integrated pair production cross section" );

      Teuchos::Array<double> data[2];
	
      readTwoColumnTableInRange<LogLogDataProcessingPolicy>( epdl,
							     data,
							     d_energy_min,
							     d_energy_max );
      writeDataToHDF5File<double>( file_id,
				   data,
				   "/Basic_Data/Pair_Production_Cross_Section" );
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
      testInterpFlagException( interpolation_flag == 5,
			       "Unexpected interpolation flag for integrated triplet production cross section" );

      Teuchos::Array<double> data[2];
	
      readTwoColumnTableInRange<LogLogDataProcessingPolicy>( epdl,
							     data,
							     d_energy_min,
							     d_energy_max );
      writeDataToHDF5File<double>( file_id,
				   data,
				   "/Basic_Data/Triplet_Production_Cross_Section" );
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
      testInterpFlagException( interpolation_flag == 5,
			       "Unexpected interpolation flag for atomic form factor" );

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
      for( int i = 2; i < data[0].size(); i++ )
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
      for( int i = 1; i < data[0].size(); i++ )
      {
	// square the argument
	data[0][i] = log( data[0][i]*data[0][i] );

	// replace the form factor with the squared form factor integrated
	// over the squared argument
	data[1][i] = log( integrated_squared_ff[i] );
      }
      
      writeDataToHDF5File<double>( file_id,
				   data,
				   "/Basic_Data/Atomic_Form_Factor" );
      break;

    case 93942:
      // Read the scattering function
      testInterpFlagException( interpolation_flag == 5,
			       "Unexpected interpolation flag for scattering function" );

      Teuchos::Array<double> data[2];
	
      readTwoColumnTableInRange<LogLogDataProcessingPolicy>( epdl,
							     data );
							     
      writeDataToHDF5File<double>( file_id,
				   data,
				   "/Basic_Data/Scattering_Function" );
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

//! Process EADL file 
void PhotonDataProcessor::processEADLFile() const
{
  // EPDL file
  FILE* eadl;
  eadl = fopen( d_eadl_file_name.c_str() );
  testFileOpen( eadl,
		"Could not open file " + d_eadl_file_name );

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
      
      // If atomic_number >= 36 there is a chance that the first electron
      // in a p, d or f shell will be split between two subshells (- or +).
      // The compton profile will only be given for the lower subshell
      // so the fraction of the electron in the upper shell must be given
      // to the lower subshell
      
      // Create the electron shell cdf
      double tmp_sum = 0.0;
      for( int i = 0; i < data[0].size(); i++ )
      {
	tmp_sum += data[1][i];
	data[1][i] = tmp_sum;
      }

      // Normalize the cdf
      for( int i = 0; i < data[0].size(); i++ )
	data[1][i] \= tmp_sum;
      
      writeDataToHDF5File<double>( file_id,
				   data,
				   "/Doppler_Data/Electron_Shell_CDF" );
      break;
}

//! Process Compton files
void PhotonDataProcessor::processComptonFiles() const
{}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end PhotonDataProcessor.cpp
//---------------------------------------------------------------------------//

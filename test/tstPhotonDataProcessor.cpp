//---------------------------------------------------------------------------//
// \file   tstPhotonDataProcessor.cpp
// \author Alex Robinson
// \brief  PhotonDataProcessor class unit tests.
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <limits>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_TwoDArray.hpp>

// FACEMC Includes
#include "PhotonDataProcessor.hpp"
#include "HDF5FileHandler.hpp"
#include "Tuple.hpp"
#include "HDF5DataFileNames.hpp"
#include "TestingHelperFunctions.hpp"

//---------------------------------------------------------------------------//
// Test File Names and Info.
//---------------------------------------------------------------------------//
#define COHERENT_DATA_TEST_FILE "test_coherent_cross_section_data.txt"
#define INCOHERENT_DATA_TEST_FILE "test_incoherent_cross_section_data.txt"
#define PHOTOELECTRIC_DATA_TEST_FILE "test_photoelectric_cross_section_data.txt"
#define PAIR_PROD_DATA_TEST_FILE "test_pair_production_cross_section_data.txt"
#define TRIPLET_PROD_DATA_TEST_FILE "test_triplet_production_cross_section_data.txt"
#define FORM_FACTOR_DATA_TEST_FILE "test_form_factor_data.txt"
#define SCAT_FUNC_DATA_TEST_FILE "test_scattering_function_data.txt"
#define EPDL_TEST_FILE "test_epdl_file.txt"
#define SHELL_OCCUP_BIND_DATA_TEST_FILE "test_shell_occupancy_binding_energy_data.txt"
#define KINETIC_ENERGY_DATA_TEST_FILE "test_shell_kinetic_energy_data.txt"
#define SHELL_RAD_TRANS_DATA_TEST_FILE "test_shell_radiative_transition_data.txt"
#define SHELL_NONRAD_TRANS_DATA_TEST_FILE "test_shell_nonradiative_transition_data.txt"
#define EADL_TEST_FILE "test_eadl_file.txt"
#define COMPTON_TEST_FILE_PREFIX "test_compton_profile-"
#define IGNORE "dummy_file.txt"
#define COMPTON_PROFILE_Z_START 5
#define COMPTON_PROFILE_Z_END 6
#define HDF5_TEST_FILE "PhotonData-test.h5"
#define HDF5_COMPLETE_TEST_FILE "PhotonData-5.h5"
#define OUTPUT_DIRECTORY ""
#define ENERGY_MIN 1e-7
#define ENERGY_MAX 1e5
#define SHELL 1
#define ATOMIC_NUMBER 5
#define ATOMIC_WEIGHT 1.0811e1
#define TOL 1e-9

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestingPhotonDataProcessor : public FACEMC::PhotonDataProcessor
{
public:
  TestingPhotonDataProcessor( const std::string epdl_file_name,
			      const std::string eadl_file_name,
			      const std::string compton_file_prefix,
			      const std::string output_directory,
			      const double energy_min,
			      const double energy_max)
    : FACEMC::PhotonDataProcessor( epdl_file_name,
				   eadl_file_name,
				   compton_file_prefix,
				   output_directory,
				   energy_min,
				   energy_max )
  { /* ... */ }

  virtual ~TestingPhotonDataProcessor()
  { /* ... */ }

  using FACEMC::PhotonDataProcessor::processEPDLFile;
  using FACEMC::PhotonDataProcessor::processCoherentCrossSectionData;
  using FACEMC::PhotonDataProcessor::processIncoherentCrossSectionData;
  using FACEMC::PhotonDataProcessor::processTotalPhotoelectricCrossSectionData;
  using FACEMC::PhotonDataProcessor::processShellPhotoelectricCrossSectionData;
  using FACEMC::PhotonDataProcessor::processPairProductionCrossSectionData;
  using FACEMC::PhotonDataProcessor::processTripletProductionCrossSectionData;
  using FACEMC::PhotonDataProcessor::processFormFactorData;
  using FACEMC::PhotonDataProcessor::processScatteringFunctionData;
  using FACEMC::PhotonDataProcessor::processEADLFile;
  using FACEMC::PhotonDataProcessor::processShellOccupancyData;
  using FACEMC::PhotonDataProcessor::processBindingEnergyData;
  using FACEMC::PhotonDataProcessor::processKineticEnergyData;
  using FACEMC::PhotonDataProcessor::processShellRadiativeTransitionData;
  using FACEMC::PhotonDataProcessor::processShellNonradiativeTransitionData;
  using FACEMC::PhotonDataProcessor::processComptonFiles;
  using FACEMC::PhotonDataProcessor::d_hdf5_file_handler;
};

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the PhotonDataProcessor can process coherent cross section data
TEUCHOS_UNIT_TEST( PhotonDataProcessor, process_coherent_xs_data )
{
  TestingPhotonDataProcessor photon_data_processor( COHERENT_DATA_TEST_FILE,
						    IGNORE,
						    IGNORE,
						    OUTPUT_DIRECTORY,
						    ENERGY_MIN,
						    ENERGY_MAX );

  photon_data_processor.d_hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE );

  photon_data_processor.processCoherentCrossSectionData();

  photon_data_processor.d_hdf5_file_handler.closeHDF5File();
  
  // Read the processed data back in
  FACEMC::HDF5FileHandler hdf5_file_handler;
  hdf5_file_handler.openHDF5FileAndReadOnly( HDF5_TEST_FILE );

  Teuchos::Array<FACEMC::Trip<double,double,double> > data;

  hdf5_file_handler.readArrayFromDataSet( data,
					  COHERENT_CROSS_SECTION_LOC );

  // Fill the reference data array
  Teuchos::Array<FACEMC::Trip<double,double,double> > ref_data;
  ref_data.resize( data.size() );
  
  ref_data[0].first = -13.815510557964;
  ref_data[0].second = -7.1676030125713;
  ref_data[0].third = 4.1407348086216;
  
  ref_data[1].first = -13.75691434492;
  ref_data[1].second = -6.9249716335666;
  ref_data[1].third = 4.1875290259276;

  ref_data[2].first = -13.633827538325;
  ref_data[2].second = -6.4095420582413;
  ref_data[2].third = 4.275960075706;
  
  ref_data[3].first = -13.510741306417;
  ref_data[3].second = -5.8832302447336;
  ref_data[3].third = 4.3799023784988;

  ref_data[4].first = -13.387654671446;
  ref_data[4].second = -5.3441227994627;
  ref_data[4].third = 0.0;

  TEST_COMPARE_FLOATING_TRIP_ARRAYS( data, ref_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataProcessor can process incoherent cross section data
TEUCHOS_UNIT_TEST( PhotonDataProcessor, process_incoherent_xs_data )
{
  TestingPhotonDataProcessor photon_data_processor( INCOHERENT_DATA_TEST_FILE,
						    IGNORE,
						    IGNORE,
						    OUTPUT_DIRECTORY,
						    ENERGY_MIN,
						    ENERGY_MAX );

  photon_data_processor.d_hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE );

  photon_data_processor.processIncoherentCrossSectionData();

  photon_data_processor.d_hdf5_file_handler.closeHDF5File();
  
  // Read the processed data back in
  FACEMC::HDF5FileHandler hdf5_file_handler;
  hdf5_file_handler.openHDF5FileAndReadOnly( HDF5_TEST_FILE );

  Teuchos::Array<FACEMC::Trip<double,double,double> > data;

  hdf5_file_handler.readArrayFromDataSet( data,
					  INCOHERENT_CROSS_SECTION_LOC );

  // Fill the reference data array
  Teuchos::Array<FACEMC::Trip<double,double,double> > ref_data;
  ref_data.resize( data.size() );
  
  ref_data[0].first = -13.815510557964;
  ref_data[0].second = -14.894173171325;
  ref_data[0].third = 2.0001517308519;

  ref_data[1].first = -13.585272234174;
  ref_data[1].second = -14.433661589488;
  ref_data[1].third = 1.9997755035229;

  ref_data[2].first = -13.354989244108;
  ref_data[2].second = -13.973147307076;
  ref_data[2].third = 1.9997052677075;

  ref_data[3].first = -13.124716142988;
  ref_data[3].second = -13.512668973755;
  ref_data[3].third = 2.0001780425014;

  ref_data[4].first = -12.894471119068;
  ref_data[4].second = -13.052137932515;
  ref_data[4].third = 0.0;

  TEST_COMPARE_FLOATING_TRIP_ARRAYS( data, ref_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataProcessor can process photoelectric cross section 
// data
TEUCHOS_UNIT_TEST( PhotonDataProcessor, process_total_photoelectric_xs_data )
{
  TestingPhotonDataProcessor photon_data_processor( PHOTOELECTRIC_DATA_TEST_FILE,
						    IGNORE,
						    IGNORE,
						    OUTPUT_DIRECTORY,
						    ENERGY_MIN,
						    ENERGY_MAX );

  photon_data_processor.d_hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE );

  photon_data_processor.processTotalPhotoelectricCrossSectionData();

  photon_data_processor.d_hdf5_file_handler.closeHDF5File();
  
  // Read the processed data back in
  FACEMC::HDF5FileHandler hdf5_file_handler;
  hdf5_file_handler.openHDF5FileAndReadOnly( HDF5_TEST_FILE );

  Teuchos::Array<FACEMC::Trip<double,double,double> > data;

  hdf5_file_handler.readArrayFromDataSet( data,
					  PHOTOELECTRIC_CROSS_SECTION_LOC );

  // Fill the reference data array
  Teuchos::Array<FACEMC::Trip<double,double,double> > ref_data;
  ref_data.resize( data.size() );
  
  ref_data[0].first = -11.919391073412;
  ref_data[0].second = 15.872476914244;
  ref_data[0].third = -1.0882888850399;

  ref_data[1].first = -11.917890698037;
  ref_data[1].second = 15.8708440724;
  ref_data[1].third = std::numeric_limits<double>::infinity();

  ref_data[2].first = -11.917890698037;
  ref_data[2].second = 16.276682760974;
  ref_data[2].third = -1.0988325647451;

  ref_data[3].first = -11.858313206861;
  ref_data[3].second = 16.211217073544;
  ref_data[3].third = -1.1642743144669;

  ref_data[4].first = -11.841429531942;
  ref_data[4].second = 16.191559844502;
  ref_data[4].third = 0.0;

  TEST_COMPARE_FLOATING_TRIP_ARRAYS( data, ref_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataProcessor can process photoelectric cross section 
// data
TEUCHOS_UNIT_TEST( PhotonDataProcessor, process_shell_photoelectric_xs_data )
{
  TestingPhotonDataProcessor photon_data_processor( PHOTOELECTRIC_DATA_TEST_FILE,
						    IGNORE,
						    IGNORE,
						    OUTPUT_DIRECTORY,
						    ENERGY_MIN,
						    ENERGY_MAX );

  photon_data_processor.d_hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE );

  photon_data_processor.processShellPhotoelectricCrossSectionData( SHELL );

  photon_data_processor.d_hdf5_file_handler.closeHDF5File();
  
  // Read the processed data back in
  FACEMC::HDF5FileHandler hdf5_file_handler;
  hdf5_file_handler.openHDF5FileAndReadOnly( HDF5_TEST_FILE );

  Teuchos::Array<FACEMC::Trip<double,double,double> > data;

  std::stringstream shell_number;
  shell_number <<  SHELL;
  hdf5_file_handler.readArrayFromDataSet( data,
					  PHOTOELECTRIC_SUBSHELL_CROSS_SECTION_ROOT + shell_number.str() );

  // Fill the reference data array
  Teuchos::Array<FACEMC::Trip<double,double,double> > ref_data;
  ref_data.resize( data.size() );
  
  ref_data[0].first = -11.919391073412;
  ref_data[0].second = 15.872476914244;
  ref_data[0].third = -1.0882888850399;

  ref_data[1].first = -11.917890698037;
  ref_data[1].second = 15.8708440724;
  ref_data[1].third = std::numeric_limits<double>::infinity();

  ref_data[2].first = -11.917890698037;
  ref_data[2].second = 16.276682760974;
  ref_data[2].third = -1.0988325647451;

  ref_data[3].first = -11.858313206861;
  ref_data[3].second = 16.211217073544;
  ref_data[3].third = -1.1642743144669;

  ref_data[4].first = -11.841429531942;
  ref_data[4].second = 16.191559844502;
  ref_data[4].third = 0.0;

  TEST_COMPARE_FLOATING_TRIP_ARRAYS( data, ref_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataProcessor can process pair production cross section 
// data
TEUCHOS_UNIT_TEST( PhotonDataProcessor, process_pair_production_xs_data )
{
  TestingPhotonDataProcessor photon_data_processor( PAIR_PROD_DATA_TEST_FILE,
						    IGNORE,
						    IGNORE,
						    OUTPUT_DIRECTORY,
						    ENERGY_MIN,
						    ENERGY_MAX );

  photon_data_processor.d_hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE );

  photon_data_processor.processPairProductionCrossSectionData();

  photon_data_processor.d_hdf5_file_handler.closeHDF5File();
  
  // Read the processed data back in
  FACEMC::HDF5FileHandler hdf5_file_handler;
  hdf5_file_handler.openHDF5FileAndReadOnly( HDF5_TEST_FILE );

  Teuchos::Array<FACEMC::Trip<double,double,double> > data;

  hdf5_file_handler.readArrayFromDataSet( data,
					  PAIR_PRODUCTION_CROSS_SECTION_LOC );

  // Fill the reference data array
  Teuchos::Array<FACEMC::Trip<double,double,double> > ref_data;
  ref_data.resize( data.size() );
  
  ref_data[0].first = 0.021761491781513;
  ref_data[0].second = -20.806526800989;
  ref_data[0].third = 0.0;

  ref_data[1].first = 0.024809678908574;
  ref_data[1].second = -20.806526800989;
  ref_data[1].third = 651.405719112;

  ref_data[2].first = 0.028344473009143;
  ref_data[2].second = -18.503941707995;
  ref_data[2].third = 301.37598804572;

  ref_data[3].first = 0.03598471371951;
  ref_data[3].second = -16.201356615001;
  ref_data[3].third = 138.01459418352;

  ref_data[4].first = 0.052668348567084;
  ref_data[4].second = -13.898771522007;
  ref_data[4].third = 0.0;

  TEST_COMPARE_FLOATING_TRIP_ARRAYS( data, ref_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataProcessor can process triplet production cross 
// section data
TEUCHOS_UNIT_TEST( PhotonDataProcessor, process_triplet_production_xs_data )
{
  TestingPhotonDataProcessor photon_data_processor( TRIPLET_PROD_DATA_TEST_FILE,
						    IGNORE,
						    IGNORE,
						    OUTPUT_DIRECTORY,
						    ENERGY_MIN,
						    ENERGY_MAX );

  photon_data_processor.d_hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE );

  photon_data_processor.processTripletProductionCrossSectionData();

  photon_data_processor.d_hdf5_file_handler.closeHDF5File();
  
  // Read the processed data back in
  FACEMC::HDF5FileHandler hdf5_file_handler;
  hdf5_file_handler.openHDF5FileAndReadOnly( HDF5_TEST_FILE );

  Teuchos::Array<FACEMC::Trip<double,double,double> > data;

  hdf5_file_handler.readArrayFromDataSet( data,
					  TRIPLET_PRODUCTION_CROSS_SECTION_LOC );

  // Fill the reference data array
  Teuchos::Array<FACEMC::Trip<double,double,double> > ref_data;
  ref_data.resize( data.size() );
  
  ref_data[0].first = 0.71490867234146;
  ref_data[0].second = -16.807268738696;
  ref_data[0].third = 0.0;

  ref_data[1].first = 0.73515726901701;
  ref_data[1].second = -16.807268738696;
  ref_data[1].third = 96.363896620944;

  ref_data[2].first = 0.75905195544767;
  ref_data[2].second = -14.504683645702;
  ref_data[2].third = 56.900144336389;

  ref_data[3].first = 0.77426623184474;
  ref_data[3].second = -13.638989122735;
  ref_data[3].third = 46.249681851326;

  ref_data[4].first = 0.78138696940935;
  ref_data[4].second = -13.309657275825;
  ref_data[4].third = 0.0;

  TEST_COMPARE_FLOATING_TRIP_ARRAYS( data, ref_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataProcessor can process form factor data
TEUCHOS_UNIT_TEST( PhotonDataProcessor, process_form_factor_data )
{
  TestingPhotonDataProcessor photon_data_processor( FORM_FACTOR_DATA_TEST_FILE,
						    IGNORE,
						    IGNORE,
						    OUTPUT_DIRECTORY,
						    ENERGY_MIN,
						    ENERGY_MAX );

  photon_data_processor.d_hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE );

  photon_data_processor.processFormFactorData();

  photon_data_processor.d_hdf5_file_handler.closeHDF5File();
  
  // Read the processed data back in
  FACEMC::HDF5FileHandler hdf5_file_handler;
  hdf5_file_handler.openHDF5FileAndReadOnly( HDF5_TEST_FILE );

  Teuchos::Array<FACEMC::Quad<double,double,double,double> > data;

  hdf5_file_handler.readArrayFromDataSet( data,
					  ATOMIC_FORM_FACTOR_LOC );

  // Fill the reference data array
  Teuchos::Array<FACEMC::Quad<double,double,double,double> > ref_data;
  ref_data.resize( data.size() );
  
  ref_data[0].first = 0.0;
  ref_data[0].second = 0.0;
  ref_data[0].third = 1.0023608689564e-12;
  ref_data[0].fourth = 0.0;

  ref_data[1].first = 1e10;
  ref_data[1].second = 0.01002360868954;
  ref_data[1].third = 1.0023608689564e-12;
  ref_data[1].fourth = -4.8433392241667e-27;

  ref_data[2].first = 2.5e11;
  ref_data[2].second = 0.25045072906964;
  ref_data[2].third = 1.0011984675426e-12;
  ref_data[2].fourth = -4.8928833764073e-27;
  
  ref_data[3].first = 7.65625e11;
  ref_data[3].second = 0.76604325554688;
  ref_data[3].third = 9.9867557455164e-13;
  ref_data[3].fourth = -3.92645590784e-27;
  
  ref_data[4].first = 1e12;
  ref_data[4].second = 1.0;
  ref_data[4].third = 9.9775531144824e-13;
  ref_data[4].fourth = 0.0;

  TEST_COMPARE_FLOATING_QUAD_ARRAYS( data, ref_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataProcessor can process scattering function data
TEUCHOS_UNIT_TEST( PhotonDataProcessor, process_scattering_function_data )
{
  TestingPhotonDataProcessor photon_data_processor( SCAT_FUNC_DATA_TEST_FILE,
						    IGNORE,
						    IGNORE,
						    OUTPUT_DIRECTORY,
						    ENERGY_MIN,
						    ENERGY_MAX );

  photon_data_processor.d_hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE );

  photon_data_processor.processScatteringFunctionData();

  photon_data_processor.d_hdf5_file_handler.closeHDF5File();
  
  // Read the processed data back in
  FACEMC::HDF5FileHandler hdf5_file_handler;
  hdf5_file_handler.openHDF5FileAndReadOnly( HDF5_TEST_FILE );

  Teuchos::Array<FACEMC::Trip<double,double,double> > data;

  hdf5_file_handler.readArrayFromDataSet( data,
					  SCATTERING_FUNCTION_LOC );

  // Fill the reference data array
  Teuchos::Array<FACEMC::Trip<double,double,double> > ref_data;
  ref_data.resize( data.size() );

  ref_data[0].first = std::numeric_limits<double>::infinity()*-1;
  ref_data[0].second = std::numeric_limits<double>::infinity()*-1;
  ref_data[0].third = 0.0;
  
  ref_data[1].first = 2.302585092994;
  ref_data[1].second = -27.183135291936;
  ref_data[1].third = 1.9999999999999;

  ref_data[2].first = 4.6051701859881;
  ref_data[2].second = -22.577965105948;
  ref_data[2].third = 2.0;

  ref_data[3].first = 6.9077552789821;
  ref_data[3].second = -17.97279491996;
  ref_data[3].third = 1.9999999999999;

  ref_data[4].first = 9.2103403719762;
  ref_data[4].second = -13.367624733972;
  ref_data[4].third = 0.0;

  TEST_COMPARE_FLOATING_TRIP_ARRAYS( data, ref_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataProcessor can process an EPDL data file
TEUCHOS_UNIT_TEST( PhotonDataProcessor, process_epdl_file_test )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    IGNORE,
						    IGNORE,
						    OUTPUT_DIRECTORY,
						    ENERGY_MIN,
						    ENERGY_MAX );

  // This member function will throw an exception and exit if an error occurs
  // so no TEST macro is needed.
  photon_data_processor.processEPDLFile();

  // Read the top level attribute data back in
  FACEMC::HDF5FileHandler hdf5_file_handler;
  hdf5_file_handler.openHDF5FileAndReadOnly( HDF5_COMPLETE_TEST_FILE );

  // Read in the atomic weight attribute
  double atomic_weight;
  hdf5_file_handler.readValueFromGroupAttribute( atomic_weight,
						 ROOT,
						 ATOMIC_WEIGHT_ATTRIBUTE );

  TEST_EQUALITY_CONST( atomic_weight, ATOMIC_WEIGHT );

  // Read in the energy limits attribute
  Teuchos::Array<double> energy_limits;
  hdf5_file_handler.readArrayFromGroupAttribute( energy_limits,
						 ROOT,
						 ENERGY_LIMITS_ATTRIBUTE );

  TEST_EQUALITY_CONST( energy_limits[0], ENERGY_MIN);
  TEST_EQUALITY_CONST( energy_limits[1], ENERGY_MAX);

  // Read in the photoelectric subshell attribute
  Teuchos::Array<unsigned int> photoelectric_subshells;
  hdf5_file_handler.readArrayFromGroupAttribute( photoelectric_subshells,
						 PHOTOELECTRIC_SUBSHELL_CROSS_SECTION_ROOT,
						 PHOTOELECTRIC_SHELL_ATTRIBUTE );

  // Fill the reference photoelectric subshell attribute array
  Teuchos::Array<unsigned int> ref_photoelectric_subshells( 4 );
  ref_photoelectric_subshells[0] = 1;
  ref_photoelectric_subshells[1] = 3;
  ref_photoelectric_subshells[2] = 5;
  ref_photoelectric_subshells[3] = 6;
  
  TEST_COMPARE_ARRAYS( photoelectric_subshells, ref_photoelectric_subshells );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataProcessor can process shell occupancy data
TEUCHOS_UNIT_TEST( PhotonDataProcessor, process_shell_occupancy_data_binding_energy_data_test )
{
  TestingPhotonDataProcessor photon_data_processor( IGNORE,
						    SHELL_OCCUP_BIND_DATA_TEST_FILE,
						    IGNORE,
						    OUTPUT_DIRECTORY,
						    ENERGY_MIN,
						    ENERGY_MAX );

  photon_data_processor.d_hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE );
  
  Teuchos::Array<FACEMC::Quad<double,unsigned int,unsigned int,double> > 
    data;

  photon_data_processor.processShellOccupancyData( ATOMIC_NUMBER,
						   data );

  photon_data_processor.processBindingEnergyData( data );

  photon_data_processor.d_hdf5_file_handler.closeHDF5File();
  
  // Read the processed data back in
  FACEMC::HDF5FileHandler hdf5_file_handler;
  hdf5_file_handler.openHDF5FileAndReadOnly( HDF5_TEST_FILE );

  Teuchos::Array<FACEMC::Pair<unsigned int, double> > binding_energy_data;

  hdf5_file_handler.readArrayFromDataSet( binding_energy_data,
					  ELECTRON_SHELL_BINDING_ENERGY_LOC );

  Teuchos::Array<FACEMC::Quad<double,unsigned int,unsigned int,double> >
    occupancy_data;

  hdf5_file_handler.readArrayFromDataSet( occupancy_data,
					  ELECTRON_SHELL_CDF_LOC );

  // Fill the reference binding energy data array
  Teuchos::Array<FACEMC::Pair<unsigned int, double> > ref_binding_energy_data;
  ref_binding_energy_data.resize( binding_energy_data.size() );
  
  ref_binding_energy_data[0].first = 1;
  ref_binding_energy_data[0].second = 1.95610e-4;

  ref_binding_energy_data[1].first = 3;
  ref_binding_energy_data[1].second = 1.2580e-5;

  ref_binding_energy_data[2].first = 5;
  ref_binding_energy_data[2].second = 6.670e-6;

  ref_binding_energy_data[3].first = 6;
  ref_binding_energy_data[3].second = 6.660e-6;

  TEST_COMPARE_FLOATING_PAIR_ARRAYS( binding_energy_data, 
				     ref_binding_energy_data, 
				     TOL );

  // Fill the reference occupancy data array
  Teuchos::Array<FACEMC::Quad<double,unsigned int, unsigned int,double> > 
    ref_occupancy_data;
  ref_occupancy_data.resize( occupancy_data.size() );
  
  ref_occupancy_data[0].first = 0.4;
  ref_occupancy_data[0].second = 1;
  ref_occupancy_data[0].third = 0;
  ref_occupancy_data[0].fourth = 1.95610e-4;

  ref_occupancy_data[1].first = 0.8;
  ref_occupancy_data[1].second = 3;
  ref_occupancy_data[1].third = 1;
  ref_occupancy_data[1].fourth = 1.2580e-5;

  ref_occupancy_data[2].first = 0.866;
  ref_occupancy_data[2].second = 5;
  ref_occupancy_data[2].third = 2;
  ref_occupancy_data[2].fourth = 6.670e-6;

  ref_occupancy_data[3].first = 1.0;
  ref_occupancy_data[3].second = 6;
  ref_occupancy_data[3].third = 2;
  ref_occupancy_data[3].fourth = 6.660e-6;

  TEST_COMPARE_FLOATING_QUAD_ARRAYS( occupancy_data, 
				     ref_occupancy_data, 
				     TOL );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataProcessor can process kinetic energy data
TEUCHOS_UNIT_TEST( PhotonDataProcessor, process_kinetic_energy_data_test )
{
  TestingPhotonDataProcessor photon_data_processor( IGNORE,
						    KINETIC_ENERGY_DATA_TEST_FILE,
						    IGNORE,
						    OUTPUT_DIRECTORY,
						    ENERGY_MIN,
						    ENERGY_MAX );

  photon_data_processor.d_hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE );

  photon_data_processor.processKineticEnergyData();

  photon_data_processor.d_hdf5_file_handler.closeHDF5File();
  
  // Read the processed data back in
  FACEMC::HDF5FileHandler hdf5_file_handler;
  hdf5_file_handler.openHDF5FileAndReadOnly( HDF5_TEST_FILE );

  Teuchos::Array<FACEMC::Pair<unsigned int, double> > data;

  hdf5_file_handler.readArrayFromDataSet( data,
					  ELECTRON_SHELL_KINETIC_ENERGY_LOC );

  // Fill the reference data array
  Teuchos::Array<FACEMC::Pair<unsigned int, double> > ref_data;
  ref_data.resize( data.size() );
  
  ref_data[0].first = 1;
  ref_data[0].second = 3.06230e-4;

  ref_data[1].first = 3;
  ref_data[1].second = 3.0530e-5;

  ref_data[2].first = 5;
  ref_data[2].second = 2.1730e-5;

  ref_data[3].first = 6;
  ref_data[3].second = 2.1710e-5;

  TEST_COMPARE_FLOATING_PAIR_ARRAYS( data, ref_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataProcessor can process radiative transition data
TEUCHOS_UNIT_TEST( PhotonDataProcessor, process_shell_radiative_transition_data_test )
{
  TestingPhotonDataProcessor photon_data_processor( IGNORE,
						    SHELL_RAD_TRANS_DATA_TEST_FILE,
						    IGNORE,
						    OUTPUT_DIRECTORY,
						    ENERGY_MIN,
						    ENERGY_MAX );

  photon_data_processor.d_hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE );

  photon_data_processor.processShellRadiativeTransitionData( SHELL );

  photon_data_processor.d_hdf5_file_handler.closeHDF5File();
  
  // Read the processed data back in
  FACEMC::HDF5FileHandler hdf5_file_handler;
  hdf5_file_handler.openHDF5FileAndReadOnly( HDF5_TEST_FILE );

  Teuchos::Array<FACEMC::Trip<double, unsigned int, double> > data;

  std::stringstream shell_number;
  shell_number << SHELL;
  hdf5_file_handler.readArrayFromDataSet( data,
					  TRANSITION_PROBABILITY_ROOT +
					  (RADIATIVE_TRANSITION_SUB_ROOT +
					   shell_number.str()) );

  // Fill the reference data array
  Teuchos::Array<FACEMC::Trip<double, unsigned int, double> > ref_data;
  ref_data.resize( data.size() );
  
  ref_data[0].first = 0.3338041767137;
  ref_data[0].second = 5;
  ref_data[0].third = 2.82020e-4;

  ref_data[1].first = 1.0;
  ref_data[1].second = 6;
  ref_data[1].third = 2.82030e-4;

  TEST_COMPARE_FLOATING_TRIP_ARRAYS( data, ref_data, TOL );

  // Read in the total radiative transition probability attribute
  double total_rad_trans_prob;
  hdf5_file_handler.readValueFromDataSetAttribute( total_rad_trans_prob,
						   TRANSITION_PROBABILITY_ROOT +
						   (RADIATIVE_TRANSITION_SUB_ROOT +
						    shell_number.str()),
						   TOTAL_RAD_TRANS_PROB_ATTRIBUTE );
  
  TEST_FLOATING_EQUALITY( total_rad_trans_prob, 1.682088e-3, TOL )
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataProcessor can process radiative transition data
TEUCHOS_UNIT_TEST( PhotonDataProcessor, process_shell_nonradiative_transition_data_test )
{
  TestingPhotonDataProcessor photon_data_processor( IGNORE,
						    SHELL_NONRAD_TRANS_DATA_TEST_FILE,
						    IGNORE,
						    OUTPUT_DIRECTORY,
						    ENERGY_MIN,
						    ENERGY_MAX );

  photon_data_processor.d_hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE );

  photon_data_processor.processShellNonradiativeTransitionData( SHELL );

  photon_data_processor.d_hdf5_file_handler.closeHDF5File();
  
  // Read the processed data back in
  FACEMC::HDF5FileHandler hdf5_file_handler;
  hdf5_file_handler.openHDF5FileAndReadOnly( HDF5_TEST_FILE );

  Teuchos::Array<FACEMC::Quad<double, unsigned int, unsigned int, double> > 
    data;

  std::stringstream shell_number;
  shell_number << SHELL;
  hdf5_file_handler.readArrayFromDataSet( data,
					  TRANSITION_PROBABILITY_ROOT +
					  (NONRADIATIVE_TRANSITION_SUB_ROOT +
					   shell_number.str()) );

  // Fill the reference data array
  Teuchos::Array<FACEMC::Quad<double, unsigned int, unsigned int, double> > 
    ref_data;
  ref_data.resize( data.size() );
  
  ref_data[0].first = 0.4143057462596;
  ref_data[0].second = 3;
  ref_data[0].third = 3;
  ref_data[0].fourth = 2.55890e-4;

  ref_data[1].first = 0.55072516552537;
  ref_data[1].second = 3;
  ref_data[1].third = 5;
  ref_data[1].fourth = 2.64460e-4;

  ref_data[2].first = 0.82228084614458;
  ref_data[2].second = 3;
  ref_data[2].third = 6;
  ref_data[2].fourth = 2.64470e-4;

  ref_data[3].first = 0.82649541386741;
  ref_data[3].second = 5;
  ref_data[3].third = 5;
  ref_data[3].fourth = 2.73030e-4;

  ref_data[4].first = 0.93669273490615;
  ref_data[4].second = 5;
  ref_data[4].third = 6;
  ref_data[4].fourth = 2.73040e-4;

  ref_data[5].first = 1.0;
  ref_data[5].second = 6;
  ref_data[5].third = 6;
  ref_data[5].fourth = 2.73050e-4;

  TEST_COMPARE_FLOATING_QUAD_ARRAYS( data, ref_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataProcessor can process an EADL data file
TEUCHOS_UNIT_TEST( PhotonDataProcessor, process_eadl_file_test )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    IGNORE,
						    OUTPUT_DIRECTORY,
						    ENERGY_MIN,
						    ENERGY_MAX );

  // This member function will throw an exception and exit if an error occurs
  // so no TEST macro is needed.
  photon_data_processor.processEADLFile();

  // Read the top level attribute data back in
  FACEMC::HDF5FileHandler hdf5_file_handler;
  hdf5_file_handler.openHDF5FileAndReadOnly( HDF5_COMPLETE_TEST_FILE );

  // Read in the atomic relaxation shell attribute
  Teuchos::Array<unsigned int> relaxation_shells;
  hdf5_file_handler.readArrayFromGroupAttribute( relaxation_shells,
						 TRANSITION_PROBABILITY_ROOT,
						 ATOMIC_RELAXATION_SHELL_ATTRIBUTE );

  TEST_EQUALITY_CONST( relaxation_shells.size(), 1 );
  TEST_EQUALITY_CONST( relaxation_shells[0], 0 );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataProcessor can process a Compton Profile data file
TEUCHOS_UNIT_TEST( PhotonDataProcessor, process_compton_file_test )
{
  TestingPhotonDataProcessor photon_data_processor( IGNORE,
						    IGNORE,
						    COMPTON_TEST_FILE_PREFIX,
						    OUTPUT_DIRECTORY,
						    ENERGY_MIN,
						    ENERGY_MAX );

  // This member function will throw an exception and exit if an error occurs
  // so no TEST macro is needed.
  photon_data_processor.processComptonFiles( 5, 6 );
}

//---------------------------------------------------------------------------//
// end tstPhotonDataProcessor.cpp
//---------------------------------------------------------------------------//

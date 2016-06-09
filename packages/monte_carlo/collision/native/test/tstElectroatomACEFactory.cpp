//---------------------------------------------------------------------------//
//!
//! \file   tstElectroatomACEFactory.cpp
//! \author Luke Kersting
//! \brief  Electroatom factory using ACE data unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomACEFactory.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor;
Teuchos::RCP<MonteCarlo::AtomicRelaxationModel> relaxation_model;
std::string electroatom_name;
double atomic_weight;
Teuchos::RCP<MonteCarlo::Electroatom> atom;
MonteCarlo::BremsstrahlungAngularDistributionType photon_distribution_function;
unsigned hash_grid_bins = 100;
double cutoff_angle_cosine = 0.999999;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a basic electroatom can be created
TEUCHOS_UNIT_TEST( ElectroatomACEFactory, createElectroatom_basic )
{
  photon_distribution_function = MonteCarlo::DIPOLE_DISTRIBUTION;

  MonteCarlo::ElectroatomACEFactory::createElectroatom( *xss_data_extractor,
                                                        electroatom_name,
                                                        atomic_weight,
                                                        hash_grid_bins,
                                                        relaxation_model,
                                                        atom,
                                                        photon_distribution_function,
                                                        false,
                                                        cutoff_angle_cosine );

  // Test the electroatom properties
  TEST_EQUALITY_CONST( atom->getAtomName(), "82000.12p" );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 2.000000000000E-03;
  double cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          4.806193787852E+08,
                          1e-12 );


  energy = 4.000000000000E-04;
  cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          1.278128947846E+09,
                          1e-12 );


  energy = 9.000000000000E-05;
  cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.411603154884E+09,
                          1e-12 );


  // Test that the absorption cross section can be returned
  cross_section =
    atom->getAbsorptionCrossSection( 1.000000000E-02 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 2.000000000000E-03 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 4.000000000000E-04 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 9.000000000000E-05 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Test that the total electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
                   1.000000000000E-02,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.053785458456E+07, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                   2.000000000000E-03,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 7.403570475672E+07, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                   4.000000000000E-04,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.117744877649E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                   9.000000000000E-05,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 3.624289144575E+08, 1e-12 );

  // Test that there are no subshell cross sections
  cross_section = atom->getReactionCrossSection(
		   1e-6,
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
		   1e5,
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  // Test that the atomic excitation cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2.000000000000E-03,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.965170000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4.000000000000E-04,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 6.226820000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9.000000000000E-05,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.160420000000E+09, 1e-12 );

  // Test that the bremsstrahlung cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2.000000000000E-03,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 9.258661418255E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4.000000000000E-04,
				 MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 8.914234996439E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9.000000000000E-05,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 7.249970966838E+03, 1e-12 );

  // Test that the cutoff elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2.000000000000E-03,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.100574153670E+08,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4.000000000000E-04,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          4.436635458458E+08,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9.000000000000E-05,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.887469904554E+08,
                          1e-12 );
}
/*
//---------------------------------------------------------------------------//
/* Check that a electroatom with detailed tabular photon angular distribution
 * data can be created
 *
TEUCHOS_UNIT_TEST( ElectroatomACEFactory, createElectroatom_detailed_brem )
{
  photon_distribution_function = MonteCarlo::TABULAR_DISTRIBUTION;
  MonteCarlo::ElectroatomACEFactory::createElectroatom( *xss_data_extractor,
                                                        electroatom_name,
                                                        atomic_weight,
                                                        hash_grid_bins,
                                                        relaxation_model,
                                                        atom,
                                                        photon_distribution_function,
                                                        false,
                                                        cutoff_angle_cosine );
}
*/
//---------------------------------------------------------------------------//
/* Check that a electroatom with detailed 2BS photon angular distribution
 * data can be created
 */
TEUCHOS_UNIT_TEST( ElectroatomACEFactory, createElectroatom_detailed_brem )
{
  photon_distribution_function = MonteCarlo::TWOBS_DISTRIBUTION;

  MonteCarlo::ElectroatomACEFactory::createElectroatom( *xss_data_extractor,
                                                        electroatom_name,
                                                        atomic_weight,
                                                        hash_grid_bins,
                                                        relaxation_model,
                                                        atom,
                                                        photon_distribution_function,
                                                        true,
                                                        cutoff_angle_cosine );

  // Test the electroatom properties
  TEST_EQUALITY_CONST( atom->getAtomName(), "82000.12p" );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 2.000000000000E-03;
  double cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          4.806193787852E+08,
                          1e-12 );


  energy = 4.000000000000E-04;
  cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          1.278128947846E+09,
                          1e-12 );


  energy = 9.000000000000E-05;
  cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.411603154884E+09,
                          1e-12 );


  // Test that the absorption cross section can be returned
  cross_section =
    atom->getAbsorptionCrossSection( 1.000000000E-02 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 2.000000000000E-03 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 4.000000000000E-04 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 9.000000000000E-05 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Test that the atomic excitation cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2.000000000000E-03,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.965170000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4.000000000000E-04,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 6.226820000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9.000000000000E-05,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.160420000000E+09, 1e-12 );

  // Test that the bremsstrahlung cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2.000000000000E-03,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 9.258661418255E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4.000000000000E-04,
				 MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 8.914234996439E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9.000000000000E-05,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 7.249970966838E+03, 1e-12 );

  // Test that the cutoff elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2.000000000000E-03,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.100574153670E+08,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4.000000000000E-04,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          4.436635458458E+08,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9.000000000000E-05,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.887469904554E+08,
                          1e-12 );

  // Test that there is no total electroionization
  cross_section = atom->getReactionCrossSection(
			1.000000000000E-05,
			MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
			1.000000000000E+05,
			MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  // Test that the K subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
		   1.000000000000E-05,
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
		   8.975400000000E-02,
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.250673571307E-01, 1e-12 );

  cross_section = atom->getReactionCrossSection(
		   1.000000000000E+05,
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 3.649190000000E+01, 1e-12 );

  // Test that the P3 subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
		  1.000000000000E-05,
		  MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.065300000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
		  2.000000000000E-03,
		  MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.774672656160E+07, 1e-12 );

  cross_section = atom->getReactionCrossSection(
		  1.000000000000E+05,
		  MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.822340000000E+05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a electroatom with electroionization subshell data can be created
TEUCHOS_UNIT_TEST( ElectroatomACEFactory, createElectroatom_ionization_subshells )
{
  photon_distribution_function = MonteCarlo::DIPOLE_DISTRIBUTION;

  MonteCarlo::ElectroatomACEFactory::createElectroatom( *xss_data_extractor,
                                                        electroatom_name,
                                                        atomic_weight,
                                                        hash_grid_bins,
                                                        relaxation_model,
                                                        atom,
                                                        photon_distribution_function,
                                                        true,
                                                        cutoff_angle_cosine );

  // Test the electroatom properties
  TEST_EQUALITY_CONST( atom->getAtomName(), "82000.12p" );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 2.000000000000E-03;
  double cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          4.806193787852E+08,
                          1e-12 );


  energy = 4.000000000000E-04;
  cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          1.278128947846E+09,
                          1e-12 );


  energy = 9.000000000000E-05;
  cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.411603154884E+09,
                          1e-12 );


  // Test that the absorption cross section can be returned
  cross_section =
    atom->getAbsorptionCrossSection( 1.000000000E-02 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 2.000000000000E-03 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 4.000000000000E-04 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 9.000000000000E-05 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Test that the atomic excitation cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2.000000000000E-03,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.965170000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4.000000000000E-04,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 6.226820000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9.000000000000E-05,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.160420000000E+09, 1e-12 );

  // Test that the bremsstrahlung cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2.000000000000E-03,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 9.258661418255E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4.000000000000E-04,
				 MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 8.914234996439E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9.000000000000E-05,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 7.249970966838E+03, 1e-12 );

  // Test that the cutoff elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2.000000000000E-03,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.100574153670E+08,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4.000000000000E-04,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          4.436635458458E+08,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9.000000000000E-05,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.887469904554E+08,
                          1e-12 );

  // Test that there is no total electroionization
  cross_section = atom->getReactionCrossSection(
			1.000000000000E-05,
			MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
			1.000000000000E+05,
			MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  // Test that the K subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
		   1.000000000000E-05,
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
		   8.975400000000E-02,
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.250673571307E-01, 1e-12 );

  cross_section = atom->getReactionCrossSection(
		   1.000000000000E+05,
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 3.649190000000E+01, 1e-12 );

  // Test that the P3 subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
		  1.000000000000E-05,
		  MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.065300000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
		  2.000000000000E-03,
		  MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.774672656160E+07, 1e-12 );

  cross_section = atom->getReactionCrossSection(
		  1.000000000000E+05,
		  MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.822340000000E+05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_ace_file_name, test_ace_table_name;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_ace_file",
		 &test_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_ace_table",
		 &test_ace_table_name,
		 "Test ACE table name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return =
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  {
    // Create a file handler and data extractor
    Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
				 new Data::ACEFileHandler( test_ace_file_name,
							   test_ace_table_name,
							   1u ) );
    xss_data_extractor.reset( new Data::XSSEPRDataExtractor(
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

    MonteCarlo::AtomicRelaxationModelFactory::createAtomicRelaxationModel(
							   *xss_data_extractor,
							   relaxation_model,
							   true );

    electroatom_name = test_ace_table_name;
    atomic_weight = ace_file_handler->getTableAtomicWeightRatio()*
      Utility::PhysicalConstants::neutron_rest_mass_amu;
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();

  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstElectroatomACEFactory.cpp
//---------------------------------------------------------------------------//

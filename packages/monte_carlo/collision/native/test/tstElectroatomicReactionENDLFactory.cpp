//---------------------------------------------------------------------------//
//!
//! \file   tstElectroatomicReactionENDLFactory.cpp
//! \author Luke Kersting
//! \brief  Electroatomic reaction factory using ENDL data unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReactionENDLFactory.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "Data_ENDLDataContainer.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

MonteCarlo::BremsstrahlungAngularDistributionType photon_distribution_function;
std::shared_ptr<Data::ENDLDataContainer> data_container;
std::vector<double> brem_photon_energy_grid;
std::shared_ptr<MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin> > brem_reaction;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the electroionization subshell reactions can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionENDLFactory,
		   createSubshellElectroelectricReactions )
{
  std::map<unsigned, std::vector<double> > ionization_energy_grids =
    data_container->getElectroionizationRecoilEnergyGrid();

  std::vector<std::shared_ptr<MonteCarlo::ElectroionizationSubshellElectroatomicReaction<Utility::LinLin> > > ionization_reactions;

  MonteCarlo::ElectroatomicReactionENDLFactory::createSubshellElectroionizationReactions(
		   *data_container,
		   ionization_energy_grids,
		   ionization_reactions );

  TEST_EQUALITY_CONST( ionization_reactions.size(), 24 );

  // Test the first shell's reaction properties
  TEST_EQUALITY_CONST(
		   ionization_reactions.front()->getReactionType(),
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( ionization_reactions.front()->getThresholdEnergy(), 8.8290E-02 );

  // Test the first shell's stored cross section is correct
  double cross_section =
    ionization_reactions.front()->getCrossSection( 8.829000E-02 );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section =
    ionization_reactions.front()->getCrossSection( 1.00000e-1 );

  TEST_FLOATING_EQUALITY( cross_section, 9.283500e-1, 1e-12 );

  cross_section =
    ionization_reactions.front()->getCrossSection( 1.58489e+2 );

  TEST_FLOATING_EQUALITY( cross_section, 2.788860E+01, 1e-12 );

  cross_section =
    ionization_reactions.front()->getCrossSection( 1.00000e+5 );

  TEST_FLOATING_EQUALITY( cross_section, 3.649190e+1, 1e-12 );

  // Check the last shell's reaction properties
  TEST_EQUALITY_CONST(
		  ionization_reactions.back()->getReactionType(),
		  MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( ionization_reactions.back()->getThresholdEnergy(), 5.290e-06 );

  cross_section =
    ionization_reactions.back()->getCrossSection( 1.00000e-5 );

  TEST_FLOATING_EQUALITY( cross_section, 1.065300e+8, 1e-12 );

  cross_section =
    ionization_reactions.back()->getCrossSection( 1.00000e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 3.248850E+07, 1e-12 );

  cross_section =
    ionization_reactions.back()->getCrossSection( 1.000000E+00 );

  TEST_FLOATING_EQUALITY( cross_section, 2.033500E+05, 1e-12 );

  cross_section =
    ionization_reactions.back()->getCrossSection( 1.00000e+5 );

  TEST_FLOATING_EQUALITY( cross_section, 1.8223400e+5, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a basic (dipole distribution) bremsstrahlung reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionENDLFactory,
                   createBremsstrahlungReaction_dipole )
{
  photon_distribution_function = MonteCarlo::DIPOLE_DISTRIBUTION;

  MonteCarlo::ElectroatomicReactionENDLFactory::createBremsstrahlungReaction(
							   *data_container,
							   brem_photon_energy_grid,
							   brem_reaction,
							   photon_distribution_function );

  // Test reaction properties
  TEST_EQUALITY_CONST( brem_reaction->getReactionType(),
		       MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( brem_reaction->getThresholdEnergy(), 1.00000e-5 );

  // Test that the stored cross section is correct
  double cross_section =
    brem_reaction->getCrossSection( brem_reaction->getThresholdEnergy() );

  TEST_FLOATING_EQUALITY( cross_section, 4.869800000000e+3, 1e-12 );

  cross_section = brem_reaction->getCrossSection( 1.00000e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 9.528370E+03, 1e-12 );

  cross_section = brem_reaction->getCrossSection( 4.000000E+01 );

  TEST_FLOATING_EQUALITY( cross_section, 1.405050E+03, 1e-12 );

  cross_section = brem_reaction->getCrossSection( 1.00000e+5 );

  TEST_EQUALITY_CONST( cross_section, 1.9541700e+3 );

  // Clear the reaction
  brem_reaction.reset();
}

//---------------------------------------------------------------------------//
/* Check that a electroatom with detailed 2BS photon angular distribution
 * data can be created
 */
TEUCHOS_UNIT_TEST( ElectroatomicReactionENDLFactory,
                   createBremsstrahlungReaction_2bs )
{
  photon_distribution_function = MonteCarlo::TWOBS_DISTRIBUTION;

  MonteCarlo::ElectroatomicReactionENDLFactory::createBremsstrahlungReaction(
							   *data_container,
							   brem_photon_energy_grid,
							   brem_reaction,
							   photon_distribution_function );

  // Test reaction properties
  TEST_EQUALITY_CONST( brem_reaction->getReactionType(),
		       MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( brem_reaction->getThresholdEnergy(), 1.00000e-5 );

  // Test that the stored cross section is correct
  double cross_section =
    brem_reaction->getCrossSection( brem_reaction->getThresholdEnergy() );

  TEST_FLOATING_EQUALITY( cross_section, 4.869800e+3, 1e-12 );

  cross_section = brem_reaction->getCrossSection( 1.00000e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 9.528370E+03, 1e-12 );

  cross_section = brem_reaction->getCrossSection( 4.000000E+01 );

  TEST_FLOATING_EQUALITY( cross_section, 1.405050E+03, 1e-12 );

  cross_section = brem_reaction->getCrossSection( 1.00000e+5 );

  TEST_EQUALITY_CONST( cross_section, 1.9541700e+3 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_endl_file_name;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_endl_file",
		 &test_endl_file_name,
		 "Test ENDL file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return =
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  {
    // Create the ENDL data file container
    data_container.reset( new Data::ENDLDataContainer(
						     test_endl_file_name ) );

    // Extract the bremsstrahlung photon energy grid
    brem_photon_energy_grid =
        data_container->getBremsstrahlungPhotonEnergyGrid();
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
// end tstElectroatomicReactionENDLFactory.cpp
//---------------------------------------------------------------------------//


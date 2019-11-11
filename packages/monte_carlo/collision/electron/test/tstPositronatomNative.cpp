//---------------------------------------------------------------------------//
//!
//! \file   tstPositronatomNative.cpp
//! \author Luke Kersting
//! \brief  Positronatom unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <algorithm>

// FRENSIE Includes
#include "MonteCarlo_Positronatom.hpp"
#include "MonteCarlo_PositronatomACEFactory.hpp"
#include "MonteCarlo_AtomicExcitationPositronatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_BremsstrahlungPositronatomicReaction.hpp"
#include "MonteCarlo_VoidAbsorptionPositronatomicReaction.hpp"
#include "MonteCarlo_VoidAtomicRelaxationModel.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::Positronatom> native_positronatom;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
bool notEqualZero( double value )
{
  return value != 0.0;
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the positronatom atom name can be returned
FRENSIE_UNIT_TEST( Positronatom, getAtomName_native )
{
  FRENSIE_CHECK_EQUAL( native_positronatom->getAtomName(), "Pb" );
}

//---------------------------------------------------------------------------//
// Check that the positronatom nuclide name can be returned
FRENSIE_UNIT_TEST( Positronatom, getNuclideName_native )
{
  FRENSIE_CHECK_EQUAL( native_positronatom->getNuclideName(), "Pb" );
}

//---------------------------------------------------------------------------//
// Check that the positronatom atomic number can be returned
FRENSIE_UNIT_TEST( Positronatom, getAtomicNumber_native )
{
  FRENSIE_CHECK_EQUAL( native_positronatom->getAtomicNumber(), 82 );
}

//---------------------------------------------------------------------------//
// Check that the positronatom atomic mass number can be returned
FRENSIE_UNIT_TEST( Positronatom, getAtomicMassNumber_native )
{
  FRENSIE_CHECK_EQUAL( native_positronatom->getAtomicMassNumber(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the positronatom isomer number can be returned
FRENSIE_UNIT_TEST( Positronatom, getIsomerNumber_native )
{
  FRENSIE_CHECK_EQUAL( native_positronatom->getIsomerNumber(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the positronatom atomic weight can be returned
FRENSIE_UNIT_TEST( Positronatom, getAtomicWeight_native )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( native_positronatom->getAtomicWeight(),
                          207.1999470456033,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the positronatom temperature can be returned
FRENSIE_UNIT_TEST( Positronatom, getTemperature_native )
{
  FRENSIE_CHECK_EQUAL( native_positronatom->getTemperature(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the total cross section can be returned
FRENSIE_UNIT_TEST( Positronatom, getTotalCrossSection_native )
{
  double cross_section =
    native_positronatom->getTotalCrossSection( 2e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          9.2586614182549074e+03 + 1.96517E+08,
                          1e-12 );
  cross_section =
    native_positronatom->getTotalCrossSection( 4e-4 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          8.9142349964387486e+03 + 6.22682E+08,
                          1e-12 );
  cross_section =
    native_positronatom->getTotalCrossSection( 9e-5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          7.2499709668376108e+03 + 1.16042E+09,
                          1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the absorption cross section can be returned
FRENSIE_UNIT_TEST( Positronatom, getAbsorptionCrossSection_native )
{
  double cross_section =
    native_positronatom->getAbsorptionCrossSection( 1.000000000E-02 );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =
    native_positronatom->getAbsorptionCrossSection( 2e-3 );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =
    native_positronatom->getAbsorptionCrossSection( 4e-4 );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =
    native_positronatom->getAbsorptionCrossSection( 9e-5 );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the survival probability can be returned
FRENSIE_UNIT_TEST( Positronatom, getSurvivalProbability_native )
{
  double survival_prob =
    native_positronatom->getSurvivalProbability( 2e-3 );

   FRENSIE_CHECK_EQUAL( survival_prob, 1.0 );

  survival_prob =
    native_positronatom->getSurvivalProbability( 4e-4 );

   FRENSIE_CHECK_EQUAL( survival_prob, 1.0 );

  survival_prob =
    native_positronatom->getSurvivalProbability( 9e-5 );

   FRENSIE_CHECK_EQUAL( survival_prob, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction cross section can be returned
FRENSIE_UNIT_TEST( Positronatom, getReactionCrossSection_native )
{
  // Total Electroionization
  double cross_section = native_positronatom->getReactionCrossSection(
                   1.000000000000E-02,
                   MonteCarlo::TOTAL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = native_positronatom->getReactionCrossSection(
                   2e-3,
                   MonteCarlo::TOTAL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = native_positronatom->getReactionCrossSection(
                   4e-4,
                   MonteCarlo::TOTAL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = native_positronatom->getReactionCrossSection(
                   9e-5,
                   MonteCarlo::TOTAL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Atomic Excitation
  cross_section = native_positronatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.96517E+08, 1e-12 );

  cross_section = native_positronatom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.22682E+08, 1e-12 );

  cross_section = native_positronatom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.16042E+09, 1e-12 );

  // Bremsstrahlung
  cross_section = native_positronatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.2586614182549074e+03, 1e-12 );

  cross_section = native_positronatom->getReactionCrossSection(
                    4e-4,
                 MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.9142349964387486e+03, 1e-12 );

  cross_section = native_positronatom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 7.2499709668376108e+03, 1e-12 );

  // Cutoff Elastic
  cross_section = native_positronatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = native_positronatom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = native_positronatom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Total
  cross_section = native_positronatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::TOTAL_POSITRONATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          9.2586614182549074e+03 + 1.96517E+08,
                          1e-12 );

  cross_section = native_positronatom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::TOTAL_POSITRONATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          8.9142349964387486e+03 + 6.22682E+08,
                          1e-12 );

  cross_section = native_positronatom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::TOTAL_POSITRONATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          7.2499709668376108e+03 + 1.16042E+09,
                          1e-12 );

  // Absorption
  cross_section = native_positronatom->getReactionCrossSection(
                    1.000000000000E-02,
                    MonteCarlo::TOTAL_ABSORPTION_POSITRONATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =native_positronatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::TOTAL_ABSORPTION_POSITRONATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = native_positronatom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::TOTAL_ABSORPTION_POSITRONATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = native_positronatom->getReactionCrossSection(
                    9e-5,
               MonteCarlo::TOTAL_ABSORPTION_POSITRONATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reaction types can be returned
FRENSIE_UNIT_TEST( Positronatom, getAbsorptionReactionTypes_native )
{
  MonteCarlo::Positronatom::ReactionEnumTypeSet reaction_types;

  native_positronatom->getAbsorptionReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reaction types can be returned
FRENSIE_UNIT_TEST( Positronatom, getScatteringReactionTypes_native )
{
  MonteCarlo::Positronatom::ReactionEnumTypeSet reaction_types;

  native_positronatom->getScatteringReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 2 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that the misc reaction types can be returned
FRENSIE_UNIT_TEST( Positronatom, getMiscReactionTypes_native )
{
  MonteCarlo::Positronatom::ReactionEnumTypeSet reaction_types;

  native_positronatom->getMiscReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction types can be returned
FRENSIE_UNIT_TEST( Positronatom, getReactionTypes_native )
{
  MonteCarlo::Positronatom::ReactionEnumTypeSet reaction_types;

  native_positronatom->getReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 3 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_file",
                                        test_native_file_name, "",
                                        "Test Native file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the native data file container
  Data::ElectronPhotonRelaxationDataContainer data_container(
        test_native_file_name );

  // Create the atomic excitation, bremsstrahlung cross sections
  std::shared_ptr<const std::vector<double> > energy_grid(
           new std::vector<double>( data_container.getElectronEnergyGrid() ) );

  // Create the hash-based grid searcher
  std::shared_ptr<Utility::HashBasedGridSearcher<double> > grid_searcher(
        new Utility::StandardHashBasedGridSearcher<std::vector<double>,false>(
                         energy_grid,
                         energy_grid->front(),
                         energy_grid->back(),
                         100 ) );

  // Atomic Excitation cross section
  std::shared_ptr<const std::vector<double> > ae_cross_section(
       new std::vector<double>( data_container.getAtomicExcitationCrossSection() ) );

  size_t ae_threshold_index =
    data_container.getAtomicExcitationCrossSectionThresholdEnergyIndex();

  // Create the energy loss distributions
  MonteCarlo::AtomicExcitationElectronScatteringDistribution::AtomicDistribution
    ae_energy_loss_function(
            new Utility::TabularDistribution<Utility::LogLog>(
                data_container.getAtomicExcitationEnergyGrid(),
                data_container.getAtomicExcitationEnergyLoss() ) );

  std::shared_ptr<const MonteCarlo::AtomicExcitationElectronScatteringDistribution>
    ae_energy_loss_distribution(
            new MonteCarlo::AtomicExcitationElectronScatteringDistribution(
                      ae_energy_loss_function ) );

  std::shared_ptr<MonteCarlo::PositronatomicReaction> ae_reaction(
        new MonteCarlo::AtomicExcitationPositronatomicReaction<Utility::LogLog>(
            energy_grid,
            ae_cross_section,
            ae_threshold_index,
            grid_searcher,
            ae_energy_loss_distribution ) );


  // Bremsstrahlung cross section
  std::shared_ptr<const std::vector<double> > b_cross_section(
       new std::vector<double>( data_container.getBremsstrahlungCrossSection() ) );

  size_t b_threshold_index =
    data_container.getBremsstrahlungCrossSectionThresholdEnergyIndex();


  // Get the energy grid for bremsstrahlung energy distributions
  const std::vector<double>& b_energy_grid =
        data_container.getBremsstrahlungEnergyGrid();

  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    secondary_dists( b_energy_grid.size() );

  for( unsigned n = 0; n < b_energy_grid.size(); ++n )
  {
    // Get the energy of the bremsstrahlung photon at the incoming energy
    std::vector<double> photon_energy(
        data_container.getBremsstrahlungPhotonEnergy( b_energy_grid[n] ) );

    // Get the bremsstrahlung photon pdf at the incoming energy
    std::vector<double> pdf(
        data_container.getBremsstrahlungPhotonPDF( b_energy_grid[n] ) );

    secondary_dists[n].reset(
        new const Utility::TabularDistribution<Utility::LinLin>( photon_energy,
                                                                 pdf ) );
  }

  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> b_energy_loss_function(
       new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::UnitBaseCorrelated<Utility::LogLogLog> >(
                                                        b_energy_grid,
                                                        secondary_dists ) );

  std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution>
    b_scattering_distribution(
            new MonteCarlo::BremsstrahlungElectronScatteringDistribution(
                data_container.getAtomicNumber(),
                b_energy_loss_function ) );


  // Create the bremsstrahlung scattering reaction
  std::shared_ptr<MonteCarlo::PositronatomicReaction> b_reaction(
        new MonteCarlo::BremsstrahlungPositronatomicReaction<Utility::LogLog>(
            energy_grid,
            b_cross_section,
            b_threshold_index,
            b_scattering_distribution ) );

  // Create the reaction maps
  MonteCarlo::PositronatomCore::ConstReactionMap scattering_reactions,
    absorption_reactions;

  scattering_reactions[ae_reaction->getReactionType()] = ae_reaction;
  
  scattering_reactions[b_reaction->getReactionType()] = b_reaction;
  
  // Create a void atomic relaxation model
  std::shared_ptr<MonteCarlo::AtomicRelaxationModel> relaxation_model(
                   new MonteCarlo::VoidAtomicRelaxationModel );

  // Create a test positronatom
  native_positronatom.reset(
           new MonteCarlo::Positronatom(
                    "Pb",
                    data_container.getAtomicNumber(),
                    207.1999470456033,
                    energy_grid,
                    grid_searcher,
                    scattering_reactions,
                    absorption_reactions,
                    relaxation_model,
                    false,
                    Utility::LogLog() ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPositronatomNative.cpp
//---------------------------------------------------------------------------//


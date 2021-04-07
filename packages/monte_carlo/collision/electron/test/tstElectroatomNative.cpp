//---------------------------------------------------------------------------//
//!
//! \file   tstElectroatomNative.cpp
//! \author Luke Kersting
//! \brief  Electroatom unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <algorithm>

// FRENSIE Includes
#include "MonteCarlo_Electroatom.hpp"
#include "MonteCarlo_ElectroatomACEFactory.hpp"
#include "MonteCarlo_AtomicExcitationElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
#include "MonteCarlo_VoidAbsorptionElectroatomicReaction.hpp"
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

std::shared_ptr<const MonteCarlo::Electroatom> native_electroatom;

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
// Check that the electroatom atom name can be returned
FRENSIE_UNIT_TEST( Electroatom, getAtomName_native )
{
  FRENSIE_CHECK_EQUAL( native_electroatom->getAtomName(), "Pb" );
}

//---------------------------------------------------------------------------//
// Check that the electroatom nuclide name can be returned
FRENSIE_UNIT_TEST( Electroatom, getNuclideName_native )
{
  FRENSIE_CHECK_EQUAL( native_electroatom->getNuclideName(), "Pb" );
}

//---------------------------------------------------------------------------//
// Check that the electroatom atomic number can be returned
FRENSIE_UNIT_TEST( Electroatom, getAtomicNumber_native )
{
  FRENSIE_CHECK_EQUAL( native_electroatom->getAtomicNumber(), 82 );
}

//---------------------------------------------------------------------------//
// Check that the electroatom atomic mass number can be returned
FRENSIE_UNIT_TEST( Electroatom, getAtomicMassNumber_native )
{
  FRENSIE_CHECK_EQUAL( native_electroatom->getAtomicMassNumber(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the electroatom isomer number can be returned
FRENSIE_UNIT_TEST( Electroatom, getIsomerNumber_native )
{
  FRENSIE_CHECK_EQUAL( native_electroatom->getIsomerNumber(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the electroatom atomic weight can be returned
FRENSIE_UNIT_TEST( Electroatom, getAtomicWeight_native )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( native_electroatom->getAtomicWeight(),
                          207.1999470456033,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the electroatom temperature can be returned
FRENSIE_UNIT_TEST( Electroatom, getTemperature_native )
{
  FRENSIE_CHECK_EQUAL( native_electroatom->getTemperature(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the total cross section can be returned
FRENSIE_UNIT_TEST( Electroatom, getTotalCrossSection_native )
{
  double cross_section =
    native_electroatom->getTotalCrossSection( 2e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          9.2586614182549074e+03 + 1.96517E+08,
                          1e-12 );
  cross_section =
    native_electroatom->getTotalCrossSection( 4e-4 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          8.9142349964387486e+03 + 6.22682E+08,
                          1e-12 );
  cross_section =
    native_electroatom->getTotalCrossSection( 9e-5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          7.2499709668376108e+03 + 1.16042E+09,
                          1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the absorption cross section can be returned
FRENSIE_UNIT_TEST( Electroatom, getAbsorptionCrossSection_native )
{
  double cross_section =
    native_electroatom->getAbsorptionCrossSection( 1.000000000E-02 );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =
    native_electroatom->getAbsorptionCrossSection( 2e-3 );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =
    native_electroatom->getAbsorptionCrossSection( 4e-4 );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =
    native_electroatom->getAbsorptionCrossSection( 9e-5 );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the survival probability can be returned
FRENSIE_UNIT_TEST( Electroatom, getSurvivalProbability_native )
{
  double survival_prob =
    native_electroatom->getSurvivalProbability( 2e-3 );

   FRENSIE_CHECK_EQUAL( survival_prob, 1.0 );

  survival_prob =
    native_electroatom->getSurvivalProbability( 4e-4 );

   FRENSIE_CHECK_EQUAL( survival_prob, 1.0 );

  survival_prob =
    native_electroatom->getSurvivalProbability( 9e-5 );

   FRENSIE_CHECK_EQUAL( survival_prob, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction cross section can be returned
FRENSIE_UNIT_TEST( Electroatom, getReactionCrossSection_native )
{
  // Total Electroionization
  double cross_section = native_electroatom->getReactionCrossSection(
                   1.000000000000E-02,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = native_electroatom->getReactionCrossSection(
                   2e-3,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = native_electroatom->getReactionCrossSection(
                   4e-4,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = native_electroatom->getReactionCrossSection(
                   9e-5,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Atomic Excitation
  cross_section = native_electroatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.96517E+08, 1e-12 );

  cross_section = native_electroatom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.22682E+08, 1e-12 );

  cross_section = native_electroatom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.16042E+09, 1e-12 );

  // Bremsstrahlung
  cross_section = native_electroatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.2586614182549074e+03, 1e-12 );

  cross_section = native_electroatom->getReactionCrossSection(
                    4e-4,
                 MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.9142349964387486e+03, 1e-12 );

  cross_section = native_electroatom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 7.2499709668376108e+03, 1e-12 );

  // Cutoff Elastic
  cross_section = native_electroatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = native_electroatom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = native_electroatom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Total
  cross_section = native_electroatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::TOTAL_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          9.2586614182549074e+03 + 1.96517E+08,
                          1e-12 );

  cross_section = native_electroatom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::TOTAL_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          8.9142349964387486e+03 + 6.22682E+08,
                          1e-12 );

  cross_section = native_electroatom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::TOTAL_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          7.2499709668376108e+03 + 1.16042E+09,
                          1e-12 );

  // Absorption
  cross_section = native_electroatom->getReactionCrossSection(
                    1.000000000000E-02,
                    MonteCarlo::TOTAL_ABSORPTION_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =native_electroatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::TOTAL_ABSORPTION_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = native_electroatom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::TOTAL_ABSORPTION_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = native_electroatom->getReactionCrossSection(
                    9e-5,
               MonteCarlo::TOTAL_ABSORPTION_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reaction types can be returned
FRENSIE_UNIT_TEST( Electroatom, getAbsorptionReactionTypes_native )
{
  MonteCarlo::Electroatom::ReactionEnumTypeSet reaction_types;

  native_electroatom->getAbsorptionReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reaction types can be returned
FRENSIE_UNIT_TEST( Electroatom, getScatteringReactionTypes_native )
{
  MonteCarlo::Electroatom::ReactionEnumTypeSet reaction_types;

  native_electroatom->getScatteringReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 2 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that the miscellaneous reaction types can be returned
FRENSIE_UNIT_TEST( Electroatom, getMiscReactionTypes_native )
{
  MonteCarlo::Electroatom::ReactionEnumTypeSet reaction_types;

  native_electroatom->getMiscReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction types can be returned
FRENSIE_UNIT_TEST( Electroatom, getReactionTypes_native )
{
  MonteCarlo::Electroatom::ReactionEnumTypeSet reaction_types;

  native_electroatom->getReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 3 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION ) );
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

  std::shared_ptr<MonteCarlo::ElectroatomicReaction> ae_reaction(
        new MonteCarlo::AtomicExcitationElectroatomicReaction<Utility::LogLog>(
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
  std::shared_ptr<MonteCarlo::ElectroatomicReaction> b_reaction(
        new MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LogLog>(
            energy_grid,
            b_cross_section,
            b_threshold_index,
            b_scattering_distribution ) );

  // Create the reaction maps
  MonteCarlo::ElectroatomCore::ConstReactionMap scattering_reactions,
    absorption_reactions;
  
  scattering_reactions[ae_reaction->getReactionType()] = ae_reaction;
  
  scattering_reactions[b_reaction->getReactionType()] = b_reaction;
  
  // Create a void atomic relaxation model
  std::shared_ptr<MonteCarlo::AtomicRelaxationModel> relaxation_model(
                   new MonteCarlo::VoidAtomicRelaxationModel );

  // Create a test electroatom
  native_electroatom.reset(
           new MonteCarlo::Electroatom(
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
// end tstElectroatomNative.cpp
//---------------------------------------------------------------------------//


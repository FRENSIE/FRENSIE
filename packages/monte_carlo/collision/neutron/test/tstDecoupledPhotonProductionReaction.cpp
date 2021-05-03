//---------------------------------------------------------------------------//
//!
//! \file   tstDecoupledPhotonProductionReaction.cpp
//! \author Eli  Moll
//! \brief  Decoupled photon production reaction unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_DecoupledPhotonProductionReaction.hpp"
#include "MonteCarlo_PhotonProductionNuclearScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "MonteCarlo_NeutronAbsorptionReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::shared_ptr<const MonteCarlo::DecoupledPhotonProductionReaction> nuclear_reaction;

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestDecoupledPhotonProductionReaction : public MonteCarlo::DecoupledPhotonProductionReaction
{
public:
  TestDecoupledPhotonProductionReaction(
      const MonteCarlo::NuclearReactionType base_reaction_type,
      const unsigned photon_production_id,
      const double temperature,
      std::shared_ptr< const MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::PhotonState> >&
        photon_production_distribution,
      const std::shared_ptr<MonteCarlo::NeutronNuclearReaction>& total_reaction,
      const std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >& total_mt_yield_array )
    : MonteCarlo::DecoupledPhotonProductionReaction( base_reaction_type,
                                                     photon_production_id,
                                                     temperature,
                                                     photon_production_distribution,
                                                     total_reaction,
                                                     total_mt_yield_array )
  { /* ... */ }

  ~TestDecoupledPhotonProductionReaction()
  { /* ... */ }

  // Test if two Atomic reactions share the same energy grid
  bool isEnergyGridShared( const Reaction& other_reaction ) const final override
  { return false; }

  // Test if the energy falls within the energy grid
  bool isEnergyWithinEnergyGrid( const double energy ) const final override
  { return false; }

  // Return the threshold energy
  double getThresholdEnergy() const final override
  { return 0.0; }

  //! Return the max energy
  double getMaxEnergy() const final override
  { return 0.0; }

  // Return the base reaction cross section at a given energy
  double getReactionCrossSection( const double energy ) const final override
  { return 0.0; }

  // Return the cross section at a given energy
  double getCrossSection( const double energy ) const final override
  { return 0.0; }

  // Return the cross section at a given energy
  double getCrossSection( const double energy, size_t bin_index ) const final override
  { return 0.0; }

  // Return the average number of emitted photons
  double getAverageNumberOfEmittedParticles( const double energy ) const final override
  { return 0.0; }

  void react( MonteCarlo::NeutronState& neutron, MonteCarlo::ParticleBank& bank, double total_pp_xs ) const
  { /* ... */ }

protected:

  // Return the head of the energy grid
  const double* getEnergyGridHead() const final override
  { return NULL; }
};

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the base photon production ID can be returned
FRENSIE_UNIT_TEST( DecoupledPhotonProductionReaction, getPhotonProductionId )
{
  FRENSIE_CHECK_EQUAL( nuclear_reaction->getPhotonProductionId(),
		       MonteCarlo::N__GAMMA_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the base reaction type can be returned
FRENSIE_UNIT_TEST( DecoupledPhotonProductionReaction, getReactionType )
{
  FRENSIE_CHECK_EQUAL( nuclear_reaction->getReactionType(),
		       MonteCarlo::N__GAMMA_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the photon production reaction ID can be returned
FRENSIE_UNIT_TEST( DecoupledPhotonProductionReaction, getPhotonProductionReactionId )
{
  FRENSIE_CHECK_EQUAL( nuclear_reaction->getPhotonProductionReactionId(), 102001u );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_basic_ace_file_name;
unsigned test_basic_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_basic_ace_file",
                                        test_basic_ace_file_name, "",
                                        "Test basic ACE file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_basic_ace_file_start_line",
                                        test_basic_ace_file_start_line, 1,
                                        "Test basic ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Initialize the reaction
  {
    // Reaction type
    unsigned reaction_type = 102001u;

    // Create the ace file handler
    std::unique_ptr<Data::ACEFileHandler> ace_file_handler(
                  new Data::ACEFileHandler( test_basic_ace_file_name,
                                            "1001.70c",
					    test_basic_ace_file_start_line ) );

    // Create the XSS data extractor
    std::unique_ptr<Data::XSSNeutronDataExtractor> xss_data_extractor(
     new Data::XSSNeutronDataExtractor( ace_file_handler->getTableNXSArray(),
				        ace_file_handler->getTableJXSArray(),
				        ace_file_handler->getTableXSSArray()));

    // Create the photon production nuclear scattering distribution ACE factory
    MonteCarlo::PhotonProductionNuclearScatteringDistributionACEFactory
      photon_production_dist_factory(
                                 "1001.70c",
                                 ace_file_handler->getTableAtomicWeightRatio(),
                                 *xss_data_extractor );

    // Create the simulation properties
    MonteCarlo::SimulationProperties properties;

    // Create the photon production nuclear scattering distribution
    std::shared_ptr<const MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::PhotonState> >
      photon_production_distribution;
    photon_production_dist_factory.createScatteringDistribution(
					      reaction_type,
                                              properties,
					      photon_production_distribution );

    std::shared_ptr<const std::vector<double> > energy_grid(
          new std::vector<double>( xss_data_extractor->extractEnergyGrid() ) );

    std::shared_ptr<const std::vector<double> > cross_section(
          new std::vector<double>( xss_data_extractor->extractTotalCrossSection() ) );

    // Construct the yield energy grid and yield data
    std::vector<double> yield_energy_grid = { 1.00000000000E-11,
                                              2.00000000000E+01 };
    std::vector<double> yield_energy_values = { 2.00000000000E+00,
                                                2.00000000000E+00 };

    std::shared_ptr<const Utility::UnivariateDistribution> d_mtp_yield(
        new Utility::TabularDistribution<Utility::LinLin>(
                              yield_energy_grid,
                              yield_energy_values ) );

    std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >
      total_mt_yield_array;
    total_mt_yield_array.push_back( d_mtp_yield );

    const std::shared_ptr< MonteCarlo::NeutronNuclearReaction> total_reaction(
          new MonteCarlo::NeutronAbsorptionReaction(
                           energy_grid,
                           cross_section,
                           0u,
                           MonteCarlo::N__TOTAL_REACTION,
                           0.0,
                           ace_file_handler->getTableTemperature().value() ) );

    nuclear_reaction.reset(new TestDecoupledPhotonProductionReaction(
                                  MonteCarlo::N__GAMMA_REACTION,
                                  reaction_type,
                                  ace_file_handler->getTableTemperature().value(),
                                  photon_production_distribution,
                                  total_reaction,
                                  total_mt_yield_array));
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstNuclearReaction.cpp
//---------------------------------------------------------------------------//

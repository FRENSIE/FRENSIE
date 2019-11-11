//---------------------------------------------------------------------------//
//!
//! \file   tstPhotonuclearScatteringDistributionACEFactory.cpp
//! \author Alex Robinson, Ryan Pease
//! \brief  photon-neutron (photonuclear) scattering distribution factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_PhotonuclearScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_PhotonuclearReactionType.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSPhotonuclearDataExtractor.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestPhotonuclearScatteringDistributionACEFactory : public MonteCarlo::PhotonuclearScatteringDistributionACEFactory
{
public:
  TestPhotonuclearScatteringDistributionACEFactory(
                         const std::string& table_name,
			 const double atomic_weight_ratio,
		   const Data::XSSPhotonuclearDataExtractor& raw_nuclide_data )
    : MonteCarlo::PhotonuclearScatteringDistributionACEFactory(
                                                           table_name,
                                                           atomic_weight_ratio,
							   raw_nuclide_data )
  { /* ... */ }

  ~TestPhotonuclearScatteringDistributionACEFactory()
  { /* ... */ }

  using MonteCarlo::PhotonuclearScatteringDistributionACEFactory::getReactionOrdering;
  using MonteCarlo::PhotonuclearScatteringDistributionACEFactory::getReactionCMScattering;
  using MonteCarlo::PhotonuclearScatteringDistributionACEFactory::getReactionsWithIsotropicScatteringOnly;
  using MonteCarlo::PhotonuclearScatteringDistributionACEFactory::getReactionsWithCoupledEnergyAngleDist;
  using MonteCarlo::PhotonuclearScatteringDistributionACEFactory::getReactionAngularDist;
  using MonteCarlo::PhotonuclearScatteringDistributionACEFactory::getReactionAngularDistStartIndex;
  using MonteCarlo::PhotonuclearScatteringDistributionACEFactory::getReactionEnergyDist;
  using MonteCarlo::PhotonuclearScatteringDistributionACEFactory::getReactionEnergyDistStartIndex;
};

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::unique_ptr<const Data::XSSPhotonuclearDataExtractor> xss_data_extractor;
std::unique_ptr<const TestPhotonuclearScatteringDistributionACEFactory> photonuclear_distribution_factory_c12;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the reaction ordering has been extracted correctly
FRENSIE_UNIT_TEST( PhotonuclearScatteringDistributionACEFactory,
		   getReactionOrdering )
{
  auto reaction_ordering =
    photonuclear_distribution_factory_c12->getReactionOrdering();

  // Only 1 reaction produces an outgoing photon, reaction 5
  FRENSIE_REQUIRE_EQUAL( reaction_ordering.size(), 1 );
  FRENSIE_REQUIRE( reaction_ordering.find(5) != reaction_ordering.end() );
  FRENSIE_CHECK_EQUAL( reaction_ordering.find(5)->second, 0 );
}

//---------------------------------------------------------------------------//
// Check that the reactions that undergo scattering in the CM frame have
// been extracted correctly
FRENSIE_UNIT_TEST( PhotonuclearScatteringDistributionACEFactory,
		   getReactionCMScattering )
{
  auto reaction_cm_scattering =
    photonuclear_distribution_factory_c12->getReactionCMScattering();
  
  // Only 1 reaction produces an outgoing photon, reaction 5
  FRENSIE_REQUIRE_EQUAL( reaction_cm_scattering.size(), 1 );
  FRENSIE_REQUIRE( reaction_cm_scattering.find(5) != reaction_cm_scattering.end() );
  FRENSIE_CHECK_EQUAL( reaction_cm_scattering.find(5)->second, true );
}

//---------------------------------------------------------------------------//
// Check that the reactions that undergo isotropic scattering have been
// extracted correctly
FRENSIE_UNIT_TEST( PhotonuclearScatteringDistributionACEFactory,
		   getReactionWithIsotropicScatteringOnly )
{
  auto reactions_with_isotropic_scattering =
    photonuclear_distribution_factory_c12->getReactionsWithIsotropicScatteringOnly();
  
  // Only 1 reaction produces an outgoing photon, reaction 5. This reaction has
  // dist_index = 0 -> iso scat only
  FRENSIE_REQUIRE_EQUAL( reactions_with_isotropic_scattering.size(), 1 );
  FRENSIE_CHECK( reactions_with_isotropic_scattering.find( MonteCarlo::GAMMA__ANYTHING_REACTION ) != reactions_with_isotropic_scattering.end() );
}

//---------------------------------------------------------------------------//
// Check that the reactions with coupled energy-angle scattering distributions
// have been extracted correctly
FRENSIE_UNIT_TEST( PhotonuclearScatteringDistributionACEFactory,
		   getReactionWithCoupledEnergyAngleDist )
{
  auto reactions_with_coupled_energy_angle_dist =
    photonuclear_distribution_factory_c12->getReactionsWithCoupledEnergyAngleDist();
  
  // Only 1 reaction produces an outgoing photon, reaction 5. This reaction has
  // dist_index = 0 -> no Energy Angle dependence
  FRENSIE_CHECK_EQUAL( reactions_with_coupled_energy_angle_dist.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that angular distributions have been extracted correctly
FRENSIE_UNIT_TEST( PhotonuclearScatteringDistributionACEFactory,
		   getReactionAngularDist )
{
  auto reaction_angular_distributions =
    photonuclear_distribution_factory_c12->getReactionAngularDist();

  FRENSIE_CHECK_EQUAL( reaction_angular_distributions.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the angular distribution start indices hae been extracted
// correctly
FRENSIE_UNIT_TEST( PhotonuclearScatteringDistributionACEFactory,
		   getReactionAngularDistStartIndex )
{
  auto reaction_angular_distribution_start_index =
    photonuclear_distribution_factory_c12->getReactionAngularDistStartIndex();

  FRENSIE_CHECK_EQUAL( reaction_angular_distribution_start_index.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction energy distributions have been extracted
// correctly
FRENSIE_UNIT_TEST( PhotonuclearScatteringDistributionACEFactory,
		   getReactionEnergyDist )
{
  auto reaction_energy_dists =
    photonuclear_distribution_factory_c12->getReactionEnergyDist();

  FRENSIE_REQUIRE_EQUAL( reaction_energy_dists.size(), 1 );
  FRENSIE_REQUIRE( reaction_energy_dists.find( MonteCarlo::GAMMA__ANYTHING_REACTION ) != reaction_energy_dists.end() );

  auto energy_dist =
    reaction_energy_dists.find( MonteCarlo::GAMMA__ANYTHING_REACTION )->second;

  FRENSIE_CHECK_EQUAL( energy_dist.size(), 11739 );
  FRENSIE_CHECK_EQUAL( energy_dist.front(), 0 );
  FRENSIE_CHECK_EQUAL( energy_dist.back(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the reaction energy distribution start indices habe been
// extracted correctly
FRENSIE_UNIT_TEST( PhotonuclearScatteringDistributionACEFactory,
		   getReactionEnergyDistStartIndex )
{
  auto reaction_energy_dist_start_indices =
    photonuclear_distribution_factory_c12->getReactionEnergyDistStartIndex();

  FRENSIE_REQUIRE_EQUAL( reaction_energy_dist_start_indices.size(), 1 );
  FRENSIE_REQUIRE( reaction_energy_dist_start_indices.find( MonteCarlo::GAMMA__ANYTHING_REACTION ) != reaction_energy_dist_start_indices.end() );
  FRENSIE_CHECK_EQUAL( reaction_energy_dist_start_indices.find( MonteCarlo::GAMMA__ANYTHING_REACTION )->second, 0 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_ace_file_name;
unsigned test_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file",
                                        test_ace_file_name, "",
                                        "Test ACE file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file_start_line",
                                        test_ace_file_start_line, 1,
                                        "Test ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create a file handler and data extractor
  std::shared_ptr<Data::ACEFileHandler> ace_file_handler(
                        new Data::ACEFileHandler( test_ace_file_name,
                                                  "6012.24u",
						  test_ace_file_start_line ) );

  xss_data_extractor.reset( new Data::XSSPhotonuclearDataExtractor(
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

  photonuclear_distribution_factory_c12.reset(
    new TestPhotonuclearScatteringDistributionACEFactory(
                                 "6012.24u",
                                 ace_file_handler->getTableAtomicWeightRatio(),
                                 *xss_data_extractor ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPhotonuclearScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//

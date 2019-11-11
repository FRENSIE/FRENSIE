//---------------------------------------------------------------------------//
//!
//! \file   tstPhotonuclearNeutronScatteringDistributionACEFactory.cpp
//! \author Alex Robinson, Ryan Pease
//! \brief  photon-neutron (photonuclear) scattering distribution factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_PhotonuclearNeutronScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_PhotonuclearReactionType.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSPhotonuclearDataExtractor.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestPhotonuclearNeutronScatteringDistributionACEFactory : public MonteCarlo::PhotonuclearNeutronScatteringDistributionACEFactory
{
public:
  TestPhotonuclearNeutronScatteringDistributionACEFactory(
                   const std::string& table_name,
                   const double atomic_weight_ratio,
		   const Data::XSSPhotonuclearDataExtractor& raw_nuclide_data )
    : MonteCarlo::PhotonuclearNeutronScatteringDistributionACEFactory( table_name,
                                                           atomic_weight_ratio,
							   raw_nuclide_data )
  { /* ... */ }

  ~TestPhotonuclearNeutronScatteringDistributionACEFactory()
  { /* ... */ }

  using MonteCarlo::PhotonuclearNeutronScatteringDistributionACEFactory::getReactionOrdering;
  using MonteCarlo::PhotonuclearNeutronScatteringDistributionACEFactory::getReactionCMScattering;
  using MonteCarlo::PhotonuclearNeutronScatteringDistributionACEFactory::getReactionsWithIsotropicScatteringOnly;
  using MonteCarlo::PhotonuclearNeutronScatteringDistributionACEFactory::getReactionsWithCoupledEnergyAngleDist;
  using MonteCarlo::PhotonuclearNeutronScatteringDistributionACEFactory::getReactionAngularDist;
  using MonteCarlo::PhotonuclearNeutronScatteringDistributionACEFactory::getReactionAngularDistStartIndex;
  using MonteCarlo::PhotonuclearNeutronScatteringDistributionACEFactory::getReactionEnergyDist;
  using MonteCarlo::PhotonuclearNeutronScatteringDistributionACEFactory::getReactionEnergyDistStartIndex;
};
//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::unique_ptr<const Data::XSSPhotonuclearDataExtractor> xss_data_extractor;
std::unique_ptr<const TestPhotonuclearNeutronScatteringDistributionACEFactory> photonuclear_neutron_distribution_factory_h2;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the reaction ordering has been extracted correctly
FRENSIE_UNIT_TEST( PhotonuclearNeutronScatteringDistributionACEFactory,
		   getReactionOrdering )
{
  auto reaction_ordering =
    photonuclear_neutron_distribution_factory_h2->getReactionOrdering();
  
  // Only 1 reaction produces an outgoing neutron, reaction 50
  FRENSIE_REQUIRE_EQUAL( reaction_ordering.size(), 1 );
  FRENSIE_REQUIRE( reaction_ordering.find(50) != reaction_ordering.end() );
  FRENSIE_CHECK_EQUAL( reaction_ordering.find(50)->second, 0 );
}

//---------------------------------------------------------------------------//
// Check that the reactions that undergo scattering in the CM frame have
// been extracted correctly
FRENSIE_UNIT_TEST( PhotonuclearNeutronScatteringDistributionACEFactory,
		   getReactionCMScattering )
{
  auto reaction_cm_scattering =
    photonuclear_neutron_distribution_factory_h2->getReactionCMScattering();

  // Only 1 reaction produces an outgoing neutron, reaction 50.
  FRENSIE_REQUIRE_EQUAL( reaction_cm_scattering.size(), 1 );
  FRENSIE_REQUIRE( reaction_cm_scattering.find(50) != reaction_cm_scattering.end() );
  FRENSIE_CHECK_EQUAL( reaction_cm_scattering.find(50)->second, true );
}

//---------------------------------------------------------------------------//
// Check that the reactions that undergo isotropic scattering have been
// extracted correctly
FRENSIE_UNIT_TEST( PhotonuclearNeutronScatteringDistributionACEFactory,
		   getReactionWithIsotropicScatteringOnly )
{
  auto reactions_with_isotropic_scattering =
    photonuclear_neutron_distribution_factory_h2->getReactionsWithIsotropicScatteringOnly();

  // Only 1 reaction produces an outgoing neutron, reaction 50. This
  // dist_index is = 1 -> no iso
  FRENSIE_CHECK_EQUAL( reactions_with_isotropic_scattering.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the reactions with coupled energy-angle scattering distributions
// have been extracted correctly
FRENSIE_UNIT_TEST( PhotonuclearNeutronScatteringDistributionACEFactory,
		   getReactionWithCoupledEnergyAngleDist )
{
  auto reactions_with_coupled_energy_angle_dist =
    photonuclear_neutron_distribution_factory_h2->getReactionsWithCoupledEnergyAngleDist();
  
  // Only 1 reaction produces an outgoing neutron, reaction 50. This
  // dist_index is = 1 -> no energy angle dependence
  FRENSIE_CHECK_EQUAL( reactions_with_coupled_energy_angle_dist.size(), 0 );
}


//---------------------------------------------------------------------------//
// Check that angular distributions have been extracted correctly
FRENSIE_UNIT_TEST( PhotonuclearNeutronScatteringDistributionACEFactory,
		   getReactionAngularDist )
{
  auto reaction_angular_distributions =
    photonuclear_neutron_distribution_factory_h2->getReactionAngularDist();

  FRENSIE_REQUIRE_EQUAL( reaction_angular_distributions.size(), 1 );
  FRENSIE_REQUIRE( reaction_angular_distributions.find( MonteCarlo::GAMMA__N_EXCITED_STATE_0_REACTION ) != reaction_angular_distributions.end());

  auto angular_distribution =
    reaction_angular_distributions.find( MonteCarlo::GAMMA__N_EXCITED_STATE_0_REACTION )->second;

  FRENSIE_CHECK_EQUAL( angular_distribution.size(), 1656 );
  FRENSIE_CHECK_EQUAL( angular_distribution.front(), 35 );
  FRENSIE_CHECK_EQUAL( angular_distribution.back(), 1 );
}


//---------------------------------------------------------------------------//
// Check that the angular distribution start indices hae been extracted
// correctly
FRENSIE_UNIT_TEST( PhotonuclearNeutronScatteringDistributionACEFactory,
		   getReactionAngularDistStartIndex )
{
  auto reaction_angular_distribution_start_index =
    photonuclear_neutron_distribution_factory_h2->getReactionAngularDistStartIndex();

  FRENSIE_REQUIRE_EQUAL( reaction_angular_distribution_start_index.size(), 1 );
  FRENSIE_REQUIRE( reaction_angular_distribution_start_index.find( MonteCarlo::GAMMA__N_EXCITED_STATE_0_REACTION ) != reaction_angular_distribution_start_index.end() );
  FRENSIE_CHECK_EQUAL( reaction_angular_distribution_start_index.find( MonteCarlo::GAMMA__N_EXCITED_STATE_0_REACTION )->second, 0 );
}


//---------------------------------------------------------------------------//
// Check that the reaction energy distributions have been extracted
// correctly
FRENSIE_UNIT_TEST( PhotonuclearNeutronScatteringDistributionACEFactory,
		   getReactionEnergyDist )
{
  auto reaction_energy_dists =
    photonuclear_neutron_distribution_factory_h2->getReactionEnergyDist();

  FRENSIE_REQUIRE_EQUAL( reaction_energy_dists.size(), 1 );
  FRENSIE_REQUIRE( reaction_energy_dists.find( MonteCarlo::GAMMA__N_EXCITED_STATE_0_REACTION ) != reaction_energy_dists.end() );

  auto energy_dist =
    reaction_energy_dists.find( MonteCarlo::GAMMA__N_EXCITED_STATE_0_REACTION )->second;
  
  FRENSIE_CHECK_EQUAL( energy_dist.size(), 11 );
  FRENSIE_CHECK_EQUAL( energy_dist.front(), 0 );
  FRENSIE_CHECK_EQUAL( energy_dist.back(), 6.66255E-01 );
}


//---------------------------------------------------------------------------//
// Check that the reaction energy distribution start indices habe been
// extracted correctly
FRENSIE_UNIT_TEST( PhotonuclearNeutronScatteringDistributionACEFactory,
		   getReactionEnergyDistStartIndex )
{
  auto reaction_energy_dist_start_indices =
    photonuclear_neutron_distribution_factory_h2->getReactionEnergyDistStartIndex();

  FRENSIE_REQUIRE_EQUAL( reaction_energy_dist_start_indices.size(), 1 );
  FRENSIE_REQUIRE( reaction_energy_dist_start_indices.find( MonteCarlo::GAMMA__N_EXCITED_STATE_0_REACTION ) != reaction_energy_dist_start_indices.end() );
  FRENSIE_CHECK_EQUAL( reaction_energy_dist_start_indices.find( MonteCarlo::GAMMA__N_EXCITED_STATE_0_REACTION )->second, 0 );
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
                                                  "1002.24u",
                                                  test_ace_file_start_line ) );

  xss_data_extractor.reset( new Data::XSSPhotonuclearDataExtractor(
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );
    
  photonuclear_neutron_distribution_factory_h2.reset(
                  new TestPhotonuclearNeutronScatteringDistributionACEFactory(
                                 "1002.24u",
                                 ace_file_handler->getTableAtomicWeightRatio(),
                                 *xss_data_extractor ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPhotonuclearNeutronScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//

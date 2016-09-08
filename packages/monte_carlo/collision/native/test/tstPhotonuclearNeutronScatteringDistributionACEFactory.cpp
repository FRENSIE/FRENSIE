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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotonuclearNeutronScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_NuclearReactionType.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSPhotonuclearDataExtractor.hpp"
#include "MonteCarlo_PhotonuclearReactionType.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestPhotonuclearNeutronScatteringDistributionACEFactory : public MonteCarlo::PhotonuclearNeutronScatteringDistributionACEFactory
{
public:
  TestPhotonuclearNeutronScatteringDistributionACEFactory(
                         const std::string& table_name,
			 const double atomic_weight_ratio,
			 const Data::XSSPhotonuclearDataExtractor raw_nuclide_data )
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
std::string test_basic_h2_ace_file_name;
std::string test_basic_h2_ace_table_name;

Teuchos::RCP<Data::ACEFileHandler> ace_file_handler_h2;
Teuchos::RCP<Data::XSSPhotonuclearDataExtractor> xss_data_extractor_h2;
Teuchos::RCP<TestPhotonuclearNeutronScatteringDistributionACEFactory> photonuclear_neutron_distribution_factory_h2;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( PhotonuclearNeutronScatteringDistributionACEFactory,
		   getReactionOrdering_h2 )
{
  ace_file_handler_h2.reset(new Data::ACEFileHandler( test_basic_h2_ace_file_name,
                                                   test_basic_h2_ace_table_name,
                                                   1u ) );

  xss_data_extractor_h2.reset(
   new Data::XSSPhotonuclearDataExtractor( ace_file_handler_h2->getTableNXSArray(),
                                      ace_file_handler_h2->getTableJXSArray(),
                                      ace_file_handler_h2->getTableXSSArray()));

  photonuclear_neutron_distribution_factory_h2.reset(
    new TestPhotonuclearNeutronScatteringDistributionACEFactory(
                             test_basic_h2_ace_table_name,
                             ace_file_handler_h2->getTableAtomicWeightRatio(),
			     *xss_data_extractor_h2 ) );

  // Only 1 reaction produces an outgoing neutron, reaction 50
  TEST_COMPARE( photonuclear_neutron_distribution_factory_h2->getReactionOrdering().size() ,==, 1);

  TEST_EQUALITY( photonuclear_neutron_distribution_factory_h2->getReactionOrdering().find(50)->second , 0);
}

TEUCHOS_UNIT_TEST( PhotonuclearNeutronScatteringDistributionACEFactory,
		   getReactionCMScattering_h2 )
{
  // Only 1 reaction produces an outgoing neutron, reaction 50. This reaction data takes place in CoM frame (-1)
  TEST_COMPARE( photonuclear_neutron_distribution_factory_h2->getReactionCMScattering().size() ,==, 1);

  TEST_EQUALITY( photonuclear_neutron_distribution_factory_h2->getReactionCMScattering().find(50)->second , true);

}

TEUCHOS_UNIT_TEST( PhotonuclearNeutronScatteringDistributionACEFactory,
		   getReactionWithIsotropicScatteringOnly_h2 )
{
   // Only 1 reaction produces an outgoing neutron, reaction 50. This dist_index is = 1 -> no iso
  TEST_COMPARE( photonuclear_neutron_distribution_factory_h2->getReactionsWithIsotropicScatteringOnly().size() ,==, 0);

}

TEUCHOS_UNIT_TEST( PhotonuclearNeutronScatteringDistributionACEFactory,
		   getReactionWithCoupledEnergyAngleDist_h2 )
{
  // Only 1 reaction produces an outgoing neutron, reaction 50. This dist_index is = 1 -> no energy angle dependence
  TEST_COMPARE( photonuclear_neutron_distribution_factory_h2->getReactionsWithCoupledEnergyAngleDist().size() ,==, 0);

}

TEUCHOS_UNIT_TEST( PhotonuclearNeutronScatteringDistributionACEFactory,
		   getReactionAngularDist_h2 )
{
  TEST_COMPARE( photonuclear_neutron_distribution_factory_h2->getReactionAngularDist().size() ,==, 1 );

  TEST_ASSERT( photonuclear_neutron_distribution_factory_h2->getReactionAngularDist().find(MonteCarlo::GAMMA__N_EXCITED_STATE_0_REACTION) != photonuclear_neutron_distribution_factory_h2->getReactionAngularDist().end());

  TEST_COMPARE( photonuclear_neutron_distribution_factory_h2->getReactionAngularDist().find(MonteCarlo::GAMMA__N_EXCITED_STATE_0_REACTION)->second.size() ,==, 1656 );

TEST_COMPARE( photonuclear_neutron_distribution_factory_h2->getReactionAngularDist().find(MonteCarlo::GAMMA__N_EXCITED_STATE_0_REACTION)->second.front() ,==, 35 );

TEST_COMPARE( photonuclear_neutron_distribution_factory_h2->getReactionAngularDist().find(MonteCarlo::GAMMA__N_EXCITED_STATE_0_REACTION)->second.back() ,==, 1 );

}

TEUCHOS_UNIT_TEST( PhotonuclearNeutronScatteringDistributionACEFactory,
		   getReactionAngularDistStartIndex_h2 )
{
  TEST_COMPARE( photonuclear_neutron_distribution_factory_h2->getReactionAngularDistStartIndex().size() ,==, 1 );
  TEST_COMPARE( photonuclear_neutron_distribution_factory_h2->getReactionAngularDistStartIndex().find(MonteCarlo::GAMMA__N_EXCITED_STATE_0_REACTION)->second ,==, 0 );

}

TEUCHOS_UNIT_TEST( PhotonuclearNeutronScatteringDistributionACEFactory,
		   getReactionEnergyDist_h2 )
{

  TEST_COMPARE(  photonuclear_neutron_distribution_factory_h2->getReactionEnergyDist().find(MonteCarlo::GAMMA__N_EXCITED_STATE_0_REACTION)->second.size() ,==, 11 );

  TEST_COMPARE(  photonuclear_neutron_distribution_factory_h2->getReactionEnergyDist().find(MonteCarlo::GAMMA__N_EXCITED_STATE_0_REACTION)->second.front() ,==, 0 );

  TEST_COMPARE(  photonuclear_neutron_distribution_factory_h2->getReactionEnergyDist().find(MonteCarlo::GAMMA__N_EXCITED_STATE_0_REACTION)->second.back() ,==, 6.66255E-01 );

}

TEUCHOS_UNIT_TEST( PhotonuclearNeutronScatteringDistributionACEFactory,
		   getReactionEnergyDistStartIndex_h2 )
{

  TEST_COMPARE(  photonuclear_neutron_distribution_factory_h2->getReactionEnergyDistStartIndex().size() ,==, 1 );

  TEST_COMPARE(  photonuclear_neutron_distribution_factory_h2->getReactionEnergyDistStartIndex().find(MonteCarlo::GAMMA__N_EXCITED_STATE_0_REACTION)->second ,==, 0 );

}
//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor & clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_basic_h2_ace_file",
		 &test_basic_h2_ace_file_name,
		 "Test basic H2 ACE file name" );
  clp.setOption( "test_basic_h2_ace_table",
		 &test_basic_h2_ace_table_name,
		 "Test basic H2 ACE table name in basic ACE file" );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

//---------------------------------------------------------------------------//
// end tstPhotonuclearNeutronScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//

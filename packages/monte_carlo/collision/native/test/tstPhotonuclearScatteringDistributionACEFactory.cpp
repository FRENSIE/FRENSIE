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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotonuclearScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_NuclearReactionType.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSPhotonuclearDataExtractor.hpp"
#include "MonteCarlo_PhotonuclearReactionType.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestPhotonuclearScatteringDistributionACEFactory : public MonteCarlo::PhotonuclearScatteringDistributionACEFactory
{
public:
  TestPhotonuclearScatteringDistributionACEFactory(
                         const std::string& table_name,
			 const double atomic_weight_ratio,
			 const Data::XSSPhotonuclearDataExtractor raw_nuclide_data )
    : MonteCarlo::PhotonuclearScatteringDistributionACEFactory( table_name,
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
std::string test_basic_c12_ace_file_name;
std::string test_basic_c12_ace_table_name;

Teuchos::RCP<Data::ACEFileHandler> ace_file_handler_c12;
Teuchos::RCP<Data::XSSPhotonuclearDataExtractor> xss_data_extractor_c12;
Teuchos::RCP<TestPhotonuclearScatteringDistributionACEFactory> photonuclear_distribution_factory_c12;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( PhotonuclearScatteringDistributionACEFactory, 
		   getReactionOrdering_c12 )
{
  ace_file_handler_c12.reset(new Data::ACEFileHandler( test_basic_c12_ace_file_name,
                                                   test_basic_c12_ace_table_name,
                                                   1u ) );

  xss_data_extractor_c12.reset(
   new Data::XSSPhotonuclearDataExtractor( ace_file_handler_c12->getTableNXSArray(),
                                      ace_file_handler_c12->getTableJXSArray(),
                                      ace_file_handler_c12->getTableXSSArray()));
 
  photonuclear_distribution_factory_c12.reset( 
    new TestPhotonuclearScatteringDistributionACEFactory(
                             test_basic_c12_ace_table_name,
                             ace_file_handler_c12->getTableAtomicWeightRatio(),
			     *xss_data_extractor_c12 ) );

  // Only 1 reaction produces an outgoing photon, reaction 5
  TEST_COMPARE( photonuclear_distribution_factory_c12->getReactionOrdering().size() ,==, 1);

  TEST_EQUALITY( photonuclear_distribution_factory_c12->getReactionOrdering().find(5)->second , 0);

}

TEUCHOS_UNIT_TEST( PhotonuclearScatteringDistributionACEFactory, 
		   getReactionCMScattering_c12 )
{
  // Only 1 reaction produces an outgoing photon, reaction 5
  TEST_COMPARE( photonuclear_distribution_factory_c12->getReactionCMScattering().size() ,==, 1);

  TEST_EQUALITY( photonuclear_distribution_factory_c12->getReactionCMScattering().find(5)->second , true);

}

TEUCHOS_UNIT_TEST( PhotonuclearScatteringDistributionACEFactory, 
		   getReactionWithIsotropicScatteringOnly_c12 )
{
  // Only 1 reaction produces an outgoing photon, reaction 5. This reaction has dist_index = 0 -> iso scat only
  TEST_COMPARE( photonuclear_distribution_factory_c12->getReactionsWithIsotropicScatteringOnly().size() ,==, 1);

  TEST_ASSERT( photonuclear_distribution_factory_c12->getReactionsWithIsotropicScatteringOnly().find(MonteCarlo::GAMMA__ANYTHING_REACTION) != photonuclear_distribution_factory_c12->getReactionsWithIsotropicScatteringOnly().end());

}

TEUCHOS_UNIT_TEST( PhotonuclearScatteringDistributionACEFactory, 
		   getReactionWithCoupledEnergyAngleDist_c12 )
{
  // Only 1 reaction produces an outgoing photon, reaction 5. This reaction has dist_index = 0 -> no Energy Angle dependence
  TEST_COMPARE( photonuclear_distribution_factory_c12->getReactionsWithCoupledEnergyAngleDist().size() ,==, 0);
}

TEUCHOS_UNIT_TEST( PhotonuclearScatteringDistributionACEFactory, 
		   getReactionAngularDist_c12 )
{
TEST_COMPARE( photonuclear_distribution_factory_c12->getReactionAngularDist().size() ,==, 0 );

  TEST_ASSERT( photonuclear_distribution_factory_c12->getReactionAngularDist().find(MonteCarlo::GAMMA__ANYTHING_REACTION) == photonuclear_distribution_factory_c12->getReactionAngularDist().end());

}

TEUCHOS_UNIT_TEST( PhotonuclearScatteringDistributionACEFactory, 
		   getReactionAngularDistStartIndex_c12 )
{
  TEST_COMPARE( photonuclear_distribution_factory_c12->getReactionAngularDistStartIndex().size() ,==, 0 );

}

TEUCHOS_UNIT_TEST( PhotonuclearScatteringDistributionACEFactory, 
		   getReactionEnergyDist_c12 )
{

  TEST_COMPARE(  photonuclear_distribution_factory_c12->getReactionEnergyDist().find(MonteCarlo::GAMMA__ANYTHING_REACTION)->second.size() ,==, 11739 );

  TEST_COMPARE(  photonuclear_distribution_factory_c12->getReactionEnergyDist().find(MonteCarlo::GAMMA__ANYTHING_REACTION)->second.front() ,==, 0 );

  TEST_COMPARE(  photonuclear_distribution_factory_c12->getReactionEnergyDist().find(MonteCarlo::GAMMA__ANYTHING_REACTION)->second.back() ,==, 1 );

}

TEUCHOS_UNIT_TEST( PhotonuclearScatteringDistributionACEFactory, 
		   getReactionEnergyDistStartIndex_c12 )
{

  TEST_COMPARE(  photonuclear_distribution_factory_c12->getReactionEnergyDistStartIndex().size() ,==, 1 );

  TEST_COMPARE(  photonuclear_distribution_factory_c12->getReactionEnergyDistStartIndex().find(MonteCarlo::GAMMA__ANYTHING_REACTION)->second ,==, 0 );

}
//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor & clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_basic_c12_ace_file",
		 &test_basic_c12_ace_file_name,
		 "Test basic C12 ACE file name" );
  clp.setOption( "test_basic_c12_ace_table",
		 &test_basic_c12_ace_table_name,
		 "Test basic C12 ACE table name in basic ACE file" );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

//---------------------------------------------------------------------------//
// end tstPhotonuclearScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//

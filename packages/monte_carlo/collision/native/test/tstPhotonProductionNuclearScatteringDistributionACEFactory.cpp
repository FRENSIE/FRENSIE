//---------------------------------------------------------------------------//
//!
//! \file   tstPhotonProductionNuclearScatteringDistributionACEFactory.cpp
//! \author Alex Robinson
//! \brief  Neutron-neutron scattering distribution factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotonProductionNuclearScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_NuclearReactionType.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestPhotonProductionNuclearScatteringDistributionACEFactory : public MonteCarlo::PhotonProductionNuclearScatteringDistributionACEFactory
{
public:
  TestPhotonProductionNuclearScatteringDistributionACEFactory(
                         const std::string& table_name,
			                   const double atomic_weight_ratio,
			                   const Data::XSSNeutronDataExtractor raw_nuclide_data )
    : MonteCarlo::PhotonProductionNuclearScatteringDistributionACEFactory( table_name,
                                                           atomic_weight_ratio,
							   raw_nuclide_data )
  { /* ... */ }
  
  ~TestPhotonProductionNuclearScatteringDistributionACEFactory()
  { /* ... */ }

  using MonteCarlo::PhotonProductionNuclearScatteringDistributionACEFactory::getReactionOrdering;
  using MonteCarlo::PhotonProductionNuclearScatteringDistributionACEFactory::getReactionCMScattering;
  using MonteCarlo::PhotonProductionNuclearScatteringDistributionACEFactory::getReactionsWithIsotropicScatteringOnly;
  using MonteCarlo::PhotonProductionNuclearScatteringDistributionACEFactory::getReactionsWithCoupledEnergyAngleDist;
  using MonteCarlo::PhotonProductionNuclearScatteringDistributionACEFactory::getReactionAngularDist;
  using MonteCarlo::PhotonProductionNuclearScatteringDistributionACEFactory::getReactionAngularDistStartIndex;
  using MonteCarlo::PhotonProductionNuclearScatteringDistributionACEFactory::getReactionEnergyDist;
  using MonteCarlo::PhotonProductionNuclearScatteringDistributionACEFactory::getReactionEnergyDistStartIndex;
};
//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::string test_basic_h1_ace_file_name;
std::string test_basic_h1_ace_table_name;

Teuchos::RCP<Data::ACEFileHandler> ace_file_handler_h1;
Teuchos::RCP<Data::XSSNeutronDataExtractor> xss_data_extractor_h1;
Teuchos::RCP<TestPhotonProductionNuclearScatteringDistributionACEFactory> neutron_distribution_factory_h1;

std::string test_basic_o16_ace_file_name;
std::string test_basic_o16_ace_table_name;

Teuchos::RCP<Data::ACEFileHandler> ace_file_handler_o16;
Teuchos::RCP<Data::XSSNeutronDataExtractor> xss_data_extractor_o16;
Teuchos::RCP<TestPhotonProductionNuclearScatteringDistributionACEFactory> neutron_distribution_factory_o16;
//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( PhotonProductionNuclearScatteringDistributionACEFactory, 
		   getReactionOrdering_h1 )
{


  ace_file_handler_h1.reset(new Data::ACEFileHandler( test_basic_h1_ace_file_name,
                                                   test_basic_h1_ace_table_name,
                                                   1u ) );

  xss_data_extractor_h1.reset(
   new Data::XSSNeutronDataExtractor( ace_file_handler_h1->getTableNXSArray(),
                                      ace_file_handler_h1->getTableJXSArray(),
                                      ace_file_handler_h1->getTableXSSArray()));
   
//  MonteCarlo::PhotonProductionNuclearScatteringDistributionACEFactory
  neutron_distribution_factory_h1.reset( 
    new TestPhotonProductionNuclearScatteringDistributionACEFactory(
                             test_basic_h1_ace_table_name,
                             ace_file_handler_h1->getTableAtomicWeightRatio(),
			                       *xss_data_extractor_h1 ) );

  TEST_COMPARE( neutron_distribution_factory_h1->getReactionOrdering().size() ,==, 1);
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( PhtonProductionNuclearScatteringDistributionACEFactory, 
		   getReactionOrdering_o16 )
{


  ace_file_handler_o16.reset(new Data::ACEFileHandler( test_basic_o16_ace_file_name,
                                                       test_basic_o16_ace_table_name,
                                                       1u ) );

  xss_data_extractor_o16.reset(
   new Data::XSSNeutronDataExtractor( ace_file_handler_o16->getTableNXSArray(),
                                      ace_file_handler_o16->getTableJXSArray(),
                                      ace_file_handler_o16->getTableXSSArray()));
   
//  MonteCarlo::PhotonProductionNuclearScatteringDistributionACEFactory
  neutron_distribution_factory_o16.reset( 
    new TestPhotonProductionNuclearScatteringDistributionACEFactory(
			     test_basic_o16_ace_table_name,
                             ace_file_handler_o16->getTableAtomicWeightRatio(),
			                       *xss_data_extractor_o16 ) );

  TEST_COMPARE( neutron_distribution_factory_o16->getReactionOrdering().size() ,==, 131);
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( PhotonProductionNuclearScatteringDistributionACEFactory, 
		   getReactionEnergyDist_h1 )
{
  TEST_COMPARE( neutron_distribution_factory_h1->getReactionEnergyDist().size() ,==, 1 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_basic_h1_ace_file",
		 &test_basic_h1_ace_file_name,
		 "Test basic H1 ACE file name" );
  clp.setOption( "test_basic_h1_ace_table",
		 &test_basic_h1_ace_table_name,
		 "Test basic H1 ACE table name in basic ACE file" );

  clp.setOption( "test_basic_o16_ace_file",
		 &test_basic_o16_ace_file_name,
		 "Test basic O16 ACE file name" );
  clp.setOption( "test_basic_o16_ace_table",
		 &test_basic_o16_ace_table_name,
		 "Test basic O16 ACE table name in basic ACE file" );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

//---------------------------------------------------------------------------//
// end tstNeutronNuclearScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//

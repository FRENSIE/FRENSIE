//---------------------------------------------------------------------------//
//!
//! \file   tstNeutronNuclearScatteringDistributionACEFactory.cpp
//! \author Alex Robinson
//! \brief  Neutron-neutron scattering distribution factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_NeutronNuclearScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_NuclearReactionType.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestNeutronNuclearScatteringDistributionACEFactory : public MonteCarlo::NeutronNuclearScatteringDistributionACEFactory
{
public:
  TestNeutronNuclearScatteringDistributionACEFactory(
                         const std::string& table_name,
			 const double atomic_weight_ratio,
			 const Data::XSSNeutronDataExtractor raw_nuclide_data )
    : MonteCarlo::NeutronNuclearScatteringDistributionACEFactory( table_name,
                                                           atomic_weight_ratio,
							   raw_nuclide_data )
  { /* ... */ }

  ~TestNeutronNuclearScatteringDistributionACEFactory()
  { /* ... */ }

  using MonteCarlo::NeutronNuclearScatteringDistributionACEFactory::getReactionOrdering;
  using MonteCarlo::NeutronNuclearScatteringDistributionACEFactory::getReactionCMScattering;
  using MonteCarlo::NeutronNuclearScatteringDistributionACEFactory::getReactionsWithIsotropicScatteringOnly;
  using MonteCarlo::NeutronNuclearScatteringDistributionACEFactory::getReactionsWithCoupledEnergyAngleDist;
  using MonteCarlo::NeutronNuclearScatteringDistributionACEFactory::getReactionAngularDist;
  using MonteCarlo::NeutronNuclearScatteringDistributionACEFactory::getReactionAngularDistStartIndex;
  using MonteCarlo::NeutronNuclearScatteringDistributionACEFactory::getReactionEnergyDist;
  using MonteCarlo::NeutronNuclearScatteringDistributionACEFactory::getReactionEnergyDistStartIndex;
};

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<const Data::XSSNeutronDataExtractor> xss_data_extractor_h1;
std::shared_ptr<const TestNeutronNuclearScatteringDistributionACEFactory> neutron_distribution_factory_h1;

std::shared_ptr<const Data::XSSNeutronDataExtractor> xss_data_extractor_o16;
std::shared_ptr<const TestNeutronNuclearScatteringDistributionACEFactory> neutron_distribution_factory_o16;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a factory can be constructed
FRENSIE_UNIT_TEST( NeutronNuclearScatteringDistributionACEFactory,
                   constructor_h1 )
{
  FRENSIE_CHECK_NO_THROW( neutron_distribution_factory_h1.reset(
    new TestNeutronNuclearScatteringDistributionACEFactory(
                             "test_h1_table",
                             0.999167,
			     *xss_data_extractor_h1 ) ) );
}

//---------------------------------------------------------------------------//
// Check that a factory can be constructed
FRENSIE_UNIT_TEST( NeutronNuclearScatteringDistributionACEFactory,
                   constructor_o16 )
{
  FRENSIE_CHECK_NO_THROW( neutron_distribution_factory_o16.reset(
    new TestNeutronNuclearScatteringDistributionACEFactory(
                             "test_o16_table",
                             15.8575,
			     *xss_data_extractor_o16 ) ) );
}

//---------------------------------------------------------------------------//
// Check that the reaction ordering can be returned
FRENSIE_UNIT_TEST( NeutronNuclearScatteringDistributionACEFactory,
		   getReactionOrdering_h1 )
{
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_h1->getReactionOrdering().size(),
                 0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction ordering can be returned
FRENSIE_UNIT_TEST( NeutronNuclearScatteringDistributionACEFactory,
		   getReactionOrdering_o16 )
{
  FRENSIE_CHECK_EQUAL(neutron_distribution_factory_o16->getReactionOrdering().size(),
                17);
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionOrdering().find(MonteCarlo::N__ANYTHING_REACTION)->second, 0 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionOrdering().find(MonteCarlo::N__N_CONTINUUM_REACTION)->second, 16 );
}

//---------------------------------------------------------------------------//
// Check that the reactions with CM scattering distributions can be returned
FRENSIE_UNIT_TEST( NeutronNuclearScatteringDistributionACEFactory,
		   getReactionCMScattering_h1 )
{
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_h1->getReactionCMScattering().size(), 1 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_h1->getReactionCMScattering().find(MonteCarlo::N__N_ELASTIC_REACTION)->second, true );
}

//---------------------------------------------------------------------------//
// Check that the reactions with CM scattering distributions can be returned
FRENSIE_UNIT_TEST( NeutronNuclearScatteringDistributionACEFactory,
		   getReactionCMScattering_o16 )
{
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionCMScattering().size(), 18);
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionCMScattering().find(MonteCarlo::N__N_ELASTIC_REACTION)->second, true );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionCMScattering().find(MonteCarlo::N__ANYTHING_REACTION)->second, true );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionCMScattering().find(MonteCarlo::N__N_CONTINUUM_REACTION)->second, true );
}

//---------------------------------------------------------------------------//
// Check that the reactions with purely isotropic scattering can be returned
FRENSIE_UNIT_TEST( NeutronNuclearScatteringDistributionACEFactory,
		   getReactionsWithIsotropicScatteringOnly_h1 )
{
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_h1->getReactionsWithIsotropicScatteringOnly().size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the reactions with purely isotropic scattering can be returned
FRENSIE_UNIT_TEST( NeutronNuclearScatteringDistributionACEFactory,
		   getReactionsWithIsotropicScatteringOnly_o16 )
{
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionsWithIsotropicScatteringOnly().size(), 2 );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionsWithIsotropicScatteringOnly().count(MonteCarlo::N__N_EXCITED_STATE_6_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionsWithIsotropicScatteringOnly().count(MonteCarlo::N__N_EXCITED_STATE_7_REACTION) );
}

//---------------------------------------------------------------------------//
// Check that reactions with coupled energy-angle distributions can be returned
FRENSIE_UNIT_TEST( NeutronNuclearScatteringDistributionACEFactory,
		   getReactionWithCoupledEnergyAngleDist_h1 )
{
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_h1->getReactionsWithCoupledEnergyAngleDist().size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that reactions with coupled energy-angle distributions can be returned
FRENSIE_UNIT_TEST( NeutronNuclearScatteringDistributionACEFactory,
		   getReactionWithCoupledEnergyAngleDist_o16 )
{
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionsWithCoupledEnergyAngleDist().size(), 10 );

  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionsWithCoupledEnergyAngleDist().count(MonteCarlo::N__ANYTHING_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionsWithCoupledEnergyAngleDist().count(MonteCarlo::N__2N_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionsWithCoupledEnergyAngleDist().count(MonteCarlo::N__N_ALPHA_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionsWithCoupledEnergyAngleDist().count(MonteCarlo::N__N_3ALPHA_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionsWithCoupledEnergyAngleDist().count(MonteCarlo::N__N_P_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionsWithCoupledEnergyAngleDist().count(MonteCarlo::N__N_D_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionsWithCoupledEnergyAngleDist().count(MonteCarlo::N__2N_P_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionsWithCoupledEnergyAngleDist().count(MonteCarlo::N__N_2P_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionsWithCoupledEnergyAngleDist().count(MonteCarlo::N__N_P_ALPHA_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionsWithCoupledEnergyAngleDist().count(MonteCarlo::N__N_CONTINUUM_REACTION) );
}

//---------------------------------------------------------------------------//
// Check that the angular distribution of a reaction can be returned
FRENSIE_UNIT_TEST( NeutronNuclearScatteringDistributionACEFactory,
		   getReactionAngularDist_h1 )
{
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_h1->getReactionAngularDist().size(), 1 );
  FRENSIE_CHECK( neutron_distribution_factory_h1->getReactionAngularDist().count(MonteCarlo::N__N_ELASTIC_REACTION) );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_h1->getReactionAngularDist().find(MonteCarlo::N__N_ELASTIC_REACTION)->second.size(), 1291 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_h1->getReactionAngularDist().find(MonteCarlo::N__N_ELASTIC_REACTION)->second.front(), 96 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_h1->getReactionAngularDist().find(MonteCarlo::N__N_ELASTIC_REACTION)->second.back(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the angular distribution of a reaction can be returned
FRENSIE_UNIT_TEST( NeutronNuclearScatteringDistributionACEFactory,
		   getReactionAngularDist_o16 )
{
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionAngularDist().size(), 6 );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionAngularDist().count(MonteCarlo::N__N_ELASTIC_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionAngularDist().count(MonteCarlo::N__N_EXCITED_STATE_1_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionAngularDist().count(MonteCarlo::N__N_EXCITED_STATE_2_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionAngularDist().count(MonteCarlo::N__N_EXCITED_STATE_3_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionAngularDist().count(MonteCarlo::N__N_EXCITED_STATE_4_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionAngularDist().count(MonteCarlo::N__N_EXCITED_STATE_5_REACTION) );

  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionAngularDist().find(MonteCarlo::N__N_ELASTIC_REACTION)->second.size(), 101748 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionAngularDist().find(MonteCarlo::N__N_ELASTIC_REACTION)->second.front(), 1175 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionAngularDist().find(MonteCarlo::N__N_ELASTIC_REACTION)->second.back(), 1 );

  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionAngularDist().find(MonteCarlo::N__N_EXCITED_STATE_1_REACTION)->second.size(), 1475 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionAngularDist().find(MonteCarlo::N__N_EXCITED_STATE_1_REACTION)->second.front(), 40 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionAngularDist().find(MonteCarlo::N__N_EXCITED_STATE_1_REACTION)->second.back(), 1 );

  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionAngularDist().find(MonteCarlo::N__N_EXCITED_STATE_2_REACTION)->second.size(), 1475 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionAngularDist().find(MonteCarlo::N__N_EXCITED_STATE_2_REACTION)->second.front(), 40 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionAngularDist().find(MonteCarlo::N__N_EXCITED_STATE_2_REACTION)->second.back(), 1 );

  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionAngularDist().find(MonteCarlo::N__N_EXCITED_STATE_3_REACTION)->second.size(), 1097 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionAngularDist().find(MonteCarlo::N__N_EXCITED_STATE_3_REACTION)->second.front(), 31 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionAngularDist().find(MonteCarlo::N__N_EXCITED_STATE_3_REACTION)->second.back(), 1 );

  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionAngularDist().find(MonteCarlo::N__N_EXCITED_STATE_4_REACTION)->second.size(), 1084 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionAngularDist().find(MonteCarlo::N__N_EXCITED_STATE_4_REACTION)->second.front(), 30 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionAngularDist().find(MonteCarlo::N__N_EXCITED_STATE_4_REACTION)->second.back(), 1 );

  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionAngularDist().find(MonteCarlo::N__N_EXCITED_STATE_5_REACTION)->second.size(), 1098 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionAngularDist().find(MonteCarlo::N__N_EXCITED_STATE_5_REACTION)->second.front(), 23 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionAngularDist().find(MonteCarlo::N__N_EXCITED_STATE_5_REACTION)->second.back(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the reaction angular distribution start index can be returned
FRENSIE_UNIT_TEST( NeutronNuclearScatteringDistributionACEFactory,
		   getReactionAngularDistStartIndex_h1 )
{
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_h1->getReactionAngularDistStartIndex().size(), 1 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_h1->getReactionAngularDistStartIndex().find(MonteCarlo::N__N_ELASTIC_REACTION)->second, 0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction angular distribution start index can be returned
FRENSIE_UNIT_TEST( NeutronNuclearScatteringDistributionACEFactory,
		   getReactionAngularDistStartIndex_o16 )
{
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionAngularDistStartIndex().size(), 6 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionAngularDistStartIndex().find(MonteCarlo::N__N_ELASTIC_REACTION)->second, 0 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionAngularDistStartIndex().find(MonteCarlo::N__N_EXCITED_STATE_1_REACTION)->second, 101748 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionAngularDistStartIndex().find(MonteCarlo::N__N_EXCITED_STATE_2_REACTION)->second, 103223 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionAngularDistStartIndex().find(MonteCarlo::N__N_EXCITED_STATE_3_REACTION)->second, 104698 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionAngularDistStartIndex().find(MonteCarlo::N__N_EXCITED_STATE_4_REACTION)->second, 105795 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionAngularDistStartIndex().find(MonteCarlo::N__N_EXCITED_STATE_5_REACTION)->second, 106879 );
}

//---------------------------------------------------------------------------//
// Check that the reaction energy distribution can be returned
FRENSIE_UNIT_TEST( NeutronNuclearScatteringDistributionACEFactory,
		   getReactionEnergyDist_h1 )
{
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_h1->getReactionEnergyDist().size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction energy distribution can be returned
FRENSIE_UNIT_TEST( NeutronNuclearScatteringDistributionACEFactory,
		   getReactionEnergyDist_o16 )
{
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().size(), 17 );

  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionEnergyDist().count(MonteCarlo::N__ANYTHING_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionEnergyDist().count(MonteCarlo::N__2N_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionEnergyDist().count(MonteCarlo::N__N_ALPHA_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionEnergyDist().count(MonteCarlo::N__N_3ALPHA_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionEnergyDist().count(MonteCarlo::N__N_P_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionEnergyDist().count(MonteCarlo::N__N_D_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionEnergyDist().count(MonteCarlo::N__2N_P_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionEnergyDist().count(MonteCarlo::N__N_2P_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionEnergyDist().count(MonteCarlo::N__N_P_ALPHA_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionEnergyDist().count(MonteCarlo::N__N_EXCITED_STATE_1_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionEnergyDist().count(MonteCarlo::N__N_EXCITED_STATE_2_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionEnergyDist().count(MonteCarlo::N__N_EXCITED_STATE_3_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionEnergyDist().count(MonteCarlo::N__N_EXCITED_STATE_4_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionEnergyDist().count(MonteCarlo::N__N_EXCITED_STATE_5_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionEnergyDist().count(MonteCarlo::N__N_EXCITED_STATE_6_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionEnergyDist().count(MonteCarlo::N__N_EXCITED_STATE_7_REACTION) );
  FRENSIE_CHECK( neutron_distribution_factory_o16->getReactionEnergyDist().count(MonteCarlo::N__N_CONTINUUM_REACTION) );

  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__ANYTHING_REACTION)->second.size(), 5438 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__ANYTHING_REACTION)->second.front(), 0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__ANYTHING_REACTION)->second.back(), 9.333427, 1e-15 );

  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__2N_REACTION)->second.size(), 3861 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__2N_REACTION)->second.front(), 0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__2N_REACTION)->second.back(), 0.7874268, 1e-15 );

  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_ALPHA_REACTION)->second.size(), 10597 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_ALPHA_REACTION)->second.front(), 0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_ALPHA_REACTION)->second.back(), 1.052822, 1e-15 );

  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_3ALPHA_REACTION)->second.size(), 3692 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_3ALPHA_REACTION)->second.front(), 0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_3ALPHA_REACTION)->second.back(), 0.7801906, 1e-15 );

  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_D_REACTION)->second.size(), 1718 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_D_REACTION)->second.front(), 0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_D_REACTION)->second.back(), 0.6012564 , 1e-15 );

  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__2N_P_REACTION)->second.size(), 966 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__2N_P_REACTION)->second.front(), 0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__2N_P_REACTION)->second.back(), 0.5165388, 1e-15 );

  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_2P_REACTION)->second.size(), 971 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_2P_REACTION)->second.front(), 0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_2P_REACTION)->second.back(), 0.5165388, 1e-15 );

  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_P_ALPHA_REACTION)->second.size(), 916 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_P_ALPHA_REACTION)->second.front(), 0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_P_ALPHA_REACTION)->second.back(), 0.502482, 1e-15 );

  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_EXCITED_STATE_1_REACTION)->second.size(), 11 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_EXCITED_STATE_1_REACTION)->second.front(), 0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_EXCITED_STATE_1_REACTION)->second.back(), 0.8848775, 1e-15 );

  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_EXCITED_STATE_2_REACTION)->second.size(), 11 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_EXCITED_STATE_2_REACTION)->second.front(), 0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_EXCITED_STATE_2_REACTION)->second.back(), 0.8848775, 1e-15 );

  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_EXCITED_STATE_3_REACTION)->second.size(), 11 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_EXCITED_STATE_3_REACTION)->second.front(), 0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_EXCITED_STATE_3_REACTION)->second.back(), 0.8848775, 1e-15 );

  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_EXCITED_STATE_4_REACTION)->second.size(), 11 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_EXCITED_STATE_4_REACTION)->second.front(), 0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_EXCITED_STATE_4_REACTION)->second.back(), 0.8848775, 1e-15 );

  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_EXCITED_STATE_5_REACTION)->second.size(), 11 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_EXCITED_STATE_5_REACTION)->second.front(), 0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_EXCITED_STATE_5_REACTION)->second.back(), 0.8848775, 1e-15 );

  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_EXCITED_STATE_6_REACTION)->second.size(), 11 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_EXCITED_STATE_6_REACTION)->second.front(), 0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_EXCITED_STATE_6_REACTION)->second.back(), 0.8848775, 1e-15 );

  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_EXCITED_STATE_7_REACTION)->second.size(), 11 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_EXCITED_STATE_7_REACTION)->second.front(), 0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_EXCITED_STATE_7_REACTION)->second.back(), 0.8848775, 1e-15 );

  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_CONTINUUM_REACTION)->second.size(), 8892 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_CONTINUUM_REACTION)->second.front(), 0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( neutron_distribution_factory_o16->getReactionEnergyDist().find(MonteCarlo::N__N_CONTINUUM_REACTION)->second.back(), 1.007868, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the reaction energy distribution start index can be returned
FRENSIE_UNIT_TEST( NeutronNuclearScatteringDistributionACEFactory,
		   getReactionEnergyDistStartIndex_h1 )
{
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_h1->getReactionEnergyDistStartIndex().size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction energy distribution start index can be returned
FRENSIE_UNIT_TEST( NeutronNuclearScatteringDistributionACEFactory,
		   getReactionEnergyDistStartIndex_o16 )
{
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDistStartIndex().find(MonteCarlo::N__ANYTHING_REACTION)->second, 34 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDistStartIndex().find(MonteCarlo::N__2N_REACTION)->second, 5472 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDistStartIndex().find(MonteCarlo::N__N_ALPHA_REACTION)->second, 9333 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDistStartIndex().find(MonteCarlo::N__N_3ALPHA_REACTION)->second, 19930 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDistStartIndex().find(MonteCarlo::N__N_P_REACTION)->second, 23622 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDistStartIndex().find(MonteCarlo::N__N_D_REACTION)->second, 29905 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDistStartIndex().find(MonteCarlo::N__2N_P_REACTION)->second, 31623 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDistStartIndex().find(MonteCarlo::N__N_2P_REACTION)->second, 32589 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDistStartIndex().find(MonteCarlo::N__N_P_ALPHA_REACTION)->second, 33560 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDistStartIndex().find(MonteCarlo::N__N_EXCITED_STATE_1_REACTION)->second, 34476 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDistStartIndex().find(MonteCarlo::N__N_EXCITED_STATE_2_REACTION)->second, 34487 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDistStartIndex().find(MonteCarlo::N__N_EXCITED_STATE_3_REACTION)->second, 34498 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDistStartIndex().find(MonteCarlo::N__N_EXCITED_STATE_4_REACTION)->second, 34509 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDistStartIndex().find(MonteCarlo::N__N_EXCITED_STATE_5_REACTION)->second, 34520 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDistStartIndex().find(MonteCarlo::N__N_EXCITED_STATE_6_REACTION)->second, 34531 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDistStartIndex().find(MonteCarlo::N__N_EXCITED_STATE_7_REACTION)->second, 34542 );
  FRENSIE_CHECK_EQUAL( neutron_distribution_factory_o16->getReactionEnergyDistStartIndex().find(MonteCarlo::N__N_CONTINUUM_REACTION)->second, 34553 );
}

//---------------------------------------------------------------------------//
// Check that an elastic scattering distribution can be constructed
FRENSIE_UNIT_TEST( NeutronNuclearScatteringDistributionACEFactory,
		   createScatteringDistribution_elastic_h1 )
{
  MonteCarlo::SimulationProperties properties;
  properties.setFreeGasThreshold( 300 );
  
  std::shared_ptr<const MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::NeutronState> > scattering_dist;

  // Sample the hydrogen elastic scattering distribution
  neutron_distribution_factory_h1->createScatteringDistribution(
					     MonteCarlo::N__N_ELASTIC_REACTION,
                                             properties,
                                             scattering_dist );

  // Check that the distribution has been constructed correctly
  // (above threshold)
  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setDirection( 0.0, 0.0, 1.0 );
  neutron.setEnergy( 1.0 );

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_dist->scatterParticle( neutron, 1e-5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( neutron.getEnergy(), 0.495733375378828611, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( neutron.getXDirection(),
                                   -0.707199874757386215,
                                   1e-15 );
  FRENSIE_CHECK_SMALL( neutron.getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( neutron.getZDirection(),
                          0.707013675357936244,
                          1e-15 );

  // Check that the distribution has been constructed correctly
  // (below threshold)
  neutron.setDirection( 0.0, 0.0, 1.0 );
  neutron.setEnergy( 1e-6 );

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  scattering_dist->scatterParticle( neutron, 1e-5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( neutron.getEnergy(),
                          3.70817360114217509e-06,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( neutron.getXDirection(),
                                   0.707214962606361519,
                                   1e-15 );
  FRENSIE_CHECK_SMALL( neutron.getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( neutron.getZDirection(),
                                   -0.706998583213348852,
                                   1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that an elastic scattering distribution can be constructed
FRENSIE_UNIT_TEST( NeutronNuclearScatteringDistributionACEFactory,
		   createScatteringDistribution_elastic_o16 )
{
  std::shared_ptr<const MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::NeutronState> > scattering_dist;

  MonteCarlo::SimulationProperties properties;
  properties.setFreeGasThreshold( 300 );
  
  neutron_distribution_factory_o16->createScatteringDistribution(
					     MonteCarlo::N__N_ELASTIC_REACTION,
                                             properties,
                                             scattering_dist );

  // Check that the distribution has been constructed correctly
  // (above threshold)
  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setDirection( 0.0, 0.0, 1.0 );
  neutron.setEnergy( 1.0 );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_dist->scatterParticle( neutron, 1e-5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( neutron.getEnergy(), 0.776792709975305806, 1e-15 );
  FRENSIE_CHECK_SMALL( neutron.getXDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( neutron.getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( neutron.getZDirection(), -1.0, 1e-15 );

  // Check that the distribution has been constructed correctly
  // (below threshold)
  neutron.setDirection( 0.0, 0.0, 1.0 );
  neutron.setEnergy( 1e-6 );

  fake_stream.resize( 3 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.0;
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_dist->scatterParticle( neutron, 1e-5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( neutron.getEnergy(),
                          6.76486278618255267e-07,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( neutron.getXDirection(),
                                   -0.0743435483211353637,
                                   1e-15 );
  FRENSIE_CHECK_SMALL( neutron.getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( neutron.getZDirection(),
                          -0.997232689407553941,
                          1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that all other scattering distributions can be constructed
FRENSIE_UNIT_TEST( NeutronNuclearScatteringDistributionACEFactory,
		   createScatteringDistribution_all )
{
  std::shared_ptr<const MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::NeutronState> > scattering_dist;

  MonteCarlo::SimulationProperties properties;

  neutron_distribution_factory_o16->createScatteringDistribution(
					      MonteCarlo::N__ANYTHING_REACTION,
                                              properties,
                                              scattering_dist );

  FRENSIE_CHECK( scattering_dist.get() != NULL );

  neutron_distribution_factory_o16->createScatteringDistribution(
					      MonteCarlo::N__2N_REACTION,
                                              properties,
					      scattering_dist );

  FRENSIE_CHECK( scattering_dist.get() != NULL );

  neutron_distribution_factory_o16->createScatteringDistribution(
					       MonteCarlo::N__N_ALPHA_REACTION,
                                               properties,
					       scattering_dist );

  FRENSIE_CHECK( scattering_dist.get() != NULL );

  neutron_distribution_factory_o16->createScatteringDistribution(
					      MonteCarlo::N__N_3ALPHA_REACTION,
                                              properties,
                                              scattering_dist );

  FRENSIE_CHECK( scattering_dist.get() != NULL );

  neutron_distribution_factory_o16->createScatteringDistribution(
					       MonteCarlo::N__N_D_REACTION,
                                               properties,
					       scattering_dist );

  FRENSIE_CHECK( scattering_dist.get() != NULL );

  neutron_distribution_factory_o16->createScatteringDistribution(
					       MonteCarlo::N__2N_P_REACTION,
                                               properties,
					       scattering_dist );

  FRENSIE_CHECK( scattering_dist.get() != NULL );

  neutron_distribution_factory_o16->createScatteringDistribution(
					       MonteCarlo::N__N_2P_REACTION,
                                               properties,
					       scattering_dist );

  FRENSIE_CHECK( scattering_dist.get() != NULL );

  neutron_distribution_factory_o16->createScatteringDistribution(
					     MonteCarlo::N__N_P_ALPHA_REACTION,
                                             properties,
                                             scattering_dist );
  
  FRENSIE_CHECK( scattering_dist.get() != NULL );

  neutron_distribution_factory_o16->createScatteringDistribution(
                                     MonteCarlo::N__N_EXCITED_STATE_1_REACTION,
                                     properties,
                                     scattering_dist );

  FRENSIE_CHECK( scattering_dist.get() != NULL );

  neutron_distribution_factory_o16->createScatteringDistribution(
				     MonteCarlo::N__N_EXCITED_STATE_2_REACTION,
                                     properties,
                                     scattering_dist );
  
  FRENSIE_CHECK( scattering_dist.get() != NULL );

  neutron_distribution_factory_o16->createScatteringDistribution(
                                     MonteCarlo::N__N_EXCITED_STATE_3_REACTION,
                                     properties,
                                     scattering_dist );

  FRENSIE_CHECK( scattering_dist.get() != NULL );

  neutron_distribution_factory_o16->createScatteringDistribution(
				     MonteCarlo::N__N_EXCITED_STATE_4_REACTION,
                                     properties,
                                     scattering_dist );

  FRENSIE_CHECK( scattering_dist.get() != NULL );

  neutron_distribution_factory_o16->createScatteringDistribution(
				     MonteCarlo::N__N_EXCITED_STATE_5_REACTION,
                                     properties,
                                     scattering_dist );

  FRENSIE_CHECK( scattering_dist.get() != NULL );

  neutron_distribution_factory_o16->createScatteringDistribution(
				     MonteCarlo::N__N_EXCITED_STATE_6_REACTION,
                                     properties,
                                     scattering_dist );

  FRENSIE_CHECK( scattering_dist.get() != NULL );

  neutron_distribution_factory_o16->createScatteringDistribution(
				     MonteCarlo::N__N_EXCITED_STATE_7_REACTION,
                                     properties,
				     scattering_dist );

  FRENSIE_CHECK( scattering_dist.get() != NULL );

  neutron_distribution_factory_o16->createScatteringDistribution(
					   MonteCarlo::N__N_CONTINUUM_REACTION,
                                           properties,
                                           scattering_dist );

  FRENSIE_CHECK( scattering_dist.get() != NULL );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_basic_h1_ace_file_name;
unsigned test_basic_h1_ace_file_start_line;
std::string test_basic_o16_ace_file_name;
unsigned test_basic_o16_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_basic_h1_ace_file",
                                        test_basic_h1_ace_file_name, "",
                                        "Test basic H1 ACE file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_basic_h1_ace_file_start_line",
                                        test_basic_h1_ace_file_start_line, 1,
                                        "Test basic H1 ACE file start line" );
  
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_basic_o16_ace_file",
                                        test_basic_o16_ace_file_name, "",
                                        "Test basic O16 ACE file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_basic_o16_ace_file_start_line",
                                        test_basic_o16_ace_file_start_line, 1,
                                        "Test basic O16 ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the H-1 xss data extractor
  std::unique_ptr<Data::ACEFileHandler> ace_file_handler_h1(
               new Data::ACEFileHandler( test_basic_h1_ace_file_name,
                                         "1001.70c",
                                         test_basic_h1_ace_file_start_line ) );

  xss_data_extractor_h1.reset(
   new Data::XSSNeutronDataExtractor(ace_file_handler_h1->getTableNXSArray(),
                                     ace_file_handler_h1->getTableJXSArray(),
                                     ace_file_handler_h1->getTableXSSArray()));

  // Create the O-16 xss data extractor
  std::unique_ptr<Data::ACEFileHandler> ace_file_handler_o16(
              new Data::ACEFileHandler( test_basic_o16_ace_file_name,
                                        "8016.70c",
                                        test_basic_o16_ace_file_start_line ) );

  xss_data_extractor_o16.reset(
   new Data::XSSNeutronDataExtractor(ace_file_handler_o16->getTableNXSArray(),
                                     ace_file_handler_o16->getTableJXSArray(),
                                     ace_file_handler_o16->getTableXSSArray()));

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstNeutronNuclearScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//

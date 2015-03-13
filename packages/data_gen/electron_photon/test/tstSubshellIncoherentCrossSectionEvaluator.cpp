//---------------------------------------------------------------------------//
//!
//! \file   tstSubshellIncoherentCrossSectionEvaluator.cpp
//! \author Alex Robinson
//! \brief  Subshell incoherent cross section evaluator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "DataGen_SubshellIncoherentCrossSectionEvaluator.hpp"
#include "DataGen_OccupationNumberEvaluator.hpp"
#include "MonteCarlo_ComptonProfileHelpers.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverterFactory.hpp"
#include "MonteCarlo_SubshellType.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_GridGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<DataGen::SubshellIncoherentCrossSectionEvaluator>
  incoherent_cs_h_k;

Teuchos::RCP<DataGen::SubshellIncoherentCrossSectionEvaluator>
  incoherent_cs_b_l1;

Teuchos::RCP<DataGen::SubshellIncoherentCrossSectionEvaluator>
  incoherent_cs_b_l2;

Teuchos::RCP<DataGen::SubshellIncoherentCrossSectionEvaluator>
  incoherent_cs_b_l3;

Teuchos::RCP<DataGen::SubshellIncoherentCrossSectionEvaluator>
  incoherent_cs_b_k;

Teuchos::RCP<Utility::OneDDistribution> incoherent_cs_h;

Teuchos::RCP<Utility::OneDDistribution> incoherent_cs_b;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
bool notEqualZero( double value )
{
  return value != 0.0;
}

bool greaterThanOrEqualToOne( double value )
{
  return value >= 1.0;
}

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the number of electrons occupying a subshell can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentCrossSectionEvaluator, getSubshell_h )
{
  TEST_EQUALITY_CONST( incoherent_cs_h_k->getSubshell(), 
		       MonteCarlo::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons occupying a subshell can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentCrossSectionEvaluator, getSubshell_b )
{
  TEST_EQUALITY_CONST( incoherent_cs_b_k->getSubshell(), 
		       MonteCarlo::K_SUBSHELL );

  TEST_EQUALITY_CONST( incoherent_cs_b_l1->getSubshell(), 
		       MonteCarlo::L1_SUBSHELL );

  TEST_EQUALITY_CONST( incoherent_cs_b_l2->getSubshell(), 
		       MonteCarlo::L2_SUBSHELL );

  TEST_EQUALITY_CONST( incoherent_cs_b_l3->getSubshell(), 
		       MonteCarlo::L3_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons that occupy the subshell can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentCrossSectionEvaluator,
		   getNumberOfElectronsInSubshell_h )
{
  TEST_EQUALITY_CONST( incoherent_cs_h_k->getNumberOfElectronsInSubshell(),
		       1.0 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons that occupy the subshell can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentCrossSectionEvaluator,
		   getNumberOfElectronsInSubshell_b )
{
  TEST_EQUALITY_CONST( incoherent_cs_b_k->getNumberOfElectronsInSubshell(),
		       2.0 );

  TEST_EQUALITY_CONST( incoherent_cs_b_l1->getNumberOfElectronsInSubshell(),
		       2.0 );

  TEST_EQUALITY_CONST( incoherent_cs_b_l2->getNumberOfElectronsInSubshell(),
		       0.33 );

  TEST_EQUALITY_CONST( incoherent_cs_b_l3->getNumberOfElectronsInSubshell(),
		       0.67 );
}

//---------------------------------------------------------------------------//
// Check that the binding energy of the subshell can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentCrossSectionEvaluator,
		   getSubshellBindingEnergy_h )
{
  TEST_EQUALITY_CONST( incoherent_cs_h_k->getSubshellBindingEnergy(),
		       1.361e-5 );
}

//---------------------------------------------------------------------------//
// Check that the binding energy of the subshell can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentCrossSectionEvaluator,
		   getSubshellBindingEnergy_b )
{
  TEST_EQUALITY_CONST( incoherent_cs_b_k->getSubshellBindingEnergy(),
		       1.9561e-04 );

  TEST_EQUALITY_CONST( incoherent_cs_b_l1->getSubshellBindingEnergy(),
		       1.258e-05 );

  TEST_EQUALITY_CONST( incoherent_cs_b_l2->getSubshellBindingEnergy(),
		       6.67e-06 );

  TEST_EQUALITY_CONST( incoherent_cs_b_l3->getSubshellBindingEnergy(),
		       6.66e-06 );
}

//---------------------------------------------------------------------------//
// Check that the max electron momentum projection can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentCrossSectionEvaluator,
		   getMaxElectronMomentumProjection_h )
{
  double max_electron_momentum_projection = 
    incoherent_cs_h_k->getMaxElectronMomentumProjection( 1.361e-5, -1.0 );
  
  TEST_EQUALITY_CONST( max_electron_momentum_projection, -1.0 );

  max_electron_momentum_projection = 
    incoherent_cs_h_k->getMaxElectronMomentumProjection( 1.361e-5, 0.0 );

  TEST_EQUALITY_CONST( max_electron_momentum_projection, -1.0 );

  max_electron_momentum_projection = 
    incoherent_cs_h_k->getMaxElectronMomentumProjection( 1.361e-5, 1.0 );

  TEST_EQUALITY_CONST( max_electron_momentum_projection, -1.0 );

  max_electron_momentum_projection = 
    incoherent_cs_h_k->getMaxElectronMomentumProjection( 1e-3, -1.0 );

  TEST_FLOATING_EQUALITY( max_electron_momentum_projection, 
			  -0.004908082271294833, 
			  1e-15 );

  max_electron_momentum_projection = 
    incoherent_cs_h_k->getMaxElectronMomentumProjection( 1e-3, 0.0 );

  TEST_FLOATING_EQUALITY( max_electron_momentum_projection, 
			  -0.008315173801003727,
			  1e-15 );

  max_electron_momentum_projection = 
    incoherent_cs_h_k->getMaxElectronMomentumProjection( 1e-3, 1.0 );

  TEST_FLOATING_EQUALITY( max_electron_momentum_projection, -1.0, 1e-15 );

  max_electron_momentum_projection = 
    incoherent_cs_h_k->getMaxElectronMomentumProjection( 1.0, -1.0 );

  TEST_FLOATING_EQUALITY( max_electron_momentum_projection, 
			  1.9569312140568826,
			  1e-15 );

  max_electron_momentum_projection = 
    incoherent_cs_h_k->getMaxElectronMomentumProjection( 1.0, 0.0 );

  TEST_FLOATING_EQUALITY( max_electron_momentum_projection, 
			  1.3837545198488141,
			  1e-15 );

  max_electron_momentum_projection = 
    incoherent_cs_h_k->getMaxElectronMomentumProjection( 1.0, 1.0 );

  TEST_FLOATING_EQUALITY( max_electron_momentum_projection, -1.0, 1e-15 );

  max_electron_momentum_projection = 
    incoherent_cs_h_k->getMaxElectronMomentumProjection( 20.0, -1.0 );

  TEST_FLOATING_EQUALITY( max_electron_momentum_projection, 
			  39.13901306764466,
			  1e-15 );

  max_electron_momentum_projection = 
    incoherent_cs_h_k->getMaxElectronMomentumProjection( 20.0, 0.0 );

  TEST_FLOATING_EQUALITY( max_electron_momentum_projection, 
			  27.67546130848567,
			  1e-15 );

  max_electron_momentum_projection = 
    incoherent_cs_h_k->getMaxElectronMomentumProjection( 20.0, 1.0 );

  TEST_FLOATING_EQUALITY( max_electron_momentum_projection, -1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the max electron momentum projection can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentCrossSectionEvaluator,
		   getMaxElectronMomentumProjection_b )
{
  // K-shell
  double max_electron_momentum_projection = 
    incoherent_cs_b_k->getMaxElectronMomentumProjection( 1.9561e-04, -1.0 );
  
  TEST_EQUALITY_CONST( max_electron_momentum_projection, -1.0 );

  max_electron_momentum_projection = 
    incoherent_cs_b_k->getMaxElectronMomentumProjection( 1.9561e-04, 1.0 );

  TEST_EQUALITY_CONST( max_electron_momentum_projection, -1.0 );

  max_electron_momentum_projection = 
    incoherent_cs_b_k->getMaxElectronMomentumProjection( 1e-3, -1.0 );

  TEST_FLOATING_EQUALITY( max_electron_momentum_projection, 
			  -0.10666302508286538,
			  1e-15 );

  max_electron_momentum_projection = 
    incoherent_cs_b_k->getMaxElectronMomentumProjection( 1e-3, 1.0 );

  TEST_FLOATING_EQUALITY( max_electron_momentum_projection, 
			  -0.9999999999999993,
			  1e-12 );

  max_electron_momentum_projection = 
    incoherent_cs_b_k->getMaxElectronMomentumProjection( 1.0, -1.0 );

  TEST_FLOATING_EQUALITY( max_electron_momentum_projection, 
			  1.9566621033337905,
			  1e-15 );

  max_electron_momentum_projection = 
    incoherent_cs_b_k->getMaxElectronMomentumProjection( 1.0, 1.0 );

  TEST_FLOATING_EQUALITY( max_electron_momentum_projection, 
			  -0.9999999996226776,
			  1e-6 );

  // L1-shell
  max_electron_momentum_projection = 
    incoherent_cs_b_l1->getMaxElectronMomentumProjection( 1.258e-05, -1.0 );
  
  TEST_EQUALITY_CONST( max_electron_momentum_projection, -1.0 );

  max_electron_momentum_projection = 
    incoherent_cs_b_l1->getMaxElectronMomentumProjection( 1.258e-05, 1.0 );

  TEST_EQUALITY_CONST( max_electron_momentum_projection, -1.0 );

  max_electron_momentum_projection = 
    incoherent_cs_b_l1->getMaxElectronMomentumProjection( 1e-3, -1.0 );

  TEST_FLOATING_EQUALITY( max_electron_momentum_projection, 
			  -0.0043852503361768895,
			  1e-15 );

  max_electron_momentum_projection = 
    incoherent_cs_b_l1->getMaxElectronMomentumProjection( 1e-3, 1.0 );

  TEST_FLOATING_EQUALITY( max_electron_momentum_projection, 
			  -1.0000000000003024,
			  1e-12 );

  max_electron_momentum_projection = 
    incoherent_cs_b_l1->getMaxElectronMomentumProjection( 1.0, -1.0 );

  TEST_FLOATING_EQUALITY( max_electron_momentum_projection, 
			  1.9569327369067626,
			  1e-15 );

  max_electron_momentum_projection = 
    incoherent_cs_b_l1->getMaxElectronMomentumProjection( 1.0, 1.0 );

  TEST_FLOATING_EQUALITY( max_electron_momentum_projection, 
			  -1.0000006403118626,
			  1e-6 );

  // L2-shell
  max_electron_momentum_projection = 
    incoherent_cs_b_l2->getMaxElectronMomentumProjection( 6.67e-06, -1.0 );
  
  TEST_EQUALITY_CONST( max_electron_momentum_projection, -1.0 );

  max_electron_momentum_projection = 
    incoherent_cs_b_l2->getMaxElectronMomentumProjection( 6.67e-06, 1.0 );

  TEST_EQUALITY_CONST( max_electron_momentum_projection, -1.0 );

  max_electron_momentum_projection = 
    incoherent_cs_b_l2->getMaxElectronMomentumProjection( 1e-3, -1.0 );

  TEST_FLOATING_EQUALITY( max_electron_momentum_projection, 
			  -0.001395756376681346,
			  1e-15 );

  max_electron_momentum_projection = 
    incoherent_cs_b_l2->getMaxElectronMomentumProjection( 1e-3, 1.0 );

  TEST_FLOATING_EQUALITY( max_electron_momentum_projection, 
			  -1.0000000000020621,
			  1e-11 );

  max_electron_momentum_projection = 
    incoherent_cs_b_l2->getMaxElectronMomentumProjection( 1.0, -1.0 );

  TEST_FLOATING_EQUALITY( max_electron_momentum_projection, 
			  1.9569414747820633,
			  1e-15 );

  max_electron_momentum_projection = 
    incoherent_cs_b_l2->getMaxElectronMomentumProjection( 1.0, 1.0 );

  TEST_FLOATING_EQUALITY( max_electron_momentum_projection, 
			  -1.0000020359820747,
			  1e-5 );

  // L3-shell
  max_electron_momentum_projection = 
    incoherent_cs_b_l3->getMaxElectronMomentumProjection( 6.66e-06, -1.0 );
  
  TEST_EQUALITY_CONST( max_electron_momentum_projection, -1.0 );

  max_electron_momentum_projection = 
    incoherent_cs_b_l3->getMaxElectronMomentumProjection( 6.66e-06, 1.0 );

  TEST_EQUALITY_CONST( max_electron_momentum_projection, -1.0 );

  max_electron_momentum_projection = 
    incoherent_cs_b_l3->getMaxElectronMomentumProjection( 1e-3, -1.0 );

  TEST_FLOATING_EQUALITY( max_electron_momentum_projection, 
			  -0.0013907130340551548,
			  1e-15 );

  max_electron_momentum_projection = 
    incoherent_cs_b_l3->getMaxElectronMomentumProjection( 1e-3, 1.0 );

  TEST_FLOATING_EQUALITY( max_electron_momentum_projection, 
			  -1.0000000000002678,
			  1e-11 );

  max_electron_momentum_projection = 
    incoherent_cs_b_l3->getMaxElectronMomentumProjection( 1.0, -1.0 );

  TEST_FLOATING_EQUALITY( max_electron_momentum_projection, 
			  1.9569414895669182,
			  1e-15 );

  max_electron_momentum_projection = 
    incoherent_cs_b_l3->getMaxElectronMomentumProjection( 1.0, 1.0 );

  TEST_FLOATING_EQUALITY( max_electron_momentum_projection, 
			  -1.0000000432652363,
			  1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the differential cross section can be evaluated
TEUCHOS_UNIT_TEST( SubshellIncoherentCrossSectionEvaluator,
		   evaluateDifferentialCrossSection_h )
{
  // Evaluate the differential cross section at E = be
  Teuchos::RCP<Utility::KleinNishinaDistribution> free_distribution(
			   new Utility::KleinNishinaDistribution( 1.361e-5 ) );

  double diff_cross_section = 
    incoherent_cs_h_k->evaluateDifferentialCrossSection( 1.0000532682153727,
							 *free_distribution );

  TEST_FLOATING_EQUALITY( diff_cross_section,
			  0.0,
			  1e-15 );

  diff_cross_section = 
    incoherent_cs_h_k->evaluateDifferentialCrossSection( 1.0,
							 *free_distribution );

  TEST_FLOATING_EQUALITY( diff_cross_section,
			  0.0,
			  1e-15 );

  // Evaluate the differential cross section at E = 0.001 MeV
  free_distribution.reset( new Utility::KleinNishinaDistribution( 0.001 ) );

  diff_cross_section = 
    incoherent_cs_h_k->evaluateDifferentialCrossSection( 1.0039139026724953,
							 *free_distribution );

  TEST_FLOATING_EQUALITY( diff_cross_section,
			  24.445250173280783,
			  1e-12 );

  diff_cross_section = 
    incoherent_cs_h_k->evaluateDifferentialCrossSection( 1.0019569513362476,
							 *free_distribution );

  TEST_FLOATING_EQUALITY( diff_cross_section,
			  3.2787925986124202,
			  1e-12 );

  diff_cross_section = 
    incoherent_cs_h_k->evaluateDifferentialCrossSection( 1.0,
							 *free_distribution );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
				  0.0,
				  1e-15 );

  // Evaluate the differential cross section at E = 1.0 MeV
  free_distribution.reset( new Utility::KleinNishinaDistribution( 1.0 ) );
    
  diff_cross_section = 
    incoherent_cs_h_k->evaluateDifferentialCrossSection( 4.913902672495315,
							 *free_distribution );

  TEST_FLOATING_EQUALITY( diff_cross_section,
			  0.02701657438992967,
			  1e-12 );

  diff_cross_section = 
    incoherent_cs_h_k->evaluateDifferentialCrossSection( 2.9569513362476574,
							 *free_distribution );

  TEST_FLOATING_EQUALITY( diff_cross_section,
			  0.033462145517114565,
			  1e-12 );

  diff_cross_section = 
    incoherent_cs_h_k->evaluateDifferentialCrossSection( 1.0,
							 *free_distribution );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
				  0.0,
				  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the differential cross section can be evaluated
TEUCHOS_UNIT_TEST( SubshellIncoherentCrossSectionEvaluator,
		   evaluateDifferentialCrossSection_b )
{
  // K-shell
  // Evaluate the differential cross section at E = be
  Teuchos::RCP<Utility::KleinNishinaDistribution> free_distribution(
			   new Utility::KleinNishinaDistribution( 1.9561e-04));

  double diff_cross_section = 
    incoherent_cs_b_k->evaluateDifferentialCrossSection( 1.0007655985017667,
							 *free_distribution );

  TEST_FLOATING_EQUALITY( diff_cross_section,
			  0.0,
			  1e-15 );

  diff_cross_section = 
    incoherent_cs_b_k->evaluateDifferentialCrossSection( 1.0,
							 *free_distribution );

  TEST_FLOATING_EQUALITY( diff_cross_section,
			  0.0,
			  1e-15 );

  // Evaluate the differential cross section at E = 0.001 MeV
  free_distribution.reset( new Utility::KleinNishinaDistribution( 0.001 ) );

  diff_cross_section = 
    incoherent_cs_b_k->evaluateDifferentialCrossSection( 1.0039139026724953,
							 *free_distribution );

  TEST_FLOATING_EQUALITY( diff_cross_section,
			  0.2747080177336685,
			  1e-12 );

  diff_cross_section = 
    incoherent_cs_b_k->evaluateDifferentialCrossSection( 1.0,
							 *free_distribution );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
				  0.0,
				  1e-15 );

  // Evaluate the differential cross section at E = 1.0 MeV
  free_distribution.reset( new Utility::KleinNishinaDistribution( 1.0 ) );
    
  diff_cross_section = 
    incoherent_cs_b_k->evaluateDifferentialCrossSection( 4.913902672495315,
							 *free_distribution );

  TEST_FLOATING_EQUALITY( diff_cross_section,
			  0.05403314877985934,
			  1e-12 );

  diff_cross_section = 
    incoherent_cs_b_k->evaluateDifferentialCrossSection( 1.0,
							 *free_distribution );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
				  0.0,
				  1e-15 );
  
  // L1-shell
  // Evaluate the differential cross section at E = be
  free_distribution.reset(new Utility::KleinNishinaDistribution( 1.258e-05 ));

  diff_cross_section = 
    incoherent_cs_b_l1->evaluateDifferentialCrossSection( 1.00004923689562,
							 *free_distribution );

  TEST_FLOATING_EQUALITY( diff_cross_section,
			  0.0,
			  1e-15 );

  diff_cross_section = 
    incoherent_cs_b_l1->evaluateDifferentialCrossSection( 1.0,
							 *free_distribution );

  TEST_FLOATING_EQUALITY( diff_cross_section,
			  0.0,
			  1e-15 );

  // Evaluate the differential cross section at E = 0.001 MeV
  free_distribution.reset( new Utility::KleinNishinaDistribution( 0.001 ) );

  diff_cross_section = 
    incoherent_cs_b_l1->evaluateDifferentialCrossSection( 1.0039139026724953,
							 *free_distribution );

  TEST_FLOATING_EQUALITY( diff_cross_section,
			  43.489582549402044,
			  1e-12 );

  diff_cross_section = 
    incoherent_cs_b_l1->evaluateDifferentialCrossSection( 1.0,
							 *free_distribution );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
				  0.0,
				  1e-15 );

  // Evaluate the differential cross section at E = 1.0 MeV
  free_distribution.reset( new Utility::KleinNishinaDistribution( 1.0 ) );
    
  diff_cross_section = 
    incoherent_cs_b_l1->evaluateDifferentialCrossSection( 4.913902672495315,
							 *free_distribution );

  TEST_FLOATING_EQUALITY( diff_cross_section,
			  0.05403314877985934,
			  1e-12 );

  diff_cross_section = 
    incoherent_cs_b_l1->evaluateDifferentialCrossSection( 1.0,
							 *free_distribution );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
				  0.0,
				  1e-15 );

  // L2-shell
  // Evaluate the differential cross section at E = be
  free_distribution.reset( new Utility::KleinNishinaDistribution( 6.67e-6 ) );

  diff_cross_section = 
    incoherent_cs_b_l2->evaluateDifferentialCrossSection( 1.0000261057308255,
							 *free_distribution );

  TEST_FLOATING_EQUALITY( diff_cross_section,
			  0.0,
			  1e-15 );

  diff_cross_section = 
    incoherent_cs_b_l2->evaluateDifferentialCrossSection( 1.0,
							 *free_distribution );

  TEST_FLOATING_EQUALITY( diff_cross_section,
			  0.0,
			  1e-15 );

  // Evaluate the differential cross section at E = 0.001 MeV
  free_distribution.reset( new Utility::KleinNishinaDistribution( 0.001 ) );

  diff_cross_section = 
    incoherent_cs_b_l2->evaluateDifferentialCrossSection( 1.0039139026724953,
							 *free_distribution );

  TEST_FLOATING_EQUALITY( diff_cross_section,
			  31.938843431155334,
			  1e-12 );

  diff_cross_section = 
    incoherent_cs_b_l2->evaluateDifferentialCrossSection( 1.0,
							 *free_distribution );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
				  0.0,
				  1e-15 );

  // Evaluate the differential cross section at E = 1.0 MeV
  free_distribution.reset( new Utility::KleinNishinaDistribution( 1.0 ) );
    
  diff_cross_section = 
    incoherent_cs_b_l2->evaluateDifferentialCrossSection( 4.913902672495315,
							 *free_distribution );

  TEST_FLOATING_EQUALITY( diff_cross_section,
			  0.008915469548676792,
			  1e-12 );

  diff_cross_section = 
    incoherent_cs_b_l2->evaluateDifferentialCrossSection( 1.0,
							 *free_distribution );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
				  0.0,
				  1e-15 );

  // L3-shell
  // Evaluate the differential cross section at E = be
  free_distribution.reset( new Utility::KleinNishinaDistribution( 6.66e-6 ) );

  diff_cross_section = 
    incoherent_cs_b_l3->evaluateDifferentialCrossSection( 1.0000260665917988,
							 *free_distribution );

  TEST_FLOATING_EQUALITY( diff_cross_section,
			  0.0,
			  1e-15 );

  diff_cross_section = 
    incoherent_cs_b_l3->evaluateDifferentialCrossSection( 1.0,
							 *free_distribution );

  TEST_FLOATING_EQUALITY( diff_cross_section,
			  0.0,
			  1e-15 );

  // Evaluate the differential cross section at E = 0.001 MeV
  free_distribution.reset( new Utility::KleinNishinaDistribution( 0.001 ) );

  diff_cross_section = 
    incoherent_cs_b_l3->evaluateDifferentialCrossSection( 1.0039139026724953,
							 *free_distribution );

  TEST_FLOATING_EQUALITY( diff_cross_section,
			  64.9170600137117,
			  1e-12 );

  diff_cross_section = 
    incoherent_cs_b_l3->evaluateDifferentialCrossSection( 1.0,
							 *free_distribution );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
				  0.0,
				  1e-15 );

  // Evaluate the differential cross section at E = 1.0 MeV
  free_distribution.reset( new Utility::KleinNishinaDistribution( 1.0 ) );
    
  diff_cross_section = 
    incoherent_cs_b_l3->evaluateDifferentialCrossSection( 4.913902672495315,
							 *free_distribution );

  TEST_FLOATING_EQUALITY( diff_cross_section,
			  0.01810110484125288,
			  1e-12 );

  diff_cross_section = 
    incoherent_cs_b_l3->evaluateDifferentialCrossSection( 1.0,
							 *free_distribution );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
				  0.0,
				  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be evaluated
TEUCHOS_UNIT_TEST( SubshellIncoherentCrossSectionEvaluator,
		   evaluateCrossSection_h )
{
  double cross_section = incoherent_cs_h_k->evaluateCrossSection( 1.361e-5 );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-15 );

  cross_section = incoherent_cs_h_k->evaluateCrossSection( 0.0001, 1e-4 );
  
  // Large difference between this cross section and table cross section
  TEST_FLOATING_EQUALITY( cross_section, 
			  3.75706853090582114e-07,
			  1e-15 );

  cross_section = incoherent_cs_h_k->evaluateCrossSection( 0.001, 1e-4 );
  
  // Large differences between this cross section and table cross section
  TEST_FLOATING_EQUALITY( cross_section, 
			  0.0231176950398478895,
			  1e-15 );

  cross_section = incoherent_cs_h_k->evaluateCrossSection( 0.005, 1e-4 );
  
  TEST_FLOATING_EQUALITY( cross_section, 
			  incoherent_cs_h->evaluate( 0.005 ),
			  5e-2 );

  cross_section = incoherent_cs_h_k->evaluateCrossSection( 0.01, 1e-4 );

  TEST_FLOATING_EQUALITY( cross_section, 
			  incoherent_cs_h->evaluate( 0.01 ),
			  1e-2 );

  cross_section = incoherent_cs_h_k->evaluateCrossSection( 0.1, 1e-4 );

  TEST_FLOATING_EQUALITY( cross_section, 
			  incoherent_cs_h->evaluate( 0.1 ),
			  1e-3 );

  cross_section = incoherent_cs_h_k->evaluateCrossSection( 1.0, 1e-4 );

  TEST_FLOATING_EQUALITY( cross_section, 
			  incoherent_cs_h->evaluate( 1.0 ),
			  1e-3 );

  cross_section = incoherent_cs_h_k->evaluateCrossSection( 10.0, 1e-4 );

  TEST_FLOATING_EQUALITY( cross_section, 
			  incoherent_cs_h->evaluate( 10.0 ),
			  1e-3 );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be evaluated
TEUCHOS_UNIT_TEST( SubshellIncoherentCrossSectionEvaluator,
		   evaluateCrossSection_b )
{
  double cross_section = incoherent_cs_b_k->evaluateCrossSection( 1.9561e-04 )
    + incoherent_cs_b_l1->evaluateCrossSection( 1.9561e-04, 1e-4 )
    + incoherent_cs_b_l2->evaluateCrossSection( 1.9561e-04, 1e-4 )
    + incoherent_cs_b_l3->evaluateCrossSection( 1.9561e-04, 1e-4 );
  
  // Large differences between this cross section and table cross section
  TEST_FLOATING_EQUALITY( cross_section,
			  0.00207911778477741678,
			  1e-15 );

  cross_section = incoherent_cs_b_k->evaluateCrossSection( 1e-3, 1e-4 )
    + incoherent_cs_b_l1->evaluateCrossSection( 1e-3, 1e-4 )
    + incoherent_cs_b_l2->evaluateCrossSection( 1e-3, 1e-4 )
    + incoherent_cs_b_l3->evaluateCrossSection( 1e-3, 1e-4 );
  
  // Large differences between this cross section and table cross section
  TEST_FLOATING_EQUALITY( cross_section, 
			  0.186226573369796589,
			  1e-15 );

  cross_section = incoherent_cs_b_k->evaluateCrossSection( 5e-3, 1e-4 )
    + incoherent_cs_b_l1->evaluateCrossSection( 5e-3, 1e-4 )
    + incoherent_cs_b_l2->evaluateCrossSection( 5e-3, 1e-4 )
    + incoherent_cs_b_l3->evaluateCrossSection( 5e-3, 1e-4 );
  
  // Large differences between this cross section and table cross section
  TEST_FLOATING_EQUALITY( cross_section, 
			  1.68753378868863657,
			  1e-15 );
  
  cross_section = incoherent_cs_b_k->evaluateCrossSection( 1e-2, 1e-4 )
    + incoherent_cs_b_l1->evaluateCrossSection( 1e-2, 1e-4 )
    + incoherent_cs_b_l2->evaluateCrossSection( 1e-2, 1e-4 )
    + incoherent_cs_b_l3->evaluateCrossSection( 1e-2, 1e-4 );

  TEST_FLOATING_EQUALITY( cross_section, 
			  incoherent_cs_b->evaluate( 1e-2 ),
			  1e-2 );

  cross_section = incoherent_cs_b_k->evaluateCrossSection( 0.1, 1e-4 )
    + incoherent_cs_b_l1->evaluateCrossSection( 0.1, 1e-4 )
    + incoherent_cs_b_l2->evaluateCrossSection( 0.1, 1e-4 )
    + incoherent_cs_b_l3->evaluateCrossSection( 0.1, 1e-4 );

  TEST_FLOATING_EQUALITY( cross_section, 
			  incoherent_cs_b->evaluate( 0.1 ),
			  1e-3 );

  cross_section = incoherent_cs_b_k->evaluateCrossSection( 1.0, 1e-4 )
    + incoherent_cs_b_l1->evaluateCrossSection( 1.0, 1e-4 )
    + incoherent_cs_b_l2->evaluateCrossSection( 1.0, 1e-4 )
    + incoherent_cs_b_l3->evaluateCrossSection( 1.0, 1e-4 );
  
  TEST_FLOATING_EQUALITY( cross_section, 
			  incoherent_cs_b->evaluate( 1.0 ),
			  1e-3 );

  cross_section = incoherent_cs_b_k->evaluateCrossSection( 10.0, 1e-4 )
    + incoherent_cs_b_l1->evaluateCrossSection( 10.0, 1e-4 )
    + incoherent_cs_b_l2->evaluateCrossSection( 10.0, 1e-4 )
    + incoherent_cs_b_l3->evaluateCrossSection( 10.0, 1e-4 );

  TEST_FLOATING_EQUALITY( cross_section, 
			  incoherent_cs_b->evaluate( 10.0 ),
			  1e-3 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_h_ace_file_name, test_h_ace_table_name;
  std::string test_b_ace_file_name, test_b_ace_table_name;
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_h_ace_file",
		 &test_h_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_h_ace_table",
		 &test_h_ace_table_name,
		 "Test ACE table name" );
  clp.setOption( "test_b_ace_file",
		 &test_b_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_b_ace_table",
		 &test_b_ace_table_name,
		 "Test ACE table name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  
  {
    // Create the file handler and data extractor for hydrogen
    Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
			       new Data::ACEFileHandler( test_h_ace_file_name,
							 test_h_ace_table_name,
							 1u ) );

    Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
				new Data::XSSEPRDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );
    
    // Create the Compton profile subshell converter
    Teuchos::RCP<MonteCarlo::ComptonProfileSubshellConverter> converter;
    
    MonteCarlo::ComptonProfileSubshellConverterFactory::createConverter(
				   converter,
			           xss_data_extractor->extractAtomicNumber() );

    unsigned k_shell_index = converter->convertSubshellToIndex(
						      MonteCarlo::K_SUBSHELL );

    // Pull out the k-shell compton profile for hydrogen
    Teuchos::ArrayView<const double> lswd_block = 
      xss_data_extractor->extractLSWDBlock();
    
    Teuchos::ArrayView<const double> swd_block = 
      xss_data_extractor->extractSWDBlock();

    unsigned profile_index = lswd_block[k_shell_index]; // ignore interp param
    
    unsigned num_mom_vals = swd_block[profile_index];
    
    Teuchos::ArrayView<const double> raw_momentum_grid = 
      swd_block( profile_index + 1, num_mom_vals );

    Teuchos::ArrayView<const double> raw_compton_profile = 
      swd_block( profile_index + 1 + num_mom_vals, num_mom_vals );

    std::cout.precision( 18 );
    for( unsigned i = 0; i < raw_momentum_grid.size(); ++i )
      std::cout << raw_momentum_grid[i] << " " << raw_compton_profile[i] << std::endl;
    
    std::vector<double> full_momentum_grid, full_compton_profile;

    MonteCarlo::createFullProfileFromHalfProfile( raw_momentum_grid.begin(),
						  raw_momentum_grid.end(),
						  raw_compton_profile.begin(),
						  raw_compton_profile.end(),
						  full_momentum_grid,
						  full_compton_profile,
						  true );

    MonteCarlo::convertMomentumGridToMeCUnits( full_momentum_grid.begin(),
					       full_momentum_grid.end() );

    MonteCarlo::convertProfileToInverseMeCUnits( full_compton_profile.begin(),
						 full_compton_profile.end() );
    
    DataGen::OccupationNumberEvaluator occupation_number_h_k(
							  full_momentum_grid,
							  full_compton_profile,
							  1e-4 );

    // Create the occupation number grid
    boost::function<double (double pz)> grid_function = 
      boost::bind( &DataGen::OccupationNumberEvaluator::evaluateOccupationNumber,
		   boost::cref( occupation_number_h_k ),
		   _1,
		   1e-4 );

    Utility::GridGenerator<Utility::LinLin> occupation_number_grid_generator(
								       1e-3,
								       1e-12,
								       1e-12 );
    
    Teuchos::Array<double> momentum_projection, occupation_number;
    Teuchos::Array<double> initial_momentum_projection( 3 );
    initial_momentum_projection[0] = -1.0;
    initial_momentum_projection[1] = 0.0;
    initial_momentum_projection[2] = 1.0;

    occupation_number_grid_generator.generateAndEvaluate( 
						   momentum_projection,
						   occupation_number,
						   initial_momentum_projection,
						   grid_function );

    // Fix the grid rounding errors
    Teuchos::Array<double>::iterator full_occupancy = 
      std::find_if( occupation_number.begin(),
		    occupation_number.end(),
		    greaterThanOrEqualToOne );

    while( full_occupancy != occupation_number.end() )
    {
      *full_occupancy = 1.0;
      
      ++full_occupancy;
    }

    Teuchos::RCP<Utility::OneDDistribution> occupation_number_dist(
			    new Utility::TabularDistribution<Utility::LinLin>(
						         momentum_projection,
							 occupation_number ) );

    // Create the subshell order array
    Teuchos::ArrayView<const double> subshell_endf_des = 
      xss_data_extractor->extractSubshellENDFDesignators();
    
    boost::unordered_map<MonteCarlo::SubshellType,unsigned> subshell_order;

    for( unsigned i = 0; i < subshell_endf_des.size(); ++i )
    {
      MonteCarlo::SubshellType subshell = 
	MonteCarlo::convertENDFDesignatorToSubshellEnum( 
					      (unsigned)subshell_endf_des[i] );
      subshell_order[subshell] = i;
    }

    unsigned k_subshell_index = subshell_order[MonteCarlo::K_SUBSHELL];

    // Create the cross section evaluator
    incoherent_cs_h_k.reset( 
     new DataGen::SubshellIncoherentCrossSectionEvaluator(
	MonteCarlo::K_SUBSHELL,
	xss_data_extractor->extractSubshellOccupancies()[k_subshell_index],
	xss_data_extractor->extractSubshellBindingEnergies()[k_subshell_index],
	occupation_number_dist ) );

     // Extract the total incoherent cross section
     Teuchos::ArrayView<const double> raw_energy_grid = 
       xss_data_extractor->extractPhotonEnergyGrid();
     
     Teuchos::ArrayView<const double> raw_incoherent_cross_section = 
       xss_data_extractor->extractIncoherentCrossSection();

     Teuchos::ArrayView<const double>::iterator start = 
       std::find_if( raw_incoherent_cross_section.begin(),
		     raw_incoherent_cross_section.end(),
		     notEqualZero );

     Teuchos::Array<double> incoherent_cross_section;
     incoherent_cross_section.assign( start, 
				      raw_incoherent_cross_section.end() );

     unsigned start_index = std::distance(raw_incoherent_cross_section.begin(),
					  start );

     start = raw_energy_grid.begin();

     std::advance( start, start_index );

     Teuchos::Array<double> energy_grid;
     energy_grid.assign( start, raw_energy_grid.end() );

     // Extract the original energy and cross section values
     for( unsigned i = 0; i < energy_grid.size(); ++i )
     {
       energy_grid[i] = exp( energy_grid[i] );
       incoherent_cross_section[i] = exp( incoherent_cross_section[i] );
     }

     incoherent_cs_h.reset( new Utility::TabularDistribution<Utility::LogLog>(
						  energy_grid,
						  incoherent_cross_section ) );
  }

  {
    // Create the file handler and data extractor for boron
    Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
			       new Data::ACEFileHandler( test_b_ace_file_name,
							 test_b_ace_table_name,
							 1u ) );

    Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
				new Data::XSSEPRDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );
    
    // Create the Compton profile subshell converter
    Teuchos::RCP<MonteCarlo::ComptonProfileSubshellConverter> converter;
    
    MonteCarlo::ComptonProfileSubshellConverterFactory::createConverter(
				   converter,
			           xss_data_extractor->extractAtomicNumber() );

    unsigned k_shell_index = converter->convertSubshellToIndex(
						      MonteCarlo::K_SUBSHELL );

    Teuchos::ArrayView<const double> lswd_block = 
      xss_data_extractor->extractLSWDBlock();
    
    Teuchos::ArrayView<const double> swd_block = 
      xss_data_extractor->extractSWDBlock();

    // Pull out the k-shell compton profile for boron
    unsigned profile_index = lswd_block[k_shell_index]; // ignore interp param
    
    unsigned num_mom_vals = swd_block[profile_index];

    Teuchos::ArrayView<const double> raw_momentum_grid = 
      swd_block( profile_index + 1, num_mom_vals );

    Teuchos::ArrayView<const double> raw_compton_profile = 
      swd_block( profile_index + 1 + num_mom_vals, num_mom_vals );

    std::vector<double> full_momentum_grid, full_compton_profile;

    MonteCarlo::createFullProfileFromHalfProfile( raw_momentum_grid.begin(),
						  raw_momentum_grid.end(),
						  raw_compton_profile.begin(),
						  raw_compton_profile.end(),
						  full_momentum_grid,
						  full_compton_profile,
						  true );

    MonteCarlo::convertMomentumGridToMeCUnits( full_momentum_grid.begin(),
					       full_momentum_grid.end() );

    MonteCarlo::convertProfileToInverseMeCUnits( full_compton_profile.begin(),
						 full_compton_profile.end() );
    
    DataGen::OccupationNumberEvaluator occupation_number_b_k(
							  full_momentum_grid,
							  full_compton_profile,
							  1e-4 );

    // Pull out the l1-shell compton profile for boron
    unsigned l1_shell_index = converter->convertSubshellToIndex(
						     MonteCarlo::L1_SUBSHELL );

    profile_index = lswd_block[l1_shell_index]; // ignore interp param
    
    num_mom_vals = swd_block[profile_index];

    raw_momentum_grid = swd_block( profile_index + 1, num_mom_vals );

    raw_compton_profile = 
      swd_block( profile_index + 1 + num_mom_vals, num_mom_vals );

    full_momentum_grid, full_compton_profile;

    MonteCarlo::createFullProfileFromHalfProfile( raw_momentum_grid.begin(),
						  raw_momentum_grid.end(),
						  raw_compton_profile.begin(),
						  raw_compton_profile.end(),
						  full_momentum_grid,
						  full_compton_profile,
						  true );

    MonteCarlo::convertMomentumGridToMeCUnits( full_momentum_grid.begin(),
					       full_momentum_grid.end() );

    MonteCarlo::convertProfileToInverseMeCUnits( full_compton_profile.begin(),
						 full_compton_profile.end() );
    
    DataGen::OccupationNumberEvaluator occupation_number_b_l1(
							  full_momentum_grid,
							  full_compton_profile,
							  1e-4 );

    // Pull out the l2-shell compton profile for boron
    unsigned l2_shell_index = converter->convertSubshellToIndex(
						     MonteCarlo::L2_SUBSHELL );

    profile_index = lswd_block[l2_shell_index]; // ignore interp param
    
    num_mom_vals = swd_block[profile_index];

    raw_momentum_grid = swd_block( profile_index + 1, num_mom_vals );

    raw_compton_profile = 
      swd_block( profile_index + 1 + num_mom_vals, num_mom_vals );

    full_momentum_grid, full_compton_profile;

    MonteCarlo::createFullProfileFromHalfProfile( raw_momentum_grid.begin(),
						  raw_momentum_grid.end(),
						  raw_compton_profile.begin(),
						  raw_compton_profile.end(),
						  full_momentum_grid,
						  full_compton_profile,
						  true );

    MonteCarlo::convertMomentumGridToMeCUnits( full_momentum_grid.begin(),
					       full_momentum_grid.end() );

    MonteCarlo::convertProfileToInverseMeCUnits( full_compton_profile.begin(),
						 full_compton_profile.end() );
    
    DataGen::OccupationNumberEvaluator occupation_number_b_l2(
							  full_momentum_grid,
							  full_compton_profile,
							  1e-4 );

    // Pull out the l3-shell compton profile for boron
    unsigned l3_shell_index = converter->convertSubshellToIndex(
						     MonteCarlo::L3_SUBSHELL );

    profile_index = lswd_block[l3_shell_index]; // ignore interp param
    
    num_mom_vals = swd_block[profile_index];

    raw_momentum_grid = swd_block( profile_index + 1, num_mom_vals );

    raw_compton_profile = 
      swd_block( profile_index + 1 + num_mom_vals, num_mom_vals );

    full_momentum_grid, full_compton_profile;

    MonteCarlo::createFullProfileFromHalfProfile( raw_momentum_grid.begin(),
						  raw_momentum_grid.end(),
						  raw_compton_profile.begin(),
						  raw_compton_profile.end(),
						  full_momentum_grid,
						  full_compton_profile,
						  true );

    MonteCarlo::convertMomentumGridToMeCUnits( full_momentum_grid.begin(),
					       full_momentum_grid.end() );

    MonteCarlo::convertProfileToInverseMeCUnits( full_compton_profile.begin(),
						 full_compton_profile.end() );
    
    DataGen::OccupationNumberEvaluator occupation_number_b_l3(
							  full_momentum_grid,
							  full_compton_profile,
							  1e-4 );
    
    // Create the occupation number grids for the k-shell
    boost::function<double (double pz)> grid_function = 
      boost::bind( &DataGen::OccupationNumberEvaluator::evaluateOccupationNumber,
		   boost::cref( occupation_number_b_k ),
		   _1,
		   1e-4 );

    Utility::GridGenerator<Utility::LinLin> occupation_number_grid_generator( 
								       1e-3,
								       1e-12,
								       1e-12 );
    Teuchos::Array<double> momentum_projection, occupation_number;
    Teuchos::Array<double> initial_momentum_projection( 3 );
    initial_momentum_projection[0] = -1.0;
    initial_momentum_projection[1] = 0.0;
    initial_momentum_projection[2] = 1.0;

    occupation_number_grid_generator.generateAndEvaluate( 
						   momentum_projection,
						   occupation_number,
						   initial_momentum_projection,
						   grid_function );

    // Fix the grid rounding errors
    Teuchos::Array<double>::iterator full_occupancy = 
      std::find_if( occupation_number.begin(),
		    occupation_number.end(),
		    greaterThanOrEqualToOne );

    while( full_occupancy != occupation_number.end() )
    {
      *full_occupancy = 1.0;
      
      ++full_occupancy;
    }

    Teuchos::RCP<Utility::OneDDistribution> occupation_number_dist_k(
			    new Utility::TabularDistribution<Utility::LinLin>(
						         momentum_projection,
							 occupation_number ) );

    // Create the occupation number grids for the l1-shell
    grid_function = boost::bind( 
		 &DataGen::OccupationNumberEvaluator::evaluateOccupationNumber,
		 boost::cref( occupation_number_b_l1 ),
		 _1,
		 1e-4 );

    occupation_number_grid_generator.generateAndEvaluate( 
						   momentum_projection,
						   occupation_number,
						   initial_momentum_projection,
						   grid_function );

    // Fix the grid rounding errors
    full_occupancy = std::find_if( occupation_number.begin(),
				   occupation_number.end(),
				   greaterThanOrEqualToOne );

    while( full_occupancy != occupation_number.end() )
    {
      *full_occupancy = 1.0;
      
      ++full_occupancy;
    }

    Teuchos::RCP<Utility::OneDDistribution> occupation_number_dist_l1(
			    new Utility::TabularDistribution<Utility::LinLin>(
						         momentum_projection,
							 occupation_number ) );

    // Create the occupation number grids for the l2-shell
    grid_function = boost::bind( 
		 &DataGen::OccupationNumberEvaluator::evaluateOccupationNumber,
		 boost::cref( occupation_number_b_l2 ),
		 _1,
		 1e-4 );

    occupation_number_grid_generator.generateAndEvaluate( 
						   momentum_projection,
						   occupation_number,
						   initial_momentum_projection,
						   grid_function );

    // Fix the grid rounding errors
    full_occupancy = std::find_if( occupation_number.begin(),
				   occupation_number.end(),
				   greaterThanOrEqualToOne );

    while( full_occupancy != occupation_number.end() )
    {
      *full_occupancy = 1.0;
      
      ++full_occupancy;
    }

    Teuchos::RCP<Utility::OneDDistribution> occupation_number_dist_l2(
			    new Utility::TabularDistribution<Utility::LinLin>(
						         momentum_projection,
							 occupation_number ) );

    // Create the occupation number grids for the l3-shell
    grid_function = boost::bind( 
		 &DataGen::OccupationNumberEvaluator::evaluateOccupationNumber,
		 boost::cref( occupation_number_b_l3 ),
		 _1,
		 1e-4 );

    occupation_number_grid_generator.generateAndEvaluate( 
						   momentum_projection,
						   occupation_number,
						   initial_momentum_projection,
						   grid_function );

    // Fix the grid rounding errors
    full_occupancy = std::find_if( occupation_number.begin(),
				   occupation_number.end(),
				   greaterThanOrEqualToOne );

    while( full_occupancy != occupation_number.end() )
    {
      *full_occupancy = 1.0;
      
      ++full_occupancy;
    }
    
    Teuchos::RCP<Utility::OneDDistribution> occupation_number_dist_l3(
			    new Utility::TabularDistribution<Utility::LinLin>(
						         momentum_projection,
							 occupation_number ) );

    // Create the subshell order array
    Teuchos::ArrayView<const double> subshell_endf_des = 
      xss_data_extractor->extractSubshellENDFDesignators();
    
    boost::unordered_map<MonteCarlo::SubshellType,unsigned> subshell_order;
    
    for( unsigned i = 0; i < subshell_endf_des.size(); ++i )
    {
      MonteCarlo::SubshellType subshell = 
	MonteCarlo::convertENDFDesignatorToSubshellEnum( 
					      (unsigned)subshell_endf_des[i] );
      
      subshell_order[subshell] = i;
    }

    unsigned k_subshell_index = subshell_order[MonteCarlo::K_SUBSHELL];

    // Create the cross section evaluator for the k-shell
    incoherent_cs_b_k.reset( 
     new DataGen::SubshellIncoherentCrossSectionEvaluator(
    	MonteCarlo::K_SUBSHELL,
    	xss_data_extractor->extractSubshellOccupancies()[k_subshell_index],
    	xss_data_extractor->extractSubshellBindingEnergies()[k_subshell_index],
    	occupation_number_dist_k ) );

    unsigned l1_subshell_index = subshell_order[MonteCarlo::L1_SUBSHELL];
    
    // Create the cross section evaluator for the l1-shell
    incoherent_cs_b_l1.reset( 
     new DataGen::SubshellIncoherentCrossSectionEvaluator(
       MonteCarlo::L1_SUBSHELL,
       xss_data_extractor->extractSubshellOccupancies()[l1_subshell_index],
       xss_data_extractor->extractSubshellBindingEnergies()[l1_subshell_index],
       occupation_number_dist_l1 ) );

    unsigned l2_subshell_index = subshell_order[MonteCarlo::L2_SUBSHELL];

    // Create the cross section evaluator for the l2-shell
    incoherent_cs_b_l2.reset( 
     new DataGen::SubshellIncoherentCrossSectionEvaluator(
       MonteCarlo::L2_SUBSHELL,
       xss_data_extractor->extractSubshellOccupancies()[l2_subshell_index],
       xss_data_extractor->extractSubshellBindingEnergies()[l2_subshell_index],
       occupation_number_dist_l2 ) );

    unsigned l3_subshell_index = subshell_order[MonteCarlo::L3_SUBSHELL];
    
    // Create the cross section evaluator for the l3-shell
    incoherent_cs_b_l3.reset( 
     new DataGen::SubshellIncoherentCrossSectionEvaluator(
       MonteCarlo::L3_SUBSHELL,
       xss_data_extractor->extractSubshellOccupancies()[l3_subshell_index],
       xss_data_extractor->extractSubshellBindingEnergies()[l3_subshell_index],
       occupation_number_dist_l3 ) ); 

     // Extract the total incoherent cross section
     Teuchos::ArrayView<const double> raw_energy_grid = 
       xss_data_extractor->extractPhotonEnergyGrid();
     
     Teuchos::ArrayView<const double> raw_incoherent_cross_section = 
       xss_data_extractor->extractIncoherentCrossSection();

     Teuchos::ArrayView<const double>::iterator start = 
       std::find_if( raw_incoherent_cross_section.begin(),
		     raw_incoherent_cross_section.end(),
		     notEqualZero );

     Teuchos::Array<double> incoherent_cross_section;
     incoherent_cross_section.assign( start, 
				      raw_incoherent_cross_section.end() );

     unsigned start_index = std::distance(raw_incoherent_cross_section.begin(),
					  start );

     start = raw_energy_grid.begin();

     std::advance( start, start_index );

     Teuchos::Array<double> energy_grid;
     energy_grid.assign( start, raw_energy_grid.end() );

     // Extract the original energy and cross section values
     for( unsigned i = 0; i < energy_grid.size(); ++i )
     {
       energy_grid[i] = exp( energy_grid[i] );
       incoherent_cross_section[i] = exp( incoherent_cross_section[i] );
     }

     incoherent_cs_b.reset( new Utility::TabularDistribution<Utility::LogLog>(
     						  energy_grid,
     						  incoherent_cross_section ) );
  }

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
// end tstSubshellIncoherentCrossSectionEvaluator.cpp
//---------------------------------------------------------------------------//

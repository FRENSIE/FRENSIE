//---------------------------------------------------------------------------//
//!
//! \file   tstGeneralEstimatorDimensionDiscretization.cpp
//! \author Alex Robinson
//! \brief  General estimator dimension discretization unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "FACEMC_UnitTestHarnessExtensions.hpp"
#include "GeneralEstimatorDimensionDiscretization.hpp"
#include "EstimatorPhaseSpaceDimensionTraits.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name )				\
  using namespace FACEMC;						\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, ENERGY_DIMENSION )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, COSINE_DIMENSION )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, TIME_DIMENSION )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, COLLISION_NUMBER_DIMENSION ) \

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize an estimator dimension discretization pointer
template<FACEMC::EstimatorPhaseSpaceDimension dimension>
void initialize( Teuchos::RCP<FACEMC::EstimatorDimensionDiscretization>&
		 dimension_discretization,
		 const bool add_discrete_lines )
{
  typedef FACEMC::Traits::EstimatorPhaseSpaceDimensionTraits<dimension> EPSDT;

  Teuchos::Array<typename EPSDT::dimensionType> discretization( 4 );

  if( add_discrete_lines )
    discretization.resize( 9 );
  
  discretization[0] = 0.0;
  discretization[1] = 1.0;
  discretization[2] = 2.0;
  discretization[3] = 3.0;
  
  if( add_discrete_lines )
  {
    discretization[4] = 3.0;
    discretization[5] = 4.0;
    discretization[6] = 5.0;
    discretization[7] = 5.0;
    discretization[8] = 6.0;
  }

  dimension_discretization.reset( 
                new FACEMC::GeneralEstimatorDimensionDiscretization<dimension>(
							    discretization ) );
}

// Initialize an estimator dimension discretization point
template<>
void initialize<FACEMC::COLLISION_NUMBER_DIMENSION>( 
			Teuchos::RCP<FACEMC::EstimatorDimensionDiscretization>&
			dimension_discretization,
			const bool )
{
  typedef FACEMC::Traits::EstimatorPhaseSpaceDimensionTraits<FACEMC::COLLISION_NUMBER_DIMENSION> EPSDT;

  Teuchos::Array<typename EPSDT::dimensionType> discretization( 3 );

  discretization[0] = 0;
  discretization[1] = 1;
  discretization[2] = std::numeric_limits<unsigned>::max();

  dimension_discretization.reset( new FACEMC::GeneralEstimatorDimensionDiscretization<FACEMC::COLLISION_NUMBER_DIMENSION>( discretization ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the discretized dimension can be returned
FACEMC_UNIT_TEST_EPSD_TEMPLATE_1_DECL( GeneralEstimatorDimensionDiscretization,
				       getDimension,
				       dimension )
{
  Teuchos::RCP<FACEMC::EstimatorDimensionDiscretization> discretized_dimension;

  initialize<dimension>( discretized_dimension, false );

  TEST_EQUALITY_CONST( discretized_dimension->getDimension(),
		       dimension );
}

UNIT_TEST_INSTANTIATION( GeneralEstimatorDimensionDiscretization,
			 getDimension );

//---------------------------------------------------------------------------//
// Check that the number of bins can be returned
FACEMC_UNIT_TEST_EPSD_TEMPLATE_1_DECL( GeneralEstimatorDimensionDiscretization,
				       getNumberOfBins,
				       dimension )
{
  Teuchos::RCP<FACEMC::EstimatorDimensionDiscretization> discretized_dimension;

  initialize<dimension>( discretized_dimension, false );

  TEST_EQUALITY_CONST( discretized_dimension->getNumberOfBins(), 3u );
}

UNIT_TEST_INSTANTIATION( GeneralEstimatorDimensionDiscretization,
			 getNumberOfBins );

//---------------------------------------------------------------------------//
// Check if a value is contained in the discretization
FACEMC_UNIT_TEST_EPSD_TEMPLATE_1_DECL( GeneralEstimatorDimensionDiscretization,
				       isValueInDiscretization,
				       dimension )
{
  Teuchos::RCP<FACEMC::EstimatorDimensionDiscretization> discretized_dimension;

  initialize<dimension>( discretized_dimension, false );

  typedef FACEMC::Traits::EstimatorPhaseSpaceDimensionTraits<dimension> EPSDT;

  typename EPSDT::dimensionType value_1, value_2, value_3, value_4;
  value_1 = -1;
  value_2 = 0;
  value_3 = 3;
  value_4 = 4;

  if( dimension != FACEMC::COLLISION_NUMBER_DIMENSION )
  {
    TEST_ASSERT( !discretized_dimension->isValueInDiscretization( 
						   Teuchos::any( value_1 ) ) );
    TEST_ASSERT( discretized_dimension->isValueInDiscretization( 
						   Teuchos::any( value_2 ) ) );
    TEST_ASSERT( discretized_dimension->isValueInDiscretization( 
						   Teuchos::any( value_3 ) ) );
    TEST_ASSERT( !discretized_dimension->isValueInDiscretization( 
						   Teuchos::any( value_4 ) ) );
  }
  else
  {
    TEST_ASSERT( discretized_dimension->isValueInDiscretization( 
						   Teuchos::any( value_1 ) ) );
    TEST_ASSERT( discretized_dimension->isValueInDiscretization( 
						   Teuchos::any( value_2 ) ) );
    TEST_ASSERT( discretized_dimension->isValueInDiscretization( 
						   Teuchos::any( value_3 ) ) );
    TEST_ASSERT( discretized_dimension->isValueInDiscretization( 
						   Teuchos::any( value_4 ) ) );
  }
 }

UNIT_TEST_INSTANTIATION( GeneralEstimatorDimensionDiscretization,
			 isValueInDiscretization );

//---------------------------------------------------------------------------//
// Check that a bin index can be calculated
FACEMC_UNIT_TEST_EPSD_TEMPLATE_1_DECL( GeneralEstimatorDimensionDiscretization,
				       calculateBinIndex,
				       dimension )
{
  Teuchos::RCP<FACEMC::EstimatorDimensionDiscretization> discretized_dimension;

  initialize<dimension>( discretized_dimension, true );

  typedef FACEMC::Traits::EstimatorPhaseSpaceDimensionTraits<dimension> EPSDT;

  typename EPSDT::dimensionType value_1, value_2, value_3, value_4,
    value_5, value_6, value_7, value_8, value_9, value_10, value_11,
    value_12, value_13, value_14, value_15, value_16, value_17;
  
  value_1 = 0;
  value_2 = 0.5;
  value_3 = 1;
  value_4 = 1.5;
  value_5 = 2;
  value_6 = 2.5;
  value_7 = 2.9999999999999;
  value_8 = 3;
  value_9 = 3.0000000000001;
  value_10 = 3.5;
  value_11 = 4;
  value_12 = 4.5;
  value_13 = 4.999999999999;
  value_14 = 5;
  value_15 = 5.000000000001;
  value_16 = 5.5;
  value_17 = 6;

  if( dimension != FACEMC::COLLISION_NUMBER_DIMENSION )
  {
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					       Teuchos::any( value_1 ) ), 0u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					       Teuchos::any( value_2 ) ), 0u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					       Teuchos::any( value_3 ) ), 0u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					       Teuchos::any( value_4 ) ), 1u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					       Teuchos::any( value_5 ) ), 1u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					       Teuchos::any( value_6 ) ), 2u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					       Teuchos::any( value_7 ) ), 2u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					       Teuchos::any( value_8 ) ), 3u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					       Teuchos::any( value_9 ) ), 4u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					      Teuchos::any( value_10 ) ), 4u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					      Teuchos::any( value_11 ) ), 4u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					      Teuchos::any( value_12 ) ), 5u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					      Teuchos::any( value_13 ) ), 5u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					      Teuchos::any( value_14 ) ), 6u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					      Teuchos::any( value_15 ) ), 7u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					      Teuchos::any( value_16 ) ), 7u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					      Teuchos::any( value_17 ) ), 7u );
  }
  else
  {
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					       Teuchos::any( value_1 ) ), 0u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					       Teuchos::any( value_3 ) ), 1u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					       Teuchos::any( value_5 ) ), 2u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					       Teuchos::any( value_8 ) ), 2u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					      Teuchos::any( value_11 ) ), 2u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					      Teuchos::any( value_14 ) ), 2u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					      Teuchos::any( value_17 ) ), 2u );
  }

  discretized_dimension->print( std::cout );
}

UNIT_TEST_INSTANTIATION( GeneralEstimatorDimensionDiscretization,
			 calculateBinIndex );

//---------------------------------------------------------------------------//
// end tstGeneralEstimatorDimensionDiscretization.cpp
//---------------------------------------------------------------------------//


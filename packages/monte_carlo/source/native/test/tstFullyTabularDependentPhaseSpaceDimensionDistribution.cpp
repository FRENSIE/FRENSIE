//---------------------------------------------------------------------------//
//!
//! \file   tstFullyTabularDependentPhaseSpaceDimensionDistribution.cpp
//! \author Alex Robinson
//! \brief  Fully-tabular dependent phase space dimension dist. unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_FullyTabularDependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_PhaseSpaceDimensionTraits.hpp"
#include "MonteCarlo_SourceUnitTestHarnessExtensions.hpp"
#include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_HistogramFullyTabularTwoDDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

using namespace MonteCarlo;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
spatial_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
directional_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

std::shared_ptr<const Utility::FullyTabularTwoDDistribution> raw_distribution;

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, PRIMARY_SPATIAL_DIMENSION, SECONDARY_SPATIAL_DIMENSION )

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Test that the dimension can be returned
MC_UNIT_TEST_PSD_TEMPLATE_2_DECL( DepedentPhaseSpaceDimensionDistribution,
                                  getDimension,
                                  IndepDimension,
                                  DepDimension )
{
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::FullyTabularDependentPhaseSpaceDimensionDistribution<IndepDimension,DepDimension>( raw_distribution ) );

  TEST_EQUALITY_CONST( dimension_distribution->getDimension(), DepDimension );
}

UNIT_TEST_INSTANTIATION( DepedentPhaseSpaceDimensionDistribution,
                         getDimension );

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create the fully tabular distribution
  Utility::HistogramFullyTabularTwoDDistribution::DistributionType
    distribution_data( 4 );

  // Create the secondary distribution in the first bin
  Utility::get<0>( distribution_data[0] ) = 0.0;
  Utility::get<1>( distribution_data[0] ).reset( new Utility::DeltaDistribution( 0.0 ) );
    
  // Create the secondary distribution in the second bin
  Utility::get<0>( distribution_data[1] ) = 0.0;
  Utility::get<1>( distribution_data[1] ).reset( new Utility::UniformDistribution( 0.0, 10.0, 2.0 ) );

  // Create the secondary distribution in the third bin
  Utility::get<0>( distribution_data[2] ) = 1.0;
  Utility::get<1>( distribution_data[2] ).reset( new Utility::UniformDistribution( 0.0, 10.0, 1.0 ) );
  
  // Create the secondary distribution beyond the third bin
  Utility::get<0>( distribution_data[3] ) = 2.0;
  Utility::get<1>( distribution_data[3] ) =
    Utility::get<1>( distribution_data[0] );

  raw_distribution.reset( new Utility::HistogramFullyTabularTwoDDistribution(
                                                         distribution_data ) );
    
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstFullyTabularDependentPhaseSpaceDimensionDistribution.cpp
//---------------------------------------------------------------------------//

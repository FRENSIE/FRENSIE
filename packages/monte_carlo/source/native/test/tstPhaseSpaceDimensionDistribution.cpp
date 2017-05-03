//---------------------------------------------------------------------------//
//!
//! \file   tstPhaseSpaceDimensionDistribution.cpp
//! \author Alex Robinson
//! \brief  Phase space dimension distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_IndependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_FullyTabularDependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_PartiallyTabularDependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_SourceUnitTestHarnessExtensions.hpp"
#include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"
#include "Utility_HistogramFullyTabularTwoDDistribution.hpp"
#include "Utility_HistogramPartiallyTabularTwoDDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_ExponentialDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

using namespace MonteCarlo;

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
spatial_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
directional_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

std::shared_ptr<const Utility::OneDDistribution> raw_indep_distribution;
std::shared_ptr<const Utility::FullyTabularTwoDDistribution> raw_dep_distribution_a;
std::shared_ptr<const Utility::PartiallyTabularTwoDDistribution> raw_dep_distribution_b;

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, PRIMARY_SPATIAL_DIMENSION, SECONDARY_SPATIAL_DIMENSION )

//---------------------------------------------------------------------------//
// Check that the parent distribution can be returned
MC_UNIT_TEST_PSD_TEMPLATE_2_DECL( PhaseSpaceDimensionDistribution,
                                  getParentDistribution,
                                  IndepDimension,
                                  DepDimension )
{
  // Create the distribution for the independent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    indep_dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<IndepDimension>( raw_indep_distribution ) );

  // Create the distribution for the dependent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    dep_dimension_distribution( new MonteCarlo::FullyTabularDependentPhaseSpaceDimensionDistribution<IndepDimension,DepDimension>( raw_dep_distribution_a ) );

  // Assign the dep dimension distribution to the indep dimension distribution
  indep_dimension_distribution->addDependentDimension(
                                                  dep_dimension_distribution );

  // The indep dimension will not have a parent
  TEST_ASSERT( !indep_dimension_distribution->getParentDistribution() );
  TEST_EQUALITY_CONST( dep_dimension_distribution->getParentDistribution(),
                       indep_dimension_distribution.get() );
}

UNIT_TEST_INSTANTIATION( PhaseSpaceDimensionDistribution,
                         getParentDistribution );

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create the raw independent distribution
  raw_indep_distribution.reset(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  // Create the raw fully-tabular dependent distribution
  {
    // Create the fully tabular distribution
    Utility::HistogramFullyTabularTwoDDistribution::DistributionType
      distribution_data( 3 );
    
    // Create the secondary distribution in the first bin
    Utility::get<0>( distribution_data[0] ) = 0.1;
    Utility::get<1>( distribution_data[0] ).reset( new Utility::UniformDistribution( 0.5, 0.9, 0.5 ) );

      
    // Create the secondary distribution in the second bin
    Utility::get<0>( distribution_data[1] ) = 0.5;
    Utility::get<1>( distribution_data[1] ).reset( new Utility::UniformDistribution( 0.6, 0.8, 0.4 ) );
    
    // Create the secondary distribution in the third bin
    Utility::get<0>( distribution_data[2] ) = 0.9;
    Utility::get<1>( distribution_data[2] ) =
      Utility::get<1>( distribution_data[1] );
    
    Utility::HistogramFullyTabularTwoDDistribution* local_raw_distribution =
      new Utility::HistogramFullyTabularTwoDDistribution( distribution_data );
    
    local_raw_distribution->limitToPrimaryIndepLimits();
    
    raw_dep_distribution_a.reset( local_raw_distribution );
  }

  // Create the raw partially-tabular dependent distribution
  {
    // Create the partially tabular distribution
    Utility::HistogramPartiallyTabularTwoDDistribution::DistributionType
      distribution_data( 3 );

    // Create the secondary distribution in the first bin
    Utility::get<0>( distribution_data[0] ) = 0.1;
    Utility::get<1>( distribution_data[0] ).reset( new Utility::UniformDistribution( 0.5, 0.9, 0.5 ) );

    // Create the secondary distribution in the second bin
    Utility::get<0>( distribution_data[1] ) = 0.5;
    Utility::get<1>( distribution_data[1] ).reset( new Utility::ExponentialDistribution( 1.0, 1.0, 0.6, 0.8 ) );
    
    // Create the secondary distribution in the third bin
    Utility::get<0>( distribution_data[2] ) = 0.9;
    Utility::get<1>( distribution_data[2] ) =
      Utility::get<1>( distribution_data[1] );
    
    Utility::HistogramPartiallyTabularTwoDDistribution*
      local_raw_distribution =
      new Utility::HistogramPartiallyTabularTwoDDistribution( distribution_data );

    local_raw_distribution->limitToPrimaryIndepLimits();
    
    raw_dep_distribution_b.reset( local_raw_distribution );
  }
  
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();


//---------------------------------------------------------------------------//
// end tstPhaseSpaceDimensionDistribution.cpp
//---------------------------------------------------------------------------//

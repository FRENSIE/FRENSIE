//---------------------------------------------------------------------------//
//!
//! \file   tstSpatialDistribution.cpp
//! \author Alex Robinson
//! \brief  Spatial distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_PowerDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_SpatialDistribution.hpp"
#include "Utility_CartesianSpatialDistribution.hpp"
#include "Utility_CylindricalSpatialDistribution.hpp"
#include "Utility_SphericalSpatialDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the bounds of two distributions can be tests
TEUCHOS_UNIT_TEST( SpatialDistribution, hasSameBounds )
{
  std::shared_ptr<Utility::OneDDistribution> delta_dist(
					new Utility::DeltaDistribution( 1. ) );
  std::shared_ptr<Utility::OneDDistribution> discrete_dist(
	new Utility::DiscreteDistribution( Teuchos::tuple( -1.0, 0.0, 1.0 ),
					   Teuchos::tuple( 1.0, 1.0, 1.0 ) ) );
  std::shared_ptr<Utility::OneDDistribution> histogram_dist(
       new Utility::HistogramDistribution( Teuchos::tuple( -1.0, 0.0, 1.0 ),
					   Teuchos::tuple( 1.0, 1.0 ) ) );

  std::shared_ptr<Utility::OneDDistribution> power_1_dist(
			 new Utility::PowerDistribution<1u>( 1.0, 0.0, 1.0 ) );

  std::shared_ptr<Utility::OneDDistribution> power_2_dist(
			 new Utility::PowerDistribution<2u>( 1.0, 0.0, 1.0 ) );

  std::shared_ptr<Utility::OneDDistribution> uniform_dist(
	    new Utility::UniformDistribution( 0.0, 
					      2*Utility::PhysicalConstants::pi,
					      1.0 ) );
  
  // Create the cartesian spatial distributions
  std::shared_ptr<Utility::SpatialDistribution> cartesian_dist_a(
		 new Utility::CartesianSpatialDistribution( delta_dist,
							    discrete_dist,
							    histogram_dist ) );
  
  std::shared_ptr<Utility::SpatialDistribution> cartesian_dist_b(
		 new Utility::CartesianSpatialDistribution( delta_dist,
							    histogram_dist,
							    histogram_dist ) );

  std::shared_ptr<Utility::SpatialDistribution> cartesian_dist_c(
		new Utility::CartesianSpatialDistribution( discrete_dist,
							   power_1_dist,
							   histogram_dist ) );

  // Create the cylindrical spatial distributions
  std::shared_ptr<Utility::SpatialDistribution> cylindrical_dist_a(
	      new Utility::CylindricalSpatialDistribution( power_1_dist,
							   uniform_dist,
							   histogram_dist,
							   0.0, 0.0, 0.0,
							   Utility::Z_AXIS ) );

  std::shared_ptr<Utility::SpatialDistribution> cylindrical_dist_b(
	      new Utility::CylindricalSpatialDistribution( power_1_dist,
							   uniform_dist,
							   histogram_dist,
							   0.0, 0.0, 0.0,
							   Utility::Y_AXIS ) );

  std::shared_ptr<Utility::SpatialDistribution> cylindrical_dist_c(
	      new Utility::CylindricalSpatialDistribution( power_1_dist,
							   uniform_dist,
							   histogram_dist,
							   0.0, 0.0, 0.0,
							   Utility::X_AXIS ) );

  std::shared_ptr<Utility::SpatialDistribution> cylindrical_dist_d(
	      new Utility::CylindricalSpatialDistribution( power_1_dist,
							   uniform_dist,
							   histogram_dist,
							   0.0, 0.0, 0.0,
							   Utility::Z_AXIS ) );
  
  std::shared_ptr<Utility::SpatialDistribution> cylindrical_dist_e(
	      new Utility::CylindricalSpatialDistribution( histogram_dist,
							   uniform_dist,
							   histogram_dist,
							   0.0, 0.0, 0.0,
							   Utility::Z_AXIS ) );

  // Create the spherical spatial distributions
  std::shared_ptr<Utility::SpatialDistribution> spherical_dist_a(
	      new Utility::SphericalSpatialDistribution( power_2_dist,
							 uniform_dist,
							 histogram_dist,
							 0.0, 0.0, 0.0,
							 Utility::Z_AXIS ) );

  std::shared_ptr<Utility::SpatialDistribution> spherical_dist_b(
	      new Utility::SphericalSpatialDistribution( power_2_dist,
							 uniform_dist,
							 histogram_dist,
							 0.0, 0.0, 0.0,
							 Utility::Y_AXIS ) );

  std::shared_ptr<Utility::SpatialDistribution> spherical_dist_c(
	      new Utility::SphericalSpatialDistribution( power_2_dist,
							 uniform_dist,
							 histogram_dist,
							 0.0, 0.0, 0.0,
							 Utility::X_AXIS ) );

  std::shared_ptr<Utility::SpatialDistribution> spherical_dist_d(
	      new Utility::SphericalSpatialDistribution( power_2_dist,
							 uniform_dist,
							 histogram_dist,
							 0.0, 0.0, 0.0,
							 Utility::Z_AXIS ) );
  
  std::shared_ptr<Utility::SpatialDistribution> spherical_dist_e(
	      new Utility::SphericalSpatialDistribution( histogram_dist,
							 uniform_dist,
							 histogram_dist,
							 0.0, 0.0, 0.0,
							 Utility::Z_AXIS ) );

  TEST_ASSERT( cartesian_dist_a->hasSameBounds( *cartesian_dist_b ) );
  TEST_ASSERT( !cartesian_dist_a->hasSameBounds( *cartesian_dist_c ) );
  TEST_ASSERT( !cartesian_dist_a->hasSameBounds( *cylindrical_dist_a ) );
  TEST_ASSERT( !cartesian_dist_a->hasSameBounds( *spherical_dist_a ) );
  TEST_ASSERT( !cartesian_dist_b->hasSameBounds( *cartesian_dist_c ) );
  
  TEST_ASSERT( !cylindrical_dist_a->hasSameBounds( *cylindrical_dist_b ) );
  TEST_ASSERT( !cylindrical_dist_a->hasSameBounds( *cylindrical_dist_c ) );
  TEST_ASSERT( cylindrical_dist_a->hasSameBounds( *cylindrical_dist_d ) );
  TEST_ASSERT( !cylindrical_dist_a->hasSameBounds( *cylindrical_dist_e ) );
  TEST_ASSERT( !cylindrical_dist_b->hasSameBounds( *cylindrical_dist_c ) );
  TEST_ASSERT( !cylindrical_dist_d->hasSameBounds( *cylindrical_dist_e ) );
  
  TEST_ASSERT( !spherical_dist_a->hasSameBounds( *spherical_dist_b ) );
  TEST_ASSERT( !spherical_dist_a->hasSameBounds( *spherical_dist_c ) );
  TEST_ASSERT( spherical_dist_a->hasSameBounds( *spherical_dist_d ) );
  TEST_ASSERT( !spherical_dist_a->hasSameBounds( *spherical_dist_e ) );
  TEST_ASSERT( !spherical_dist_b->hasSameBounds( *spherical_dist_c ) );
  TEST_ASSERT( !spherical_dist_d->hasSameBounds( *spherical_dist_e ) );
}

//---------------------------------------------------------------------------//
// end tstSpatialDistribution.cpp
//---------------------------------------------------------------------------//
